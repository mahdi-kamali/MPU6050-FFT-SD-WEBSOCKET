void initWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected ! ");
  Serial.println(WiFi.localIP());
}



void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {

  DynamicJsonDocument doc = translateMessage(payload, length);

  switch (type) {
    case WStype_DISCONNECTED:
      {
        Serial.println(" Server Closed Connection! ");
        Serial.println("");
        Serial.println("");
        allowedToSend = false;
        delay(5000);
        break;
      }

    case WStype_CONNECTED:
      {
        sendConnectionJson();
        delay(1000);
      }
      break;
    case WStype_TEXT:
      {
        hanldeServerResponse(doc);
      }
      break;
    case WStype_BIN:


      break;
    case WStype_PING:
      Serial.printf("[WSc] get ping\n");
      break;
    case WStype_PONG:
      // answer to a ping we send
      Serial.printf("[WSc] get pong\n");
      break;
  }
}

void initWebSocket() {

  // while (webSocket.isConnected() == false) {
  //   String SERVER_IP_ADDRESS = Serial.readString();
  //   SERVER_IP_ADDRESS.trim();
  //   Serial.println(SERVER_IP_ADDRESS);
  //   Serial.println(SERVER_IP_ADDRESS.length());
  //   if (SERVER_IP_ADDRESS.length() > 7) {
  //     Serial.println(" Attempting To Connect Ip => " + SERVER_IP_ADDRESS);
  //     delay(4000);
  //     webSocket.begin(SERVER_IP_ADDRESS, 80, "/ws");
  //     webSocket.onEvent(webSocketEvent);
  //     if (webSocket.isConnected()) {
  //       Serial.println("Connected");
  //     }
  //     break;
  //   }
  //   // delay(5000);
  // }

  // server address, port and URL
  // webSocket.begin(SERVER_IP_ADDRESS, 80, "/ws");

  webSocket.begin(SERVER_IP_ADDRESS, 80, "/ws");

  Serial.println("");
  webSocket.onEvent(webSocketEvent);


  webSocket.setReconnectInterval(1000);
  // webSocket.enableHeartbeat(60000, 3000, 2);
}