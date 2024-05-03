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
        int i;
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->printf("{");
        #ifdef DOME
        response->printf("\"dome\":{ \"actualState\":");
            response->print(Dome.ShutterState);
            response->print(",\"lastCommand\":");
            response->print(Dome.LastDomeCommand);
        response->print("},");
        #endif

        #ifdef COVERC
        response->printf("\"cover\":{ \"value\":");
            response->print(coverC.actualValue);
        response->print("},");
        #endif
        response->printf("\"freeHeap\":");
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

    server.on("/config",                HTTP_GET, [](AsyncWebServerRequest *request) {
        int i;
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->print("{");
        #ifdef DOME
        response->print("\"dome\":{ \"pinstart\":");
        response->print(Config.dome.pinStart);
        response->print(",\"pinhalt\":");
        response->print(Config.dome.pinHalt);
        response->print(",\"pinopen\":");
        response->print(Config.dome.pinOpen);
        response->print(",\"pinclose\":");
        response->print(Config.dome.pinClose);
        response->print(",\"tout\":");
        response->print(Config.dome.movingTimeOut);
        response->print(",\"enautoclose\":");
        Config.dome.enAutoClose ? response->print("true") : response->print("false");
        response->print(",\"autoclose\":");
        response->print(Config.dome.autoCloseTimeOut);
        response->print("}");
        #endif
        #ifdef COVERC
        response->print(",");
        response->print("\"cover\":{ \"pin\":");
        response->print(Config.coverC.pin);
        response->print("}");
        #endif
        #ifdef SWITCH
        response->print(",");
        response->print("\"switches\":[");
        for(i=0;i<Config.switches.configuredSwitch;i++){
            response->print("{\"name\":\"");
            response->print(Switch[i].Name);
            response->print("\",\"desc\":\"");
            response->print(Switch[i].Description);
            response->print("\",\"type\":");
            response->print(Switch[i].property.type);
            response->print(",\"pin\":");
            response->print(Switch[i].pin);
            response->print("}");
            if (i != Config.switches.configuredSwitch - 1 ){
                response->print(",");
            }
        }    
        response->print("]");
        #endif
        response->print("}");
        request->send(response);
    });


    #ifdef COVERC

    #endif
    server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico").setCacheControl("max-age=31536000");
    server.serveStatic("/assets/", SPIFFS, "/assets/").setCacheControl("max-age=31536000");

    server.onNotFound(notFound);
}

#endif