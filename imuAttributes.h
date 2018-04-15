#include <LSM6.h>

struct _lsm6d_sensor
{
  uint8_t accGyroUUID[16];
  uint8_t accGyroID; 
  int timeStamp;  

  short gyroX;
  short gyroY;
  short gyroZ;


  short accX;
  short accY;
  short accZ;

  LSM6 imu;
};

typedef  _lsm6d_sensor lsm6d_sensor;
