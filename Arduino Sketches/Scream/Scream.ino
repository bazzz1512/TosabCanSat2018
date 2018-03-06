//Scream
class Beeper {
public:
void SwitchState();
Beeper();

private:
int DigitalPin;
bool OnOff;
}BP;

Beeper::Beeper(){
  OnOff = false;
  DigitalPin = 4;
}
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
   Serial.begin(9600);
   Serial.println(F("Serial started"));  
  pinMode(26, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
if (Serial.available())
  {
    char ch = Serial.read();
    if (ch = 'B'){
      Serial.println("Lol");
      BP.SwitchState();
    }
  }  
}

void Beeper::SwitchState(){
  (OnOff) ? digitalWrite(26,LOW) : digitalWrite(26,HIGH);
  OnOff = !OnOff;
  
}



