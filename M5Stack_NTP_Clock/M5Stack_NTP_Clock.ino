#include <WiFi.h>
#include <SPI.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid     = "NETGEAR45";
const char* password = "orangeflower393";

#define NTP_OFFSET  19800 // In seconds 
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

  M5.Lcd.setTextSize(1);
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

  M5.Lcd.print(formattedTime);
}
