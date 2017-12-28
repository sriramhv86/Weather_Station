//Weather reporter

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>

// WiFi Parameters
const char* ssid = "ssid";
const char* password = "passwd";

String url;
String resource = "http://api.openweathermap.org/data/2.5/weather?q=";
String city_country;
String apid = "AAPID";
//const char url_complete;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  //Uncomment the following lines if you need the update for a city continuously.
 /* Serial.println("Enter the city,country(Please enter a comma in between City and Country. Format Example: Heidelberg,DE):");
  while(Serial.available() < 2)delay(10);
  city_country = Serial.readString();
  Serial.println(city_country);
  url = resource + city_country + apid;
  //Serial.println(url);*/
  
}

void loop() {

    
      Serial.println("Enter the city,country(Please enter a comma in between City and Country. Format Example: Heidelberg,DE):");
      while(Serial.available() < 2)delay(10);
      city_country = Serial.readString();
      //Serial.println(city_country);
      url = resource + city_country + apid;
      // Check WiFi Status
      if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;  //Object of class HTTPClient
      http.begin(url);
      int httpCode = http.GET();
      //Check the returning code                                                                  
      if (httpCode > 0) {
      // Parsing
      const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 400;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      // Parameters
      float coord_lon = root["coord"]["lon"]; // 77.59
      float coord_lat = root["coord"]["lat"]; // 12.98

      JsonObject& weather0 = root["weather"][0];
      int weather0_id = weather0["id"]; // 800
      const char* weather0_main = weather0["main"]; // "Clear"
      const char* weather0_description = weather0["description"]; // "clear sky"
      const char* weather0_icon = weather0["icon"]; // "01n"
      
      const char* base = root["base"]; // "stations"
      
      JsonObject& main = root["main"];
      float main_temp = main["temp"]; // 293.68
      int main_pressure = main["pressure"]; // 1016
      int main_humidity = main["humidity"]; // 60
      float main_temp_min = main["temp_min"]; // 293.15
      float main_temp_max = main["temp_max"]; // 294.15
      
      int visibility = root["visibility"]; // 6000
      
      float wind_speed = root["wind"]["speed"]; // 2.1
      int wind_deg = root["wind"]["deg"]; // 70
      
      int clouds_all = root["clouds"]["all"]; // 0
      
      long dt = root["dt"]; // 1514385000
      
      JsonObject& sys = root["sys"];
      int sys_type = sys["type"]; // 1
      int sys_id = sys["id"]; // 7823
      float sys_message = sys["message"]; // 0.0038
      const char* sys_country = sys["country"]; // "IN"
      long sys_sunrise = sys["sunrise"];
      long sys_sunset = sys["sunset"];
      
      long id = root["id"]; // 1277333
      const char* name = root["name"];
      int cod = root["cod"];
      float maintemp = main_temp - 273;
      Serial.println(" ");
      Serial.print(name);
      Serial.print(": ");
      Serial.print("Temperature = ");
      Serial.print(maintemp); 
      Serial.print("˚Celcius");
      Serial.print(", Humidity = ");
      Serial.print(main_humidity); 
      Serial.print("% ,");
      Serial.println(weather0_description); 
      Serial.println(" ");
    }
    http.end();   //Close connection
  }
  // Delay
  delay(1000);
}
