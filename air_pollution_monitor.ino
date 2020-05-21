/**
 * Code for the Article  http://www.gumino.com/air-pollution-monitor-1/
 */
#include <M5Stack.h>

// buffer to store the SDS011 message
byte buffer[10] = {};

// Struct to keep calculated PM2.5 and PM10 values
struct AirQualityData {
  float pm25;
  float pm10;
} airQuality;

// Marker byte for SDS011 message end
byte DATA_END_MARK = 0xAB;

void setup() {
  M5.begin();
  Serial.begin(115200);

  // Serial2 bound on M5Stack pin 16 and 17 (UART RX and TX)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  memset(buffer, 0, sizeof(buffer));
  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextSize(3);
}


void loop() {

 if(Serial2.available()) {
   Serial2.readBytesUntil(DATA_END_MARK, buffer, 10);
   readAirQuality();      
   displayAirQuality();
 }
}


void readAirQuality() {
  airQuality.pm25 = (buffer[3] * 256 + buffer[2]) / 10.0;
  airQuality.pm10 = (buffer[5] * 256 + buffer[4]) / 10.0;
}

void displayAirQuality() {
  M5.Lcd.clear(WHITE);
  M5.Lcd.setCursor(5, 10);
  M5.Lcd.printf("PM2.5 %.2f ug/m3",airQuality.pm25);
  M5.Lcd.setCursor(5, 40);
  M5.Lcd.printf("PM10  %.2f ug/m3",airQuality.pm10);
}
  
