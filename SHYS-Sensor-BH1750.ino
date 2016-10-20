#include <BH1750.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Shys_Sensor.h>
#include <Wire.h>

BH1750 lightMeter; // Pins an SCL&SDA (je nach board)

/* *********************************** */
/*             CONFIGURE               */
/* *********************************** */
long lightSensorId = 10003;

byte _piAddress[] =  {192, 168, 1, 98};

byte _mac[]  = {0xDF, 0x8D, 0xCB, 0x37, 0xC4, 0xED  };
byte _ip[]   = { 192, 168, 1, 28 };
byte _dns[]  = { 192, 168, 1, 1  };
byte _gate[] = { 192, 168, 1, 1  };
byte _mask[] = { 255, 255, 255, 0  };

long unsigned int lightSignalIntervall = 10000;
/* *********************************** */
/*           END CONFIGURE             */
/* *********************************** */





long light = -999;
long unsigned int lastLightSignal;  
Shys_Sensor sensor  = Shys_Sensor(_mac, _ip, _dns, _gate, _mask, _piAddress);

/**
 *  Basic setup Method
 */
void setup(void){
  Serial.begin(9600); 
  delay(700);
  
  sensor.init();
  
  lightMeter.begin();
  
  delay(500); 
}

// --------------------------------------------------

void loop(void){
  refreshBH1750SensorValues();

  if(lastLightSignal+lightSignalIntervall<millis()){
    Serial.print("Light: ");
    Serial.print(light);
    Serial.println(" lx");
    sensor.setSensorValue(lightSensorId, light);
  }
  delay(1000); 
}

void refreshBH1750SensorValues(){
  uint16_t lux = lightMeter.readLightLevel();
  light = lux;
}
