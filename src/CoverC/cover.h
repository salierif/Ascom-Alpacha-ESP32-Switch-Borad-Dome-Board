#ifndef COVER_HAND
#define COVER_HAND


void initCoverCConfig(){
    JsonDocument doc;
    File file = SPIFFS.open("/ccalibconfig.txt", FILE_READ);
    if (!file) {
        Serial.println("Reading Cover Calibrator config error");
        return;
    }
    DeserializationError error = deserializeJson(doc, file);

    if(error){
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    } else {
        Config.coverC.pin = doc["pin"];
    }
    file.close();
    Config.read.coverC.isValid = true;
    ledcSetup(0, 5000, 13);
    if(Config.coverC.pin){ ledcAttachPin(Config.coverC.pin, 0); }
}

void saveCoverCConfig(){
    String datasetup;
    JsonDocument doc;
    doc["pin"] = Config.coverC.pin;
    serializeJson(doc, datasetup);
    File file = SPIFFS.open("/ccalibconfig.txt", FILE_WRITE);
    file.print(datasetup);
    file.close();
}


void coverCLoop(){

    coverC.actualValue = ledcRead(0);
    if (coverC.actualValue != coverC.cmdValue){
        ledcWrite(0 ,coverC.cmdValue);
    }
}


#include "alpacaDevice.h"
#include "alpacaManage.h"
#include "webserver.h"

void coverServer(){

    CoverAlpacaDevice();
    CoverAlpacaManage();
    coverCWebServer();
}

#endif