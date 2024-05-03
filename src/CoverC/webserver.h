#ifndef COVERC_SERVER
#define COVERC_SERVER

void coverCWebServer(){

    server.on("/coverstatus",               HTTP_PUT, [](AsyncWebServerRequest *request) {
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->printf("\"cover\":{ \"value\":");
        response->print(coverC.actualValue);
        response->printf("}}");
    });

    server.on("/covercmd",             HTTP_PUT, [](AsyncWebServerRequest *request) {
        int value = -1;

        if (request->hasParam("value")){ 
            value = request->getParam("value")->value().toInt();
        } else {
            request->send(200, "application/json", "{\"error\" : \"Missing Value\"}");
            return;
        }
        if (value < 0 || value > 8192){
            request->send(200, "application/json", "{\"error\" : \"Out of Range Value\"}");
            return;
        }
        coverC.cmdValue = value;
        request->send(200, "text/html", "{\"done\" : 1}");
    
    });

    AsyncCallbackJsonWebHandler *covercfg = new AsyncCallbackJsonWebHandler("/coverconfig", [](AsyncWebServerRequest * request, JsonVariant & json) {
        JsonDocument doc;
        doc = json.as<JsonObject>();
        if (Config.coverC.pin == doc["pin"]){
            request->send(200, "application/json", "{\"accept\": \"ok\"}");
        } else {
            Config.coverC.pin = doc["pin"];
            Config.save.coverC.execute = true;
            Config.save.coverC.restartNeeded = true;
            request->send(200, "application/json", "{\"reboot\": \"1\"}");
        }
    });
    server.addHandler(covercfg);

    server.serveStatic("/ccalibconfig.txt", SPIFFS, "/ccalibconfig.txt");
}
#endif
