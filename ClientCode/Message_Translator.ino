// On This Algorithm , First We Translate Data To Char Then We Translate It To String Value
DynamicJsonDocument translateMessage(uint8_t *data, size_t len) {
  char jsonChar[len];
  for (int i = 0; i < len; i++) {
    jsonChar[i] = ((char)data[i]);
  }


  DynamicJsonDocument doc(256);
  deserializeJson(doc, String(jsonChar));


  return doc;
}