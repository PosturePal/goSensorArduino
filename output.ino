void generate_packege()
{
  char outputDataset[20];

  sprintf(outputDataset, sizeof(outputDataset), "%d, %d %d %d, %d %d %d, %d %d %d",
  sensor.timeStamp, sensor.accX, sensor.accY, sensor.accZ, sensor.gyroX, sensor.gyroY, sensor.gyroZ);

  //for testing
  Serial.println(outputDataset);

  gatt.setChar(sensor.accGyroID, outputDataset);
}
