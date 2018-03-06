//pre-define functions
class LED;
LED light;
void initializeLEDLight(LED &Light, int delay);

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

// the loop function runs over and over again forever
void loop() {
Ledloop();
}

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

