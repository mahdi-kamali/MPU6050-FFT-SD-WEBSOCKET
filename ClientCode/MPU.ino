void startMPU() {


  int connectionTry = 3;
  long sensorCheckTimeDelay = 1000;
  while (connectionTry != 0) {
    if (!mpu.begin(0x69, &I2Cone, 1)) {
      Serial.println("Failed to find MPU6050 chip ( SENSOR 1 )  Try => " + String(connectionTry));
      delay(sensorCheckTimeDelay);
      connectionTry--;
    } else {
      Serial.println(" ---------- MPU6050 chip ( SENSOR 1 ) FINDED !  ");
      sensorOneActive = true;
      break;
    }
  }

  connectionTry = 3;
  while (connectionTry != 0) {
    if (!mpu2.begin(0x68, &I2Cone, 2)) {
      Serial.println("Failed to find MPU6050 chip ( SENSOR 2 )  Try => " + String(connectionTry));
      delay(sensorCheckTimeDelay);
      connectionTry--;
    } else {
      Serial.println(" ---------- MPU6050 chip ( SENSOR 2 ) FINDED !  ");
      sensorTwoActive = true;
      break;
    }
  }


  connectionTry = 3;
  while (connectionTry != 0) {
    if (!mpu3.begin(0x68, &I2Ctwo, 3)) {
      Serial.println("Failed to find MPU6050 chip ( SENSOR 3 )  Try => " + String(connectionTry));
      delay(sensorCheckTimeDelay);
      connectionTry--;
    } else {
      Serial.println(" ---------- MPU6050 chip ( SENSOR 3 ) FINDED !  ");
      sensorThreeActive = true;

      break;
    }
  }


  connectionTry = 3;
  while (connectionTry != 0) {
    if (!mpu4.begin(0x69, &I2Ctwo, 4)) {
      Serial.println("Failed to find MPU6050 chip ( SENSOR 4 )  Try => " + String(connectionTry));
      delay(sensorCheckTimeDelay);
      connectionTry--;
    } else {
      Serial.println(" ---------- MPU6050 chip ( SENSOR 4 ) FINDED !  ");
      sensorFourActive = true;
      break;
    }
  }
}

void getMpuOneData() {


  // Sensor 1   AX




  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu.getEvent(&accel_event, &gyro_event, &temp_event);


    vReal[i] = accel_event.acceleration.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_1_AX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorOneFFT.set_AX(frequency);

  frequency = 0;
  frequencyValue = 0;






  // Sensor 1   AY


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu.getEvent(&accel_event, &gyro_event, &temp_event);

    vReal[i] = accel_event.acceleration.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_1_AY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorOneFFT.set_AY(frequency);

  frequency = 0;
  frequencyValue = 0;





  // Sensor 1   AZ



  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu.getEvent(&accel_event, &gyro_event, &temp_event);

    vReal[i] = accel_event.acceleration.z;
    vImag[i] = 0;

    // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();




    for (int i = 0; i < (SAMPLES / 2); i++) {

      if (vReal[i] > frequencyValue) {
        frequencyValue = vReal[i];
        frequency = i * (float)SAMPLING_FREQ / SAMPLES;
      }
    }

    Serial.print("S_1_AZ(HZ):");
    Serial.print(frequency, 1);  // print frequency with 1 decimal place
    Serial.println("");
    sensorOneFFT.set_AZ(frequency);

    frequency = 0;
    frequencyValue = 0;


    // Sensor 1   GX



    for (int i = 0; i < SAMPLES; i++) {
      sensors_event_t accel_event, gyro_event, temp_event;
      mpu.getEvent(&accel_event, &gyro_event, &temp_event);

      vReal[i] = gyro_event.gyro.x;
      vImag[i] = 0;
    }

    // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();




    for (int i = 0; i < (SAMPLES / 2); i++) {

      if (vReal[i] > frequencyValue) {
        frequencyValue = vReal[i];
        frequency = i * (float)SAMPLING_FREQ / SAMPLES;
      }
    }

    Serial.print("S_1_GX(HZ):");
    Serial.print(frequency, 1);  // print frequency with 1 decimal place
    Serial.println("");
    sensorOneFFT.set_GX(frequency);

    frequency = 0;
    frequencyValue = 0;



    // Sensor 1   GY



    for (int i = 0; i < SAMPLES; i++) {
      sensors_event_t accel_event, gyro_event, temp_event;
      mpu.getEvent(&accel_event, &gyro_event, &temp_event);

      vReal[i] = gyro_event.gyro.y;
      vImag[i] = 0;
    }

    // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();




    for (int i = 0; i < (SAMPLES / 2); i++) {

      if (vReal[i] > frequencyValue) {
        frequencyValue = vReal[i];
        frequency = i * (float)SAMPLING_FREQ / SAMPLES;
      }
    }

    Serial.print("S_1_GY(HZ):");
    Serial.print(frequency, 1);  // print frequency with 1 decimal place
    Serial.println("");
    sensorOneFFT.set_GY(frequency);

    frequency = 0;
    frequencyValue = 0;



    // Sensor 1   GZ



    for (int i = 0; i < SAMPLES; i++) {
      sensors_event_t accel_event, gyro_event, temp_event;
      mpu.getEvent(&accel_event, &gyro_event, &temp_event);

      vReal[i] = gyro_event.gyro.z;
      vImag[i] = 0;
    }

    // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();




    for (int i = 0; i < (SAMPLES / 2); i++) {

      if (vReal[i] > frequencyValue) {
        frequencyValue = vReal[i];
        frequency = i * (float)SAMPLING_FREQ / SAMPLES;
      }
    }

    Serial.print("S_1_GZ(HZ):");
    Serial.print(frequency, 1);  // print frequency with 1 decimal place
    Serial.println("");
    sensorOneFFT.set_GZ(frequency);

    frequency = 0;
    frequencyValue = 0;
  }
}

