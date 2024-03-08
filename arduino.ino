#define TRIG_PIN 12 // Definerer pin for utløseren til ultralydsensoren
#define ECHO_PIN 11 // Definerer pin for ekkoet fra ultralydsensoren
#define BUZZER_PIN 10 // Definerer pin for buzzeren
unsigned long previousMillis = 0; // Lagrer siste tidspunkt en tone ble spilt
long beepDelay = 0; // Forsinkelsen mellom pip, varierer invers med avstand
const int numReadings = 10; // Antall avlesninger for å bestemme om et objekt er stasjonært
int readings[numReadings]; // Array for å lagre avstandsavlesninger
int readIndex = 0; // Indeks for gjeldende avlesning
long averageDistance = 0; // Gjennomsnittlig avstand
long total = 0; // Totalen av avlesningene for gjennomsnittsberegning
bool isStationary = false; // Flagg for deteksjon av stasjonære objekter
long lastDistance = 0; // Lagrer siste avstandsmåling
unsigned long lastTime = 0; // Lagrer siste tidspunkt en måling ble tatt
float speed = 0; // Hastigheten til objektet som nærmer seg eller fjerner seg

void setup() {
 pinMode(TRIG_PIN, OUTPUT); // Setter trigger-pin som en utgang
 pinMode(ECHO_PIN, INPUT); // Setter ekko-pin som en inngang
 pinMode(BUZZER_PIN, OUTPUT); // Setter buzzer-pin som en utgang
 Serial.begin(9600); // Starter seriell kommunikasjon
 // Initialiserer alle avlesningene til 0:
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
   readings[thisReading] = 0;
 }
 lastTime = millis(); // Initialiserer lastTime
}

void loop() {
 unsigned long currentMillis = millis(); // Henter gjeldende tid i millisekunder
 long duration, distance;
 digitalWrite(TRIG_PIN, LOW); // Sørger for lavt signal for å stabilisere sensoren
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH); // Sender en høy puls for å aktivere sensoren
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW); // Setter signalet lavt igjen for å lytte etter ekko
 duration = pulseIn(ECHO_PIN, HIGH); // Måler varigheten av ekkoet
 distance = duration * 0.034 / 2; // Regner ut avstanden basert på varigheten

 // Trekker fra siste avlesning:
 total = total - readings[readIndex];
 // Leser fra sensoren:
 readings[readIndex] = distance;
 // Legger til den nye avlesningen i totalen:
 total = total + readings[readIndex];
 // Går videre til neste posisjon i arrayet:
 readIndex = readIndex + 1;

 // Hvis vi er ved slutten av arrayet...
 if (readIndex >= numReadings) {
   // ...går vi tilbake til begynnelsen:
   readIndex = 0;
 }

 // Kalkulerer gjennomsnittet:
 averageDistance = total / numReadings;
 // Sjekker om objektet er stasjonært
 isStationary = checkIfStationary(distance);

 // Hastighetsberegning
 unsigned long timeInterval = currentMillis - lastTime;
 if (timeInterval > 0) { // Forhindrer deling på null
   // Hastighet i cm/s (endring i avstand i cm over tid i ms)
   speed = (distance - lastDistance) / (timeInterval / 1000.0);
   lastDistance = distance;
   lastTime = currentMillis;
 }

 // Invers kartlegging av avstand til pip-forsinkelse
 if (distance < 200) {
   beepDelay = map(distance, 0, 200, 200, 1000);
   beepDelay = constrain(beepDelay, 200, 1000);
 } else {
   beepDelay = -1;
 }

 if (beepDelay != -1 && currentMillis - previousMillis >= beepDelay) {
   previousMillis = currentMillis;
   tone(BUZZER_PIN, 1000, 100); // Spiller en tone på buzzeren
 }

 // Bruker Serial.println() for grafing i Serial Plotter
 Serial.println(distance);
 // Valgfritt: Bruk Serial Monitor for feilsøking
 Serial.print("Avstand: "); Serial.print(distance); Serial.print(" cm, Stasjonær: "); Serial.print(isStationary ? "Ja" : "Nei");
 Serial.print(", Hastighet: "); Serial.print(speed); Serial.println(" cm/s");
 delay(100); // Kort forsinkelse for stabil avlesning
}

bool checkIfStationary(long currentDistance) {
  // Antar at objektet er stasjonært hvis forskjellen mellom to påfølgende avlesninger er innenfor en terskel
  for (int i = 1; i < numReadings; i++) {
    if (abs(readings[i] - readings[i - 1]) > 5) { // 5 cm som terskel for endring
      return false;
    }
  }
  return true;
}
