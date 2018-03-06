// Just a small test to see what works and what doesn't with arduino's
//pre-define stuff
class LED;
LED light;
void initializeLEDLight(LED &Light, int delay);

//Define Led Class
class LED{
  public: 
  int LEDDelay;
  bool IsLedOn;
};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  initializeLEDLight(light, 10);
}


void loop() {
Ledloop();
}
//Define classes
void Ledloop(){
  SwitchLed();
  light.LEDDelay = light.LEDDelay + 10;
  delay(light.LEDDelay);
}
void SwitchLed(){
   digitalWrite(LED_BUILTIN, light.IsLedOn ? LOW : HIGH);
   light.IsLedOn = !light.IsLedOn;
}

void initializeLEDLight(LED &Light, int delay){
  Light.LEDDelay = delay;
  Light.IsLedOn = false;  
}

