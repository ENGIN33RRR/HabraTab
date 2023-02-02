



String USER = "ENGIN33RRR";  //Имя пользователя
const char ssid[] = "Eng";   //SSID
const char password[] = "123456789h";  //Пароль от WiFi

const char* ntpServer1 = "pool.ntp.org";  //Первый сервер времени
const char* ntpServer2 = "time.nist.gov"; //Второй сервер времени
const long gmtOffset_sec = 21600;         //Часовой пояс в секундах


String SURL = "https://habr.com/ru/users/"; //Начало адреса до страницы пользователя




//LОбъявляем Дисплей
#include <GxEPD2_BW.h>
#define USE_VSPI_FOR_EPD
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define MAX_DISPLAY_BUFFER_SIZE 65536ul       
#define GxEPD2_DRIVER_CLASS GxEPD2_290_T94_V2  
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=*/5, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));




//Шрифты
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSerifBoldItalic18pt7b.h>














//Библиотеки Wifi, HTTP и времени
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
WiFiClientSecure client;

#include <HTTPClient.h>
HTTPClient http;


#include "time.h"
#include "sntp.h"





//Библиотека для датчика темпреатуры/влажности
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 27     
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);





//Переменные для хранения данных и фиксации изменений
String KARMA = "000";
String RATING = "000.0";
String RatingPos = "999";

String KARMA1;
String RATING1;
String RatingPos1;

float Temp;
float Hum;

float HumR;
float TempR;


char TimeDisp[9];

byte count;
bool flag;

long ms;
long ms1;
bool blink;
bool noWiFi;
byte WS;


void setup() {

  xTaskCreatePinnedToCore(
    Graph,   //Функция потока
    "Task2", //Название потока
    16000,   //Стек потока
    NULL,    //Параметры потока
    1,       //Приоритет потока
    NULL,  //Идентифкатор потока
    0);      //Ядро для выполнения потока


  delay(500);

  xTaskCreatePinnedToCore(
    FileUpdate, //Функция потока
    "Task1",    //Название потока
    10000,      //Стек потока
    NULL,       //Параметры потока
    2,          //Приоритет потока
    NULL,     //Идентифкатор потока
    1);         //Ядро для выполнения потока

  delay(500);
}




void FileUpdate(void* pvParameters) {
 Serial.begin(115200);             //Инициализация UART
  //http.setReuse(true);            
  http.setTimeout(3000);
 http.setReuse(true);

 Connect();  //Подключаемся к WiFi

  client.setInsecure(); //Игнорируем сертификаты HTTPS

  for (;;) //Цикл потока
  {

    if (WiFi.status() == WL_CONNECTED) {  //Если есть подключение

      if (WiFi.RSSI() > -60) {    //переводим уровень сигнала для значка
        WS = 2;
      } else if (WiFi.RSSI() > -70) {
        WS = 1;
      } else {
        WS = 0;
      }
      noWiFi = 0;
     
      findVAR();  //Функция поиска значений
    } else {
      Reconnect();   //Переподключить Wifi
      noWiFi = 1;     
    }



    if (!KARMA1.equals(KARMA) || !RATING1.equals(RATING) || !RatingPos1.equals(RatingPos)) {  //Детектируем изменения в переменных
      KARMA1 = KARMA;
      RATING1 = RATING;
      RatingPos1 = RatingPos;
      flag = 1;             //И поднимаем флаг
    }

    vTaskDelay(20000);    //Пауза 20 секунд
  }
}



void Graph(void* pvParameters) {     //Поток отрисовки на дисплей

  configTime(gmtOffset_sec, 0, ntpServer1, ntpServer2); //Инициализируем службу времени
  dht.begin();       //Инициализируем датчик температуры
  display.init();    //Инициализируем дисплей
  display.setRotation(3); 
  display.clearScreen(); //Очистка экрана
  display.setTextColor(GxEPD_BLACK);
  display.fillScreen(GxEPD_WHITE);
  Static(); // Отрисовка статического изображения
  display.display(false);  //Полный вывод на дисплей


  for (;;) {   //Цикл потока отрисовки на дисплей

    updLocalTime(); //Обновляем время в переменной

    if (millis() > ms + 1000) {  //Обновляем показания датчика раз в секунду
 
      ms = millis();
      HumR = dht.readHumidity();
      TempR = dht.readTemperature();
    }

    if (!isnan(HumR) || !isnan(TempR)) { //Если значения не NAN, копируем в перменные
      Hum = HumR;
      Temp = TempR;
    }

if (millis() > ms1 + 1000) {  //Моргалка для потери WiFi
  ms1=millis();
      blink = !blink;
    }

  
   Dynamic(); // Функция отрисовки меняющихся данных
    
  }
}






void loop() { //Не используется
}