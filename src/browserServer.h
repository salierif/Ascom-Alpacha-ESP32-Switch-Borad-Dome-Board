#ifndef BROWSER_WEB
#define BROWSER_WEB

void notFound(AsyncWebServerRequest *request) {
  request->send(400, "text/plain", "Not found");
  Serial.println("400");
  Serial.println(request->url());
}


void browserServer(){

    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/setup", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/setup.html", "text/html");
    });

    server.on("/setup.txt", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/setup.txt", "text/plain");
    });

    server.on("/status",                HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->printf("{");
        response->printf("\"dome\":");
        #ifdef DOME
            response->printf("1");
        #else
            response->printf("0");
        #endif
            response->printf(",\"switch\":");
        #ifdef SWITCH
            response->printf("1");
        #else
            response->printf("0");
        #endif
                response->printf(",\"cover\":");
        #ifdef COVERC
            response->printf("1");
        #else
            response->printf("0");
        #endif
        response->printf(",\"freeHeap\":");
        response->print(ESP.getFreeHeap());
        response->printf(",\"minFreeHeap\":");
        response->print(ESP.getMinFreeHeap());
        response->printf(",\"totalHeap\":");
        response->print(ESP.getHeapSize());
        response->printf(",\"upTime\":");
        response->print(Global.esp32.upTime.minutes);
        response->printf(",\"upWiFiTime\":");
        response->print(Global.wifi.upTime.minutes);
        response->print("}");
        request->send(response);
    });

    server.on("/get-config",                HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->print("{");
        response->printf("\"dome\":");
        #ifdef DOME
            response->printf("1");
        #else
            response->printf("0");
        #endif
            response->printf(",\"switch\":");
        #ifdef SWITCH
            response->printf("1");
        #else
            response->printf("0");
        #endif
                response->printf(",\"cover\":");
        #ifdef COVERC
            response->printf("1");
        #else
            response->printf("0");
        #endif
        response->printf(",\"alpRemPort\":");
        response->print(Config.alpacaPort.remotePort);
        response->printf(",\"alpPort\":");
        response->print(Config.alpacaPort.alpacaPort);
        response->print("}");
        request->send(response);
    });

    AsyncCallbackJsonWebHandler *boardcfg = new AsyncCallbackJsonWebHandler("/set-config", [](AsyncWebServerRequest * request, JsonVariant & json) {
        JsonDocument doc;
        doc = json.as<JsonObject>();
        
        request->send(200, "application/json", "{\"reboot\": \"1\"}");
        
    });
    server.addHandler(boardcfg);

    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico").setCacheControl("max-age=31536000");
    server.serveStatic("/assets/", SPIFFS, "/assets/").setCacheControl("max-age=31536000");

    server.onNotFound(notFound);
}

#endif