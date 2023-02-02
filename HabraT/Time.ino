
void setTime (){

  sntp_set_time_sync_notification_cb(timeavailable);

 configTime(gmtOffset_sec, 0, ntpServer1, ntpServer2);
  
}


void updLocalTime()
{
  struct tm timeinfo;
getLocalTime(&timeinfo);
strftime(TimeDisp,9, "%H:%M:%S", &timeinfo);
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
 // Serial.println("Got time adjustment from NTP!");
//  printLocalTime();
}
