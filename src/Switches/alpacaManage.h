#ifndef SWITCH_ALPACA_MANAGE
#define SWITCH_ALPACA_MANAGE

void SwitchAlpacaManage(){

  Alpserver.on("/api/v1/switch/0/name",                                                     HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"NINAHubSwitch\"}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/connected",                                                HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response,false);
    response->printf("}");
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/description",                                              HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"NINAHub Switch\"}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/driverinfo",                                               HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"NINAHub Dome response on the fly\"}",Alp_Value);
    request->send(response);
  });

  Alpserver.on("/api/v1/switch/0/driverversion",                                            HTTP_GET, [](AsyncWebServerRequest *request) {

    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s\"2.0.0\"}",Alp_Value);
    request->send(response);

  });

  Alpserver.on("/api/v1/switch/0/interfaceversion",                                         HTTP_GET, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->printf("%s1}",Alp_Value);
    request->send(response);
  });

}

#endif
