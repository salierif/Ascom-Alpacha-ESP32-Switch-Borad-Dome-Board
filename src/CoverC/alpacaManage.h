#ifndef COVER_ALPACA_MANAGE
#define COVER_ALPACA_MANAGE



void CoverAlpacaManage()
{
  Alpserver.on("/api/v1/covercalibrator/0/connected", HTTP_GET, [](AsyncWebServerRequest *request){
      GetAlpArguments(request);
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      AlpacaHeaderSchema(response,AlpacaData);
      AlpacaNoErrorSchema(response);
      response->print(F("\"Value\":true}"));
      request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/connected", HTTP_PUT, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response,false);
    response->print(F("}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/description", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"StefanoTesla CoverCalibrator\"}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/driverinfo", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"StefanoTesla CoverCalibrator response on the fly\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/driverversion", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"2.0.0\"}"));
    request->send(response);
  });

  Alpserver.on("/api/v1/covercalibrator/0/interfaceversion", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":1}"));
    request->send(response); 
  });

  Alpserver.on("/api/v1/covercalibrator/0/name", HTTP_GET, [](AsyncWebServerRequest *request){
    GetAlpArguments(request);
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    AlpacaHeaderSchema(response,AlpacaData);
    AlpacaNoErrorSchema(response);
    response->print(F("\"Value\":\"StefanoTesla Cover Calibrator\"}"));
    request->send(response);
  });
  
}

#endif
