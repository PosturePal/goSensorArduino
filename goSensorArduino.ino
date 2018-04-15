

#include <Wire.h>
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
#include <SoftwareSerial.h>
#endif

/*including LSM6D struct*/
#include "imuAttributes.h"

/*includind libs and configs headers for adafruit LE bluetooth module */
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLEGatt.h"
#include "bleConfig.h" // config header for BLE module 

/*accelerometer lib */
#include <LSM6.h>


/*=========================================================================
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    MODE_LED_BEHAVIOUR        LED activity, valid options are
                              "DISABLE" or "MODE" or "BLEUART" or
                              "HWUART"  or "SPI"  or "MANUAL"
    -----------------------------------------------------------------------*/
#define FACTORYRESET_ENABLE         0 //sometimes needs to chage
// #define GAPDEVNAME "[R]_SERMO_"
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/

/* Create blkuefruit objects */
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                              BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

Adafruit_BLEGatt gatt(ble);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/*prepare bluetooth sensor services*/
int8_t sensorServiceId;
uint8_t sensorServiceUUID[] {0xfc, 0xed, 0x64, 0x08, 0xc0, 0x15, 0x45, 0xea, 0xb5, 0x0d, 0x1d, 0xe3, 0x2a, 0x1c, 0x2f, 0x6d};

/* declare inertial sensor*/
lsm6d_sensor sensor;

void init_characteristics()
{

  memcpy(sensor.accGyroUUID, sensorServiceUUID, 16);
  sensor.accGyroUUID[3] += 0x01; //prosto edenica i troika
  Serial.println("- adding gyro and acc characteristic");
  sensor.accGyroID = gatt.addCharacteristic(sensor.accGyroUUID, GATT_CHARS_PROPERTIES_READ, 1, 20, BLE_DATATYPE_STRING);
  if (sensor.accGyroID == 0)
  {
    error(F("Failed to init characteristic"));
  }

}

void setup_gatt()
{
  ble.setInterCharWriteDelay(5);

  ble.atcommand("AT+GAPDEVNAME=smartShirt");
  ble.atcommand("AT+GATTCLEAR");

  Serial.println("Adding sensor service");
  sensorServiceId = gatt.addService(sensorServiceUUID);
  if (sensorServiceId == 0)
  {
    Serial.println(sensorServiceId);
    ble.atcommand("AT+GATTLIST");
    error(F("Failed to create sensors service "));
  }
  ble.atcommand("AT+GATTLIST");

  init_characteristics();

  // Serial.println("Adding sensors service UUID to the advertising payload");
  // uint8_t advdata[] { 0x02, 0x01, 0x06, 0x11, 0x06, 0x6d, 0x2f, 0x1c, 0x2a, 0xe3, 0x1d, 0x0d, 0xb5, 0xea, 0x45, 0x15, 0xc0, 0x08, 0x64, 0xfc };
  // ble.setAdvData(advdata, sizeof(advdata));

  Serial.println("Performing SW reset (service changes require reset)");
  ble.reset();
}

void setup()
{
  Serial.begin(115200);



  pinMode(7, OUTPUT); //activate pin #7 for trigering I2C communication of IMU
  digitalWrite(7, HIGH); //activate I2C on IMU

  memcpy(sensor.accGyroUUID, sensorServiceUUID, 16);

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ) {
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  ble.verbose(true);  // debug info is a little annoying after this point!

  if ( GATT_RUN_SETUP )
  {
    setup_gatt();
  }

  I2C_Init();

  init_sensors();

  Serial.println(F("Adafruit Bluefruit Command <-> Data Mode"));
  Serial.println(F("------------------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  /* Wait for connection */
  while (!ble.isConnected()) {
    delay(500);
    Serial.println("fuck");
  }

  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));

}

void loop(void)
{

  read_sensor_data();
  generate_packege();
  
}
