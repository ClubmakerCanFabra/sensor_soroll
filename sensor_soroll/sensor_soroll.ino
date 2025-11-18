/*void setup(){
    Serial.begin(9600);
}

void loop(){
    int so=analogRead(A0);
    Serial.println(so);
    delay(200);
}
*/

// https://www.luisllamas.es/medir-sonido-con-arduino-y-microfono-amplificado-max9812/
// https://forum.arduino.cc/t/consulta-sobre-la-placa-ky-038-deteccion-de-sonido/850276
// https://circuitdigest.com/microcontroller-projects/arduino-sound-level-measurement
// https://www.youtube.com/watch?v=dKPURQHRQ4k

#define MAX_SAMPLE_SQUARED_DENOMINATOR 1
#define SOROLL_MINIM 0.01

const int sensorPIN = A0;
const int sampleWindow = 50; // Ancho ventana en mS (50 mS = 20Hz)

void setup() {
   Serial.begin(9600);
}

void loop() {
   unsigned long startMillis= millis();

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
   double squared_samples_sum = 0;
   unsigned int samples_in_window = 0;
 
   // Recopilar durante la ventana
   unsigned int sample;
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPIN);
      if (sample < 1024){
         if (sample > signalMax){
            signalMax = sample;  // Actualizar máximo
         }
         else if (sample < signalMin){
                signalMin = sample;  // Actualizar mínimo
              }
         squared_samples_sum += sample * sample;
         samples_in_window ++;
      }
   }
   unsigned int peakToPeak = signalMax - signalMin;  // Amplitud del sonido
   double volts = (peakToPeak * 3.3) / 1024;  // Convertir a tensión
   int deBe = (int)((volts * 87.1));  // - 75.4);
   //Serial.println(volts);
   Serial.print("Max:");  Serial.print(signalMax);  Serial.print("  Min:");  Serial.print(signalMin);  Serial.print("  P2P:");  Serial.print(peakToPeak);
   Serial.print("  V:");  Serial.print(volts);  Serial.print("  dB:");  Serial.print(deBe);  Serial.print("  Samples:");  Serial.print(samples_in_window);
   double rms_db = 10.0 * log10(squared_samples_sum / MAX_SAMPLE_SQUARED_DENOMINATOR / samples_in_window);
   double peak_db = 10.0 * log10(signalMax*signalMax / MAX_SAMPLE_SQUARED_DENOMINATOR);
   Serial.print("  rms dB:");  Serial.print(rms_db);  Serial.print("  Peak dB:");  Serial.print(peak_db);
   double nou_db = 10.0 * log10(volts*volts / SOROLL_MINIM*SOROLL_MINIM);
   Serial.print("  nou dB:");  Serial.println(nou_db);
}
