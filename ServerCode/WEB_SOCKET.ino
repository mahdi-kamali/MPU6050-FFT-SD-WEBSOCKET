


void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {

  DynamicJsonDocument doc = translateMessage(data, len);

  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
    
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}


void notifyClients() {
  ws.textAll(String(ledState));
}

String processor(const String &var) {
  Serial.println(var);
  if (var == "STATE") {
    if (ledState) {
      return "ON";
    } else {
      return "OFF";
    }
  }
  return String();
}


void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", "Alive", processor);
  });


  // Start server
  server.begin();
}