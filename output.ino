void generate_packege()
{
  char outputDataset[20];
  sensor.timeStamp = 20;

  /*
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
  */

  snprintf(outputDataset, sizeof(outputDataset), "%d%d%d%d%d%d%d",
  highByte(sensor.timeStamp), lowByte(sensor.timeStamp) , highByte(sensor.accX), lowByte(sensor.accX), highByte(sensor.accY), lowByte(sensor.accY), highByte(sensor.accZ), lowByte(sensor.accZ),
  highByte(sensor.gyroX), lowByte(sensor.gyroX), highByte(sensor.gyroY), lowByte(sensor.gyroY), highByte(sensor.gyroZ), lowByte(sensor.gyroZ));
  //sensor.timeStamp, sensor.accX, sensor.accY, sensor.accZ, sensor.gyroX, sensor.gyroY, sensor.gyroZ);

  //for testing
  Serial.println(outputDataset);
  Serial.println(sensor.accGyroID);
  Serial.println("HERE IS DATA");

  gatt.setChar(sensor.accGyroID, outputDataset);
}
