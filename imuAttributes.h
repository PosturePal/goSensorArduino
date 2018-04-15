#include <LSM6.h>

struct lsm6d_sensor
{
  uint8_t accGyroUUID[16];
  uint8_t accGyroID; 
  uint8_t timeStamp;

  int gyroX;
  int gyroY;
  int gyroZ;

  int accX;
  int accY;
  int accZ;
  

  LSM6 imu
}
