#include <Wire.h>
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
#include <SoftwareSerial.h>
#endif

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
int8_t sensorsServiceId;
uint8_t sensorsServiceUUID[] {0xfc, 0xed, 0x64, 0x08, 0xc0, 0x15, 0x45, 0xea, 0xb5, 0x0d, 0x1d, 0xe3, 0x2a, 0x1c, 0x2f, 0x6d};

/* declare inertial sensor*/
lsm6d_sensor sensor;

memcpy(sensor.accGyroUUID, sensorServiceUUID, 16);


void setup_gatt()
{
  ble.setInterCharWriteDelay(5);

  ble.atcommand("AT+GAPDEVNAME=smartShirt");
  ble.atcommand("AT+GATTCLEAR");

  generate_sensors_uuids(sensorsServiceUUID, allSensors);//TODO

  Serial.println("Adding sensors service");
  sensorsServiceId = gatt.addService(sensorsServiceUUID);
  if(sensorsServiceId == 0)
  {
    Serial.println(sensorsServiceId);
    ble.atcommand("AT+GATTLIST");
    error(F("Failed to create sensors service "));
  }
  ble.atcommand("AT+GATTLIST");

  init_characteristics(allSensors);

  // Serial.println("Adding sensors service UUID to the advertising payload");
  // uint8_t advdata[] { 0x02, 0x01, 0x06, 0x11, 0x06, 0x6d, 0x2f, 0x1c, 0x2a, 0xe3, 0x1d, 0x0d, 0xb5, 0xea, 0x45, 0x15, 0xc0, 0x08, 0x64, 0xfc };
  // ble.setAdvData(advdata, sizeof(advdata));

  Serial.println("Performing SW reset (service changes require reset)");
  ble.reset();
}

void setup()
{
  pinMode(7, OUTPUT) //activate pin #7 for trigering I2C communication of IMU
  digitalWrite(7, HIGH) //activate I2C on IMU
}
