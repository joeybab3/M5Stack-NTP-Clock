#include <WiFi.h>
#include <SPI.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid     = "NETGEAR45";
const char* password = "orangeflower393";

String formattedDate;
String dayStamp;
String timeStamp;

#define NTP_OFFSET  -28798 // In seconds for los angeles/san francisco time zone
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "pool.ntp.org"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
#include <M5Stack.h>

#define TFT_GREY 0x5AEB

unsigned int colour = 0;

void setup(void) {
  Serial.begin(115200);
  M5.begin();
  // M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextSize(6);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
}

void loop() {
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  
  String dateStamp = formattedDate.substring(0, splitT);
  String dayStamp = formattedDate.substring(splitT-2, splitT);
  String monthStamp = formattedDate.substring(splitT-5, splitT-3);
  String yearStamp = formattedDate.substring(0, 4);
  String yearStampSmall = formattedDate.substring(2, 4);
  String timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  String hourStamp = timeStamp.substring(0,2);
  String minuteStamp = timeStamp.substring(3,5);
  String secondStamp = timeStamp.substring(6,8);

  int year = yearStamp.toInt();
  int month = monthStamp.toInt();
  int day = dayStamp.toInt();
  int hour = hourStamp.toInt();
  int minute = minuteStamp.toInt();
  int second = secondStamp.toInt();

  boolean isPm = false;
  
  int hourNoMilitary;
  
  if(hour > 12)
  {
    hourNoMilitary = hour - 12;
    isPm = true;
  }
  else
  {
    isPm = false;
    hourNoMilitary = hour;
  }
  String hourStampNoMilitary = (String)hourNoMilitary;
  if(hourNoMilitary < 10)
  {
    hourStampNoMilitary = "0"+hourNoMilitary;
  }

  int daysLeft = 0;
  int monthsLeft = 0;

  String timeStampNoMilitary = hourStampNoMilitary + ":" + minuteStamp + ":" + secondStamp;    //hh:mm:ss
  String dateStampConstructed = monthStamp + "/" + dayStamp + "/" + yearStampSmall;  //mm/dd/yy
  
  M5.Lcd.setTextSize(6);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.print(dateStampConstructed);
  M5.Lcd.println(timeStampNoMilitary);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(290, 60);
  if(isPm)
  {
    M5.Lcd.println("PM");
  }
  else
  {
    M5.Lcd.println("AM");
  }
  delay(950);
}
