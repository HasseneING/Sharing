#include <ArduinoJson.h>

/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

//const char* ssid = "Fixbox-71E048";
//const char* password = "MDI4MmNk";


const char* ssid = "blocc1";
const char* password = "";


//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.0.3:8082/candidats";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String sensorReadings;
String sensorReadingsArr[3];

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      sensorReadings = httpGETRequest(serverName);
      Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var  
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      //Serial.println(myObject);
      Serial.println(myObject["_embedded"]["candidats"]);
      //Serial.println(myObject.keys().keys());

String input=sensorReadings;

StaticJsonDocument<1536> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

for (JsonObject embedded_candidats_item : doc["_embedded"]["candidats"].as<JsonArray>()) {

  const char* embedded_candidats_item_nom = embedded_candidats_item["nom"]; // "Mariem", "Sarra", ...
  // embedded_candidats_item["prenom"] is null
  // embedded_candidats_item["email"] is null

  const char* embedded_candidats_item_links_self_href = embedded_candidats_item["_links"]["self"]["href"];

  const char* embedded_candidats_item_links_candidat_href = embedded_candidats_item["_links"]["candidat"]["href"];

  Serial.println(embedded_candidats_item_nom);

}

JsonObject links = doc["_links"];

const char* links_self_href = links["self"]["href"]; // "http://192.168.0.3:8082/candidats"

const char* links_profile_href = links["profile"]["href"];

const char* links_search_href = links["search"]["href"]; // "http://192.168.0.3:8082/candidats/search"

JsonObject page = doc["page"];
int page_size = page["size"]; // 20
int page_totalElements = page["totalElements"]; // 3
int page_totalPages = page["totalPages"]; // 1
int page_number = page["number"]; // 0



    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
