
void Static() {

  display.setFont(&FreeMonoBold12pt7b);
  display.fillRect(0, 0, 296, 20, GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(10, 16);
  display.print("HabraTab");
 display.fillRect(10, 80, 276, 2, GxEPD_BLACK);
display.fillRect(15, 50, 73, 2, GxEPD_BLACK);
display.fillRect(103, 50, 90, 2, GxEPD_BLACK);
display.fillRect(208, 50, 73, 2, GxEPD_BLACK);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(18, 72);
  display.print("Karma");
  display.setCursor(115, 72);
  display.print("Score");
  display.setCursor(215, 72);
 display.print("R No");
 display.setFont(&FreeSerifBoldItalic18pt7b);
 display.fillRect(15, 22, 100, 26, GxEPD_WHITE);
  display.setCursor(15, 45);
  display.print(KARMA.toInt());
  display.fillRect(110, 22, 100, 26, GxEPD_WHITE);
  display.setCursor(110, 45);
  display.print(RATING.toFloat(), 1);
  display.fillRect(220, 22, 85, 26, GxEPD_WHITE);
  display.setCursor(220, 45);
  display.print(RatingPos.toInt());
display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(5, 100);
  display.print("@");
  display.print(USER);
  display.setTextColor(GxEPD_BLACK);
display.fillRect(0, 108, 296, 20, GxEPD_BLACK);

}


void Dynamic() {


 display.setFont(&FreeMonoBold12pt7b);
    display.fillRect(145, 0, 150, 20, GxEPD_BLACK);



    

    if (!noWiFi || blink) {
      display.fillCircle(148, 9, 3, GxEPD_WHITE);
      display.fillRect(156, 6, 2, 8, GxEPD_WHITE);

      if (WS == 1) {

        display.fillRect(162, 4, 2, 12, GxEPD_WHITE);
      }
      if (WS == 2) {
        display.fillRect(162, 4, 2, 12, GxEPD_WHITE);
        display.fillRect(168, 2, 2, 16, GxEPD_WHITE);
      }
    }
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(175, 16);
    display.print(TimeDisp);
    vTaskDelay(1);


    if (flag) {

      display.setFont(&FreeSerifBoldItalic18pt7b);
      display.setTextColor(GxEPD_BLACK);
      display.fillRect(15, 22, 95, 26, GxEPD_WHITE);
      display.setCursor(15, 45);
      display.print(KARMA.toInt());
      display.fillRect(110, 22, 95, 26, GxEPD_WHITE);
      display.setCursor(110, 45);
      display.print(RATING.toFloat(), 1);
      display.fillRect(220, 22, 76, 26, GxEPD_WHITE);
      display.setCursor(220, 45);
      display.print(RatingPos.toInt());
      flag = 0;
    }

    display.setFont(&FreeMonoBold12pt7b);
    display.fillRect(0, 108, 200, 20, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(10, 124);
    vTaskDelay(1);
    display.print("T");
   
      display.print(Temp, 1);
    
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(82, 118);
    display.print("o");
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(120, 124);
    display.print("H");
  
      display.print(Hum, 1);
      display.print("%");
    
    vTaskDelay(10);
    display.display(true);
    vTaskDelay(10);


}

