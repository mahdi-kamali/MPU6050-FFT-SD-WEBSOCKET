void handleClientMessage(DynamicJsonDocument doc) {

  int type = doc["type"];

  switch (type) {
    case RESPONSE_TYPE_MPU_FFT:
      {


        String espName = doc["name"];
        String data = doc["data"];



        JsonArray array = doc["data"].as<JsonArray>();


        for (JsonVariant v : array) {
          String sensorName = v["sensorName"];
          String ax = v["ax"];
          String ay = v["ay"];
          String az = v["az"];
          String gx = v["gx"];
          String gy = v["gy"];
          String gz = v["gz"];
          String temp = v["temp"];

          String data = ax + "," + ay + "," + az + "," + gx + "," + gy + "," + gz + "," + temp;
          checkDataCsvHeaders(espName, sensorName);
          saveToSDCard(espName, sensorName, data);
        }
        break;
      }
  }
}