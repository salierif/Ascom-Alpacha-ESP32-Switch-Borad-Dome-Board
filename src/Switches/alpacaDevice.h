#ifndef SWITCH_ALPACA_DEVICE
#define SWITCH_ALPACA_DEVICE

void SwitchAlpacaDevice(){

  Alpserver.on("/api/v1/dome/0/action",                                                    HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    response->print(F("\"ErrorNumber\":1036,\"ErrorMessage\":\"No actions defined\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/maxswitch",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s%d}",Alp_Value,Config.switches.configuredSwitch);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/connected",                                             HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%strue}",Alp_Value,Dome.ShutterState);
    request->send(response);
  });

 
  Alpserver.on("/api/v1/switch/0/getswitchname",                                            HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s\"%s\"}",Alp_Value,Switch[AlpacaData.switches.id].Name);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitchdescription",                                     HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s\"%s\"}",Alp_Value,Switch[AlpacaData.switches.id].Description);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/minswitchvalue",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].property.minValue);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/maxswitchvalue",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].property.maxValue);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/switchstep",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      response->printf("%s%d}",Alp_Value,Switch[AlpacaData.switches.id].property.Step);
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/canwrite",                                                 HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
      AlpacaNoErrorSchema(response);
      if(Switch[AlpacaData.switches.id].property.type == 1 || Switch[AlpacaData.switches.id].property.type == 3){
        response->printf("%strue}",Alp_Value);
      } else {
        response->printf("%sfalse}",Alp_Value);
      }
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitchvalue",                                           HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response);
        response->printf("%s",Alp_Value);
        response->print(Switch[AlpacaData.switches.id].readValue);
        response->print(F("}"));
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/getswitch",                                                HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response);
        response->printf("%s",Alp_Value);
        if (Switch[AlpacaData.switches.id].readValue == 0){
          response->printf("false");
        }
        else {
          response->printf("true");
        }
        response->print(F("}"));
    }
    
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/setswitch",                                                 HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else if(!AlpacaData.switches.stateExist || AlpacaData.switches.state < 0 || AlpacaData.switches.state > 1){
      response->printf("%s1025,%s\"State value not valid MIN:false MAX:true, %d given\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.state);
    } else if( Switch[AlpacaData.switches.id].property.type == 2 || Switch[AlpacaData.switches.id].property.type == 4){
      response->printf("%s1025,%s\"Switch %d is an input, cannot be set\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response,false);
        if (AlpacaData.switches.state){
          Switch[AlpacaData.switches.id].cmdValue = Switch[AlpacaData.switches.id].property.maxValue;
        } else {
          Switch[AlpacaData.switches.id].cmdValue = Switch[AlpacaData.switches.id].property.minValue;
        }
        response->printf("}");
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/setswitchvalue",                                            HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(!AlpacaData.switches.idExist || AlpacaData.switches.id < 0 || AlpacaData.switches.id >= Config.switches.configuredSwitch){
      response->printf("%s1025,%s\"The Switch %d doesn't exist\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else if(!AlpacaData.switches.intValueExist || !validateSwitchValue(AlpacaData.switches.id,AlpacaData.switches.intValue)){
      response->printf("%s1025,%s\"State value not valid MIN:%d MAX:%d, %d given\"}",Alp_ErrN,Alp_ErrM,Switch[AlpacaData.switches.id].property.minValue,Switch[AlpacaData.switches.id].property.maxValue,AlpacaData.switches.intValue);
    } else if( Switch[AlpacaData.switches.id].property.type == 2 || Switch[AlpacaData.switches.id].property.type == 4){
      response->printf("%s1025,%s\"Switch %d is an input, cannot be set\"}",Alp_ErrN,Alp_ErrM,AlpacaData.switches.id);
    } else {
        AlpacaNoErrorSchema(response,false);
        Switch[AlpacaData.switches.id].cmdValue = AlpacaData.switches.intValue;
        response->printf("}");
    }
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/commandblind",                                           HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandbool",                                            HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/commandstring",                                          HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/switch/0/supportedactions",                                       HTTP_GET, AscomNoActions);

}

#endif
