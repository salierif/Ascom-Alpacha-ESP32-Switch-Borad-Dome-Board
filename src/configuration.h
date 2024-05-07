#ifndef CONFIGURATION
#define CONFIGURATION

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
    Config.alpacaPort.remotePort = doc["alpacaremport"];
    Config.alpacaPort.alpacaPort = doc["alpacaboardport"];
    file.close();
    Config.read.dome.isValid = true;
}

void saveBoardConfig(){
    String datasetup;
    JsonDocument doc;

    doc["alpacaremport"] = Config.alpacaPort.remotePort;
    doc["alpacaboardport"] = Config.alpacaPort.alpacaPort;

    serializeJson(doc, datasetup);
    File file = SPIFFS.open("/config.txt", FILE_WRITE);
    file.print(datasetup);
    file.close();
}


void saveConfig(){

    if(Config.save.board.execute){
        saveBoardConfig();
    }
    
    #ifdef DOME 
    if(Config.save.dome.execute){
        saveDomeConfig();
    }
    #endif

    #ifdef SWITCH
    if(Config.save.switches.execute){
        saveSwitchConfig();
    }
    #endif

    #ifdef COVERC
    if(Config.save.coverC.execute){  
        saveCoverCConfig();
    }
    #endif

    Config.save.dome.execute = false;
    Config.save.switches.execute = false;
    Config.save.coverC.execute = false;

    if(Config.save.coverC.restartNeeded || Config.save.dome.restartNeeded || Config.save.switches.restartNeeded || Config.save.board.restartNeeded){
        Serial.println("restarting...");
        ESP.restart();
    }

}

#endif