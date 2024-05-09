#ifndef ALPACA_CONFIG
#define ALPACA_CONFIG


void initBoardConfig(){
    JsonDocument doc;
    File file = SPIFFS.open("/config.txt", FILE_READ);
    if (!file) {
        Serial.println("Reading Board config error");
        return;
    }
    DeserializationError error = deserializeJson(doc, file);
    if(error){
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }
    Config.alpacaPort.remotePort = doc["alpRemPort"];
    Config.alpacaPort.alpacaPort = doc["alpPort"];
    Serial.println(Config.alpacaPort.remotePort);
    Serial.println(Config.alpacaPort.alpacaPort);
    file.close();
    Config.read.dome.isValid = true;
}

#endif