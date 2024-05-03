#ifndef DOME_SERVER
#define DOME_SERVER


void domeWebServer(){


    server.on("/domestatus",               HTTP_PUT, [](AsyncWebServerRequest *request) {
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->printf("{\"dome\":{ \"actualState\":");
        response->print(Dome.ShutterState);
        response->print(",\"lastCommand\":");
        response->print(Dome.LastDomeCommand);
        response->print("}");
        response->print("}");
    });

    server.on("/domecmd",               HTTP_PUT, [](AsyncWebServerRequest *request) {
        if (request->hasParam("cmd")){
            int cmd;
            cmd = request->getParam("cmd")->value().toInt();
            switch (cmd) {
                case 1:
                    if(Dome.ShutterState != ShOpen){
                    Dome.ShutterCommand = CmdOpen;
                    request->send(200, "application/json", "{\"error\":0}");
                    } else { request->send(200, "application/json", "{\"error\":1}"); }
                    break;

                case 2:
                    if(Dome.ShutterState != ShClose){
                        Dome.ShutterCommand = CmdClose;
                        request->send(200, "application/json", "{\"error\":0}");
                    } else { request->send(200, "application/json", "{\"error\":2}"); }
                    break;

                case 3:
                    Dome.ShutterCommand = CmdHalt;
                    Dome.Cycle = 100;
                    request->send(200, "application/json", "{\"error\":0}");
                    break;
                default:
                    request->send(200, "application/json", "{\"error\":3}");
                    break;
            }
        } else {
            request->send(200, "application/json", "{\"error\":3}");
        }
    });


    AsyncCallbackJsonWebHandler *domecfg = new AsyncCallbackJsonWebHandler("/domeconfig", [](AsyncWebServerRequest * request, JsonVariant & json) {
        JsonDocument doc;
        doc = json.as<JsonObject>();
        bool reboot = false;
        if (Config.dome.pinStart != doc["pinstart"]) {reboot=true;}
        Config.dome.pinStart = doc["pinstart"];
        if (Config.dome.pinHalt != doc["pinhalt"]) {reboot=true;}
        Config.dome.pinHalt = doc["pinhalt"];
        if (Config.dome.pinOpen != doc["pinopen"]) {reboot=true;}
        Config.dome.pinOpen = doc["pinopen"];
        if (Config.dome.pinClose != doc["pinclose"]) {reboot=true;}
        Config.dome.pinClose = doc["pinclose"];
        
        Config.dome.movingTimeOut = doc["tout"];
        Config.dome.enAutoClose = doc["enautoclose"];
        Config.dome.autoCloseTimeOut = doc["autoclose"];
        Config.save.dome.execute = true;
        if (reboot){
            Config.save.dome.restartNeeded = true;
            request->send(200, "application/json", "{\"reboot\": \"1\"}");
        } else {
            request->send(200, "application/json", "{\"accept\": \"ok\"}");
        }
    });
    server.addHandler(domecfg);


    server.serveStatic("/domeconfig.txt", SPIFFS, "/domeconfig.txt");
}

#endif