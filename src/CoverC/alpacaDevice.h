#ifndef COVER_ALPACA_DEVICE
#define COVER_ALPACA_DEVICE


void CoverAlpacaDevice()
{

  Alpserver.on("/api/v1/covercalibrator/0/brightness", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":"));
    response->print(ledcRead(0));
    response->print(F("}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/calibratorstate", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":3}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/coverstate", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":3}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/maxbrightness", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":8192}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/calibratoroff", HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    coverC.cmdValue = 0;
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response,false);
    response->print(F("}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/calibratoron", HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    if(AlpacaData.coverC.brightness < 0 || AlpacaData.coverC.brightness > 8192){
      response->printf("%s1025,%s\"Brightness value exced limit. %d given, MIN:0 MAX:8192\"",Alp_ErrN,Alp_ErrM,AlpacaData.coverC.brightness);
    } else {
      coverC.cmdValue = AlpacaData.coverC.brightness;
      AlpacaNoErrorSchema(response,false);
    }
    response->print(F("}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/action", HTTP_PUT, [](AsyncWebServerRequest *request) {
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    response->printf("%s1036,%s\"No Actions defined\"}",Alp_ErrN,Alp_ErrM);
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/closecover", HTTP_PUT, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/haltcover", HTTP_PUT, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/opencover", HTTP_PUT, AscomPropertyNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/commandblind", HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/commandbool", HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/commandstring", HTTP_PUT, AscomMethodNotImplemented);
  Alpserver.on("/api/v1/covercalibrator/0/supportedactions", HTTP_GET, AscomNoActions);
}

#endif
