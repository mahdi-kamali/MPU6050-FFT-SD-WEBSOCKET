bool sendConnectionJson() {
  DynamicJsonDocument doc(50);
  doc["type"] = REQUEST_TYPE_CONNECTION;
  doc["userName"] = "Admin";
  doc["password"] = "Admin";
  String jsonMessage;
  serializeJson(doc, jsonMessage);
  return sendJSON(jsonMessage);
}

bool sendMicroControllerInfo() {
  DynamicJsonDocument doc(50);
  doc["type"] = REQUEST_TYPE_CHIP_INFO;
}

bool sendMessage(String data) {
  DynamicJsonDocument doc(256);
  doc["type"] = REQUEST_TYPE_MESSAGE;
  doc["message"] = data;
  String temp;
  serializeJson(doc, temp);
  return sendJSON(temp);
}


bool sendGetValue(int pinNumber, String mode) {
  DynamicJsonDocument doc(126);
  doc["type"] = REQUEST_TYPE_GET;
  doc["pin"] = pinNumber;
  doc["method"] = "get";
  doc["mode"] = "analog";
  doc["repeat"] = 999;  // Infinite
  String jsonString;
  serializeJson(doc, jsonString);
  return sendJSON(jsonString);
}