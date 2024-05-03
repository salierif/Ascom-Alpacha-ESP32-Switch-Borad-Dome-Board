#ifndef CONFIGURATION
#define CONFIGURATION


void saveConfig(){

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

    if(Config.save.coverC.restartNeeded || Config.save.dome.restartNeeded || Config.save.switches.restartNeeded){
        ESP.restart();
    }

}

#endif