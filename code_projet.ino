
// Pins
const int lightSensorPin = A0;      // Capteur KY-018 sur A0
const int soundSensorPin = A2;      // KY-037 sur A2 pour lecture analogique
const int whiteLedPin1 = 7;          // LED blanche sur D9 (PWM)
const int whiteLedPin2 = 6;          // LED blanche sur D9 (PWM)
//const int whiteLedPin3 = 5;          // LED blanche sur D9 (PWM)
const int redLedPin = 4;            // LED rouge sur D8


// Seuils et délais
const int THRESHOLD = 27;
const unsigned long DURATION = 15000;
unsigned long startTime = 0;


void setup() {
  pinMode(whiteLedPin1, OUTPUT);
  pinMode(whiteLedPin2, OUTPUT);
  //pinMode(whiteLedPin3, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Mesure de la lumière ambiante
  int lightLevel = analogRead(lightSensorPin);
  
  // Inverser la luminosité de la LED blanche en fonction de la lumière ambiante
  int whiteLedBrightness1 = map(lightLevel, 400,1000, 255, 10); // Faible quand la lumière est forte
  int whiteLedBrightness2 = map(lightLevel, 400, 1000, 255, 10); // Faible quand la lumière est forte
  //int whiteLedBrightness3 = map(lightLevel, 400, 1000, 255, 10); // Faible quand la lumière est forte
  analogWrite(whiteLedPin1, whiteLedBrightness1);
  analogWrite(whiteLedPin2, whiteLedBrightness2);
  //analogWrite(whiteLedPin3, whiteLedBrightness3);

  // Mesure du bruit
  int soundLevel = analogRead(soundSensorPin);

  // Affichage des valeurs pour le débogage
  Serial.print("Lumière ambiante: ");
  Serial.print(lightLevel);
  Serial.print("| Intensite: ");
  Serial.print(whiteLedBrightness1);
  Serial.print(" |: ");
  Serial.print(whiteLedBrightness2);
  Serial.print(" |: ");
  //Serial.print(whiteLedBrightness3);
  Serial.print(" | Son: ");
  Serial.println(soundLevel);

  //Détection du bruit
  if (soundLevel >= THRESHOLD){
      if (startTime == 0){
        startTime = millis();
      
      }else if (millis() - startTime >= DURATION){
        digitalWrite(redLedPin, HIGH);

      }
    }else{

      startTime = 0;
      digitalWrite(redLedPin, LOW);
    }

    delay(100);

}
