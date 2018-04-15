void generate_packege()
{
  char outputDataset[20];
  sensor.timeStamp = 20;
  
  Serial.print(sensor.timeStamp);
  //Serial.print(" ");
  Serial.print(sensor.accX);
  //Serial.print(" ");
  Serial.print(sensor.accY);
  //Serial.print(" ");
  Serial.print(sensor.accZ);
  //Serial.print(" ");
  Serial.print(sensor.gyroX);
  //Serial.print(" ");
  Serial.print(sensor.gyroY);
  //Serial.print(" ");
  Serial.print(sensor.gyroZ);
  Serial.print('\n');

  snprintf(outputDataset, sizeof(outputDataset), "%i%hi%hi%hi%hi%hi%hi%hi%hi%hi",
  sensor.timeStamp, sensor.accX, sensor.accY, sensor.accZ, sensor.gyroX, sensor.gyroY, sensor.gyroZ);

  //for testing
  Serial.println(outputDataset);
  Serial.println("HERE IS DATA");

  gatt.setChar(sensor.accGyroID, outputDataset);
}