void getMpuTwoData() {
  // Sensor 2   AX



  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    vReal[i] = accel_event.acceleration.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_2_AX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorTwoFFT.set_AX(frequency);

  frequency = 0;
  frequencyValue = 0;


  // Sensor 2   AY



  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    vReal[i] = accel_event.acceleration.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_2_AY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");

  sensorTwoFFT.set_AY(frequency);


  frequency = 0;
  frequencyValue = 0;



  // Sensor 2   AZ



  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    vReal[i] = accel_event.acceleration.z;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_2_AZ(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorTwoFFT.set_AZ(frequency);


  frequency = 0;
  frequencyValue = 0;


  // Sensor 2   GX


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    vReal[i] = gyro_event.gyro.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_2_GX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorTwoFFT.set_GX(frequency);


  frequency = 0;
  frequencyValue = 0;







  // Sensor 2   GY


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_2_GY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorTwoFFT.set_GY(frequency);

  frequency = 0;
  frequencyValue = 0;



  // Sensor 2   GZ


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.z;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_2_GZ(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorTwoFFT.set_GZ(frequency);

  frequency = 0;
  frequencyValue = 0;
}

void getMpuThreeData() {
  // Sensor 3   AX


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = accel_event.acceleration.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_3_AX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorThreeFFT.set_AX(frequency);

  frequency = 0;
  frequencyValue = 0;



  // Sensor 3   AY


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = accel_event.acceleration.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_3_AY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorThreeFFT.set_AY(frequency);

  frequency = 0;
  frequencyValue = 0;



  // Sensor 3   AZ


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = accel_event.acceleration.z;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_3_AZ(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");

  sensorThreeFFT.set_AZ(frequency);

  frequency = 0;
  frequencyValue = 0;



  // Sensor 3   GX


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_3_GX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorThreeFFT.set_GX(frequency);

  frequency = 0;
  frequencyValue = 0;


  // Sensor 3   GY


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_3_GY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorThreeFFT.set_GY(frequency);


  frequency = 0;
  frequencyValue = 0;



  // Sensor 3   GZ


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.z;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_3_GZ(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorThreeFFT.set_GZ(frequency);


  frequency = 0;
  frequencyValue = 0;
}

void getMpuFourData() {







  // Sensor 4   AX


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = accel_event.acceleration.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_4_AX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorFourFFT.set_AX(frequency);

  frequency = 0;
  frequencyValue = 0;



  // Sensor 4   AY


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = accel_event.acceleration.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_4_AY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorFourFFT.set_AY(frequency);

  frequency = 0;
  frequencyValue = 0;


  // Sensor 4   AZ


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = accel_event.acceleration.z;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_4_AZ(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorFourFFT.set_AZ(frequency);

  frequency = 0;
  frequencyValue = 0;


  // Sensor 4   GX


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.x;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_4_GX(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorFourFFT.set_GX(frequency);

  frequency = 0;
  frequencyValue = 0;


  // Sensor 4   GY


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.y;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_4_GY(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorFourFFT.set_GY(frequency);

  frequency = 0;
  frequencyValue = 0;




  // Sensor 4   GZ


  for (int i = 0; i < SAMPLES; i++) {
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);

    // Serial.print(",");
    vReal[i] = gyro_event.gyro.z;
    vImag[i] = 0;
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();




  for (int i = 0; i < (SAMPLES / 2); i++) {

    if (vReal[i] > frequencyValue) {
      frequencyValue = vReal[i];
      frequency = i * (float)SAMPLING_FREQ / SAMPLES;
    }
  }

  Serial.print("S_4_GZ(HZ):");
  Serial.print(frequency, 1);  // print frequency with 1 decimal place
  Serial.println("");
  sensorFourFFT.set_GZ(frequency);


  frequency = 0;
  frequencyValue = 0;
}




void sendMpuesFFTToServer() {

  DynamicJsonDocument doc(2048);


  doc["type"] = RESPONSE_TYPE_MPU_FFT;
  doc["name"] = ESP_NAME;


  int i = 0;

  if (sensorOneActive || true) {
    doc["data"][i]["sensorName"] = "Sensor_1";
    doc["data"][i]["ax"] = sensorOneFFT.get_AX();
    doc["data"][i]["ay"] = sensorOneFFT.get_AY();
    doc["data"][i]["az"] = sensorOneFFT.get_AZ();
    doc["data"][i]["gx"] = sensorOneFFT.get_GX();
    doc["data"][i]["gy"] = sensorOneFFT.get_GY();
    doc["data"][i]["gz"] = sensorOneFFT.get_GZ();
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu.getEvent(&accel_event, &gyro_event, &temp_event);
    doc["data"][i]["temp"] = temp_event.temperature;
    i++;
  }
  if (sensorTwoActive) {
    doc["data"][i]["sensorName"] = "Sensor_2";
    doc["data"][i]["ax"] = sensorTwoFFT.get_AX();
    doc["data"][i]["ay"] = sensorTwoFFT.get_AY();
    doc["data"][i]["az"] = sensorTwoFFT.get_AZ();
    doc["data"][i]["gx"] = sensorTwoFFT.get_GX();
    doc["data"][i]["gy"] = sensorTwoFFT.get_GY();
    doc["data"][i]["gz"] = sensorTwoFFT.get_GZ();
    sensors_event_t accel_event, gyro_event, temp_event;
    mpu2.getEvent(&accel_event, &gyro_event, &temp_event);
    doc["data"][i]["temp"] = temp_event.temperature;
    i++;

  }
  if (sensorThreeActive) {
    doc["data"][i]["sensorName"] = "Sensor_3";
    doc["data"][i]["ax"] = sensorThreeFFT.get_AX();
    doc["data"][i]["ay"] = sensorThreeFFT.get_AY();
    doc["data"][i]["az"] = sensorThreeFFT.get_AZ();
    doc["data"][i]["gx"] = sensorThreeFFT.get_GX();
    doc["data"][i]["gy"] = sensorThreeFFT.get_GY();
    doc["data"][i]["gz"] = sensorThreeFFT.get_GZ();
    doc["data"][i]["temp"] = "Temp";
    i++;

  }
  if (sensorFourActive) {
    doc["data"][i]["sensorName"] = "Sensor_4";
    doc["data"][i]["ax"] = sensorFourFFT.get_AX();
    doc["data"][i]["ay"] = sensorFourFFT.get_AY();
    doc["data"][i]["az"] = sensorFourFFT.get_AZ();
    doc["data"][i]["gx"] = sensorFourFFT.get_GX();
    doc["data"][i]["gy"] = sensorFourFFT.get_GY();
    doc["data"][i]["gz"] = sensorFourFFT.get_GZ();
    doc["data"][i]["temp"] = "Temp";
    i++;

  }


  String temp;
  serializeJson(doc, temp);

  webSocket.sendTXT(temp);
}