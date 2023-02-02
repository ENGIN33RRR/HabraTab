
void findVAR() {
  if ((WiFi.status() == WL_CONNECTED)) {  //Если есть подключение к Wifi
    http.begin(client, SURL + USER + "/");  //Открываем HTTP соединение
delay(10);
    int httpCode = http.GET(); //Производим GET запрос
    delay(10);
Serial.print("httpCode");
    Serial.println(httpCode);
    if (httpCode==200) {   //Если ответ 200

        WiFiClient* stream = http.getStreamPtr();  //Пребразуем данные в поток Stream

        if (stream->available()) { //Если поток доступен

          //----------------карма
          stream->find(R"rawliteral(karma__votes_positive">)rawliteral");   //Ищем якорь
          for (int i = 0; i < 5; i++) {       //Отступ от якоря
            stream->read();
          }

          for (byte i = 0; i < 5; i++) {     //Читаем нужное количество символов
            KARMA[i] = stream->read();
          }

          //----------------рейтинг

          stream->find(R"rawliteral(tm-rating__counter">)rawliteral");

          for (byte i = 0; i < 7; i++) {
            RATING[i] = stream->read();
          }

          //----------------позиция

          stream->find("В рейтинге");
          for (int i = 0; i < 118; i++) {
            stream->read();
          }

          for (byte i = 0; i < 4; i++) {
            RatingPos[i] = stream->read();
          }


          Serial.println(KARMA);
          Serial.println(RATING);
          Serial.println(RatingPos);
          Serial.println("END");
        }
        delay(10);


        Serial.println();
        Serial.print("[HTTP] connection closed or file end.\n");
      
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    delay(10);
  }
}
