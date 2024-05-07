#ifndef SWITCH_HAND
#define SWITCH_HAND

bool validateSwitchValue(int id,int value){
  if(value >= Switch[id].property.minValue && value <= Switch[id].property.maxValue){
    return true;
  }

  return false;
}

void switchSetup() {
  int i=0;
/* Switch Setup */

/* Default Switch setting

  pin -> Choose the GPIO where switch is plugged on!
  minValue -> Min Value the switch can have (default is 0 and is set to 0 if Switch is Output)
  maxValue -> Max Value the switch can have (default is 1 and is forced to 1 if Switch is Output)
  Step -> Choose the step for change the value of Switch (default 1 and forced to 1 if is output)
  pwmChannel -> Default -1, the value can be 0..15 according to esp32 pwm channels

Please refer to this page to understand wich output/input you can use without problems:
https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
*/


/* automatic setup for Switch */

  for (i=0;i<_MAX_SWITCH_ID_;i++){
    if(Switch[i].pin == 0){
        Switch[i].Name ="";
        Switch[i].Description ="";
        return;
    }
    switch(Switch[i].property.type){
      case 1: //Digital Output
              pinMode(Switch[i].pin, OUTPUT);
              break;
      case 2: //Digital Input
              pinMode(Switch[i].pin, INPUT);
              break;
      case 3: //PWM Output
              ledcSetup(pwmchannles, 5000, 13);
              ledcAttachPin(Switch[i].pin, pwmchannles);
              Switch[i].pwmChannel = pwmchannles;
              Switch[i].property.minValue = 0;
              Switch[i].property.maxValue = 8192;
              pwmchannles++;
              break;
      case 4: //Analog Input
              Switch[i].property.minValue = 0;
              Switch[i].property.maxValue = 4095;
              break;
      default:
        Serial.print(F("Wrong type "));
        Serial.print(Switch[i].property.type);
        Serial.print(F(" for pin "));
        Serial.print(Switch[i].pin);
    }
  }
}

void initSwitchConfig(){

    JsonDocument doc;
    File file = SPIFFS.open("/switchconfig.txt", FILE_READ);
    if (!file) {
        Serial.println(F("Reading Switch config error"));
        return;
    }

    DeserializationError error = deserializeJson(doc, file);
    if(error){
        Serial.print(F("deserialize switch setting failed: "));
        Serial.println(error.c_str());
        return;
    } 

    int i=0;
    int type = 0;
    int pin = 0;
    for (JsonObject elem : doc.as<JsonArray>()) {
        pin = elem["pin"].as<unsigned int>();
        type = elem["type"].as<unsigned int>();
        if (validatePin(pin,type)){
            Switch[i].Name = elem["name"].as<String>();
            Switch[i].Description = elem["desc"].as<String>();
            Switch[i].pin = pin;
            Switch[i].property.type = type;
            i++;
            Config.switches.configuredSwitch = i;
        } else{
          break;
        }
    }
    
    file.close();
    Config.read.switches.isValid = true;
    switchSetup();
}

void saveSwitchConfig(){
    int i = 0;
    File file = SPIFFS.open("/switchconfig.txt", FILE_WRITE);
    file.print("[");
    for(i=0;i<_MAX_SWITCH_ID_;i++){
        file.print("{\"name\":\"");
        file.print(Switch[i].Name.substring(0,32));
        file.print("\",\"desc\":\"");
        file.print(Switch[i].Description.substring(0,32));
        file.print("\",\"type\":");
        file.print(Switch[i].property.type);
        file.print(",\"pin\":");
        file.print(Switch[i].pin);
        file.print("}");
        if(i != _MAX_SWITCH_ID_ - 1){
            file.print(",");
        }
        if (Switch[i].pin != 0 ){
          Config.switches.configuredSwitch = i+ 1;    //avoid problems if delete one switch
        }
    }
    file.print("]");
    file.close();
}


void switchLoop(){
  for(int i=0;i<Config.switches.configuredSwitch;i++){
    int type = Switch[i].property.type;
    switch(type){
    
      case 1://DO
        Switch[i].readValue = digitalRead(Switch[i].pin);
        if (Switch[i].cmdValue >= 0 && validateSwitchValue(i,Switch[i].cmdValue) ){
          digitalWrite(Switch[i].pin,Switch[i].cmdValue);
          Switch[i].cmdValue = -1;
        }
        break;

      case 2://DI
        Switch[i].readValue = digitalRead(Switch[i].pin);
        break;

      case 3://PWM
        Switch[i].readValue = ledcRead(Switch[i].pwmChannel);
        if ( Switch[i].cmdValue >= 0 && validateSwitchValue(i,Switch[i].cmdValue)
        ){
          Serial.print("switch new value ");
          Serial.println(Switch[i].cmdValue);
          ledcWrite(Switch[i].pwmChannel,Switch[i].cmdValue);
          Switch[i].cmdValue = -1;
        }      
        break;

      case 4://AI
        Switch[i].readValue = analogRead(Switch[i].pin);
        break;

    default:
      Serial.print("error handling switch ");
      Serial.println(i);
      break;

    }
  }



}
  
#include "alpacaDevice.h"
#include "alpacaManage.h"
#include "webserver.h"

void switchServer(){
  SwitchAlpacaDevice();
  SwitchAlpacaManage();
  switchWebServer();
}

#endif
