
void I2C_Init()
{
  Wire.begin();
}

void gyro_init()
{
  // Accel_Init() should have already called gyro_acc.init() and enableDefault()
  sensor.imu.writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale
}

void read_gyro()
{
  sensor.imu.readGyro();
  sensor.gyroX = sensor.imu.g.x;
  sensor.gyroY = sensor.imu.g.y;
  sensor.gyroZ = sensor.imu.g.z;
}

void acc_init()
{
  sensor.imu.init();
  sensor.imu.enableDefault();
  sensor.imu.writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale

}

// Reads x,y and z accelerometer registers
void read_acce()
{
  sensor.imu.readAcc();
  sensor.accX = sensor.imu.a.x;
  sensor.accY = sensor.imu.a.y;
  sensor.accZ = sensor.imu.a.z;
}

void init_sensors()
{
  sensor.imu.init();
  sensor.imu.enableDefault();
  sensor.imu.writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale
  sensor.imu.writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale
}

void read_sensor_data()
{
  sensor.imu.readAcc();
  sensor.accX = sensor.imu.a.x;
  sensor.accY = sensor.imu.a.y;
  sensor.accZ = sensor.imu.a.z;

  sensor.imu.readGyro();
  sensor.gyroX = sensor.imu.g.x;
  sensor.gyroY = sensor.imu.g.y;
  sensor.gyroZ = sensor.imu.g.z;


  


}

