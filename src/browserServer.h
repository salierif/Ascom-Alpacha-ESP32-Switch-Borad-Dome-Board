#ifndef BROWSER_WEB
#define BROWSER_WEB


void browserServer(){

    server.on("/domecmd",              HTTP_PUT, [](AsyncWebServerRequest *request) {
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

    server.on("/switchcmd",              HTTP_PUT, [](AsyncWebServerRequest *request) {
        int id = -1;
        int value = -1;
        if (request->hasParam("id")){
             id = request->getParam("id")->value().toInt();
        } else { 
            request->send(200, "application/json", "{\"error\" : \"Missing ID\"");
            return;
        }
        if (request->hasParam("value")){ 
            value = request->getParam("value")->value().toInt();
        } else {
            request->send(200, "application/json", "{\"error\" : \"Missing Value\"");
            return;
        }
        if (id >= _MAX_SWTICH_ID_){ 
            request->send(200, "application/json", "{\"error\" : \"ID Out of Range\""); return;
        }
        if (!Switch[id].CanSet){ 
            request->send(200, "application/json", "{\"error\" : \"Switch cannot be setted\""); 
            return;
        }
        if (value < Switch[id].minValue || value > Switch[id].maxValue){
            request->send(200, "application/json", "{\"error\" : \"Value outside limits\"");
            return;
        }

        if (Switch[id].analog){
            Switch[id].anaValue = value;
            ledcWrite(Switch[id].pwmChannel, Switch[id].anaValue);
        } else {
            value == 1 ? digitalWrite(Switch[id].pin, HIGH) : digitalWrite(Switch[id].pin, LOW);
        }
        request->send(200, "text/html", "{\"done\" : 1");
    
    });

    server.on("/status",            HTTP_GET, [](AsyncWebServerRequest *request) {
        int i;
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->print("{");
        response->printf("\"dome\":{");
            response->print("\"actualState\":");
            response->print(Dome.ShutterState);
            response->print(",");
            response->print("\"lastCommand\":");
            response->print(Dome.LastDomeCommand);
        response->print("},");

        response->print("\"switches\": [");
        for (i=0;i<_MAX_SWTICH_ID_;i++){
            response->print("{\"id\":");
            response->print(i);
            response->print(",\"name\":\"");
            response->print(Switch[i].Name);
            response->print("\",\"description\":\"");
            response->print(Switch[i].Description);
            response->print("\",\"canBeHandle\":");
            response->print(Switch[i].CanSet);
            response->print(",\"type\":");
            response->print(Switch[i].analog);
            response->print(",\"actualValue\":");
            if (Switch[i].analog == true){
                response->print(analogRead(Switch[i].pin));
            } else {
                response->print(digitalRead(Switch[i].pin));
            }
            response->print(",\"min\":");
            response->print(Switch[i].minValue);
            response->print(",\"max\":");
            response->print(Switch[i].maxValue);
            response->print(",\"step\":");
            response->print(Switch[i].Step);
            response->print("}");
            if(i != _MAX_SWTICH_ID_ - 1 ){
                response->printf(",");
            }
        }
        response->print("]}");
        request->send(response);
    });

}

#endif