# goSensorArduino

[![N|Solid](https://github.com/PosturePal/goSensorArduino/blob/master/img/go-logo-boxing-white-fb.png)]()


GoSensor is a wearable posture coach. This repository conteins code of the one of the first arduino based prototypes

##### HW prerequisites
  - [Arduino nano (or comatible clones)](https://store.arduino.cc/arduino-nano)
  - [LSM6DS33 3D Accelerometer and Gyro](https://www.pololu.com/product/2736)
  - [BLE module](https://www.adafruit.com/product/2479) 
  - [Li-po battery](https://www.adafruit.com/product/1578)
  - [Lithium charge controller](https://www.banggood.com/Micro-USB-TP4056-Charge-And-Discharge-Protection-Module-Over-Current-Over-Voltage-Protection-18650-p-1183439.html?utm_source=google&utm_medium=cpc_ods&utm_content=nancy&utm_campaign=content-sdsrm-india&gclid=Cj0KCQjw4-XlBRDuARIsAK96p3AiNVXg0K-YPiaph6ki88_5qstb3HhPgJNOtkThF3KFCOdh2K6cHi0aAlZ6EALw_wcB&cur_warehouse=CN)

#####  Wiring

  - Import a HTML file and watch it magically convert to Markdown
  - Drag and drop images (requires your Dropbox account be linked)


#####  Code Structure
- I2C.ino  - implements  configuration and getting data from IMU through I2C
- bleConfig.ino - implements configuration of BLE module and setting up of the characteristics
- goSensorArdduino - contains the main code of the firmware
- imuAttributes.h - contains the data structure for data
- output.ino - implements the data formating function and prepare them for sending via BLE
