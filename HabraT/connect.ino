



void Connect(void) {


 WiFi.mode(WIFI_STA);
 delay(10);
  WiFi.begin(ssid, password);
delay(10);
  while (WiFi.status() != WL_CONNECTED && count < 15) {
    count++;
    delay(500);
  }

  delay(10);

}


void Reconnect(void) {

KARMA = "000";
RATING = "000.0";
RatingPos = "999";

  WiFi.disconnect();
  vTaskDelay(1000);
  WiFi.begin(ssid, password);
  count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 15 ) {
    count++;
    delay(500);
   
  }




}
