void hanldeServerResponse(DynamicJsonDocument doc) {
  Serial.println(" ==== SERVER MESSAGE => " + String(SERVER_IP_ADDRESS) + " ==== ");



  int type = doc["type"];

  switch (type) {
    case RESPONSE_TYPE_MESSAGE:
      {
        String message = doc["message"];
        Serial.println(message);
        break;
      }
    case RESPONSE_TYPE_CONNECTION:
      {
        String response = doc["response"];
        if (response == "Accepted") {
          allowedToSend = true;
          Serial.println("Server Accepted Connection");
        } else {
          Serial.println(" Server Refused From Connection ");
          String errorMessage = doc["error"];
          Serial.println(" Error Message => " + errorMessage);
          allowedToSend = false;
        }
        break;
      }
    case RESPONSE_TYPE_GET:
      {
        int pin = doc["pin"];
        int value = doc["value"];
        Serial.println(" Pin ( " + String(pin) + " ) Value => " + String(value));
      }
  }
  Serial.println(" ==== END MESSAGE  ==== ");
  Serial.println("");
}