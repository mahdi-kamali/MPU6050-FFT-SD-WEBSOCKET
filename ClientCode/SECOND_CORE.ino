
void initTaksCoreTwo() {
  xTaskCreatePinnedToCore(
    TaskTwoCode, /* Function to implement the task */
    "Task2",     /* Name of the task */
    10000,       /* Stack size in words */
    NULL,        /* Task input parameter */
    0,           /* Priority of the task */
    &Task2,      /* Task handle. */
    0);          /* Core where the task should run */
}