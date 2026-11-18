/* 

  Erkennung ob ein Modell (Lok) digitalisiert ist
  Beide LEDs aus: Gleis leer
  rot leuchtet:  Anlalog
  grün leuchtet: Digital
  
  [D2] ────[ 2 kΩ ]────(>|)────[GND]   (Rote LED: Analog)
                       Anode Kathode
                      (lang) (kurz)

  [D3] ────[ 2 kΩ ]────(>|)────[GND]   (Grüne LED: Digital)
                       Anode Kathode
                      (lang) (kurz)

  [5V] ────[ 10 kΩ ]────┬──── Gleisanschluss 1 (Schiene A)
                        │
                       [A0]  (Misst die Spannung am Gleis)

  [GND] ────────────────┴──── Gleisanschluss 2 (Schiene B)

 */

const int MESS_PIN    = A0;
const int LED_ANALOG  = 2; // Rot
const int LED_DIGITAL = 3; // Grün

// Variable Schwelle: Passe diesen Wert an, basierend auf dem, 
// was der Serielle Monitor bei deiner analogen Lok anzeigt!
const int GRENZE_ANALOG = 200; // Erst mal höher angesetzt (ca. 1V)
const int GRENZE_LEER   = 950; // Ab hier gilt das Gleis als leer

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_ANALOG, OUTPUT);
  pinMode(LED_DIGITAL, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.begin(115200);
}

void loop() {
  int wert = analogRead(MESS_PIN);
  
  // Wert permanent ausgeben, damit du die Schwellen perfekt einstellen kannst
  Serial.print("ADC-Wert: ");
  Serial.println(wert);

  if (wert > GRENZE_LEER) {
    // Gleis ist leer (~5V) -> Beide LEDs aus
    digitalWrite(LED_ANALOG, LOW);
    digitalWrite(LED_DIGITAL, LOW);
  } 
  else if (wert < GRENZE_ANALOG) {
    // Wert liegt unter der Schwelle -> Analoger Motor -> ROTE LED
    digitalWrite(LED_ANALOG, HIGH);
    digitalWrite(LED_DIGITAL, LOW);
  } 
  else {
    // Wert liegt zwischen analoger Schwelle und Leerlauf -> Decoder -> GRÜNE LED
    digitalWrite(LED_ANALOG, LOW);
    digitalWrite(LED_DIGITAL, HIGH);
  }

  delay(250); // Etwas verlangsamt, damit man im Monitor gut mitlesen kann
}