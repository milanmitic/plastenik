
int sum = 0;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  byte upper = Serial.read();
  byte lower = Serial.read();
  int x = (upper<<8) | lower; //Reassemble the number
  Serial.print(x, DEC);
  
  if(x>500){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  }
  else if(x<500){
  digitalWrite(LED_BUILTIN, LOW);delay(1000);
  }
   
  
   
}
