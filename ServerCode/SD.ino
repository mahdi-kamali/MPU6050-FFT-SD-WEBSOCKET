void initSdCart() {
  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CHIP_SELECT)) {
    digitalWrite(2, HIGH);
    Serial.println("SD card initialization failed!");
    delay(200);
    digitalWrite(2, LOW);
  } else {
    Serial.println("SD card initialized.");
  }



  String mpuHeader = "Sensor Name, Date, Time, AX, AY, AZ, GX, GY,GZ, Temperature (°C)";

  // setDataCsvHeaders("/Sensor_1.csv ", mpuHeader);
  // setDataCsvHeaders("/Sensor_2.csv ", mpuHeader);
  // setDataCsvHeaders("/Sensor_3.csv ", mpuHeader);
  // setDataCsvHeaders("/Sensor_4.csv ", mpuHeader);

  delay(2000);
}




void setDataCsvHeaders(String fileName, String fileHeaderString) {
  dataFile = SD.open(fileName, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Failed to create file!");
    return;
  }
  dataFile.println(fileHeaderString);
  dataFile.close();
}


void checkDataCsvHeaders(String espName, String sensorName) {


  String fileName = "/" + espName + "/" + sensorName + ".csv";
  bool fileExist = SD.exists(fileName);

  if (fileExist) {
    // Serial.println("Exist");
  } else {
    if (SD.mkdir("/" + espName)) {
      // Serial.println("folder Created With Name => " + espName);
      dataFile = SD.open(fileName, FILE_WRITE);
      if (dataFile) {
        Serial.println("File Created With Name => " + fileName);
        dataFile.print("Date");
        dataFile.print(",");
        dataFile.print("Time");
        dataFile.print(",");
        dataFile.print("ax");
        dataFile.print(",");
        dataFile.print("ay");
        dataFile.print(",");
        dataFile.print("az");
        dataFile.print(",");
        dataFile.print("gx");
        dataFile.print(",");
        dataFile.print("gy");
        dataFile.print(",");
        dataFile.print("gz");
        dataFile.print(",");
        dataFile.print("temp");
        dataFile.println();
        dataFile.close();
      } else {
        // Serial.println("File Creating Failed !");
      }

    } else {
      // Serial.println("Error With Creating Folder !");
    }
  }
}


void saveToSDCard(String espName, String sensorName, String data) {



  String fileName = "/" + espName + "/" + sensorName + ".csv";


  dataFile = SD.open(fileName, FILE_APPEND);



  if (dataFile) {
    dataFile.print(currentTime.year());
    dataFile.print("-");
    dataFile.print(currentTime.month());
    dataFile.print("-");
    dataFile.print(currentTime.day());
    dataFile.print(",");
    dataFile.print(currentTime.hour());
    dataFile.print(":");
    dataFile.print(currentTime.minute());
    dataFile.print(":");
    dataFile.print(currentTime.second());
    dataFile.print(",");
    dataFile.println(data);
  } else {
    Serial.println("Error !");
  }

  dataFile.close();
}


// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
// void appendFile(fs::FS &fs, const char * path, const char * message) {
//   Serial.printf("Appending to file: %s\n", path);

//   File file = fs.open(path, FILE_APPEND);
//   if(!file) {
//     Serial.println("Failed to open file for appending");
//     return;
//   }
//   if(file.print(message)) {
//     Serial.println("Message appended");
//   } else {
//     Serial.println("Append failed");
//   }
//   file.close();
// }
