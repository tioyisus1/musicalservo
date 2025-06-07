#include <Servo.h>
#include "pitches.h"

// Definir los pines de los piezoeléctricos
const int piezoPin1 = 8;
const int piezoPin2 = 12;

// Definir los pines para los servos
const int servoPin1 = 9;
const int servoPin2 = 10;
const int servoPin3 = 11;

// Definir los pines para los LEDs
const int ledPin1 = 5;
const int ledPin2 = 6;

// Definir el pin para el potenciómetro
const int potPin = A0;

// Crear objetos Servo
Servo servo1;
Servo servo2;
Servo servo3;

// Melodía
int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,
  REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5,
  REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5,
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,

  REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5,
  REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5,
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,

  REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5,
  REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

// Duraciones de las notas
int noteDurations[] = {
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};

void setup() {
  // Inicializar el Monitor Serial
  Serial.begin(9600);

  // Inicializar los servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  
  // Inicializar los piezoeléctricos
  pinMode(piezoPin1, OUTPUT);
  pinMode(piezoPin2, OUTPUT);
  
  // Inicializar los LEDs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Inicializar el pin del potenciómetro
  pinMode(potPin, INPUT);
  
  // Inicializar los servos en la posición central
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  
  Serial.println("Setup completo");
}

void loop() {
  // Leer el valor del potenciómetro
  int potValue = analogRead(potPin);
  // Mapear el valor del potenciómetro a un rango de 0.5x a 2x de la velocidad original
  float speedFactor = map(potValue, 0, 1023, 50, 200) / 100.0;
  
  Serial.print("Potenciómetro: ");
  Serial.print(potValue);
  Serial.print(" - Speed Factor: ");
  Serial.println(speedFactor);
  
  // Iterar sobre las notas de la melodía
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    // Asegurarse de que la duración no sea menor que 1 milisegundo
    int baseDuration = 1000 / noteDurations[thisNote];
    float noteDurationFloat = baseDuration / speedFactor;
    int noteDuration = max(int(noteDurationFloat), 1); // Asegúrate de que noteDuration sea al menos 1
    
    int noteFrequency = melody[thisNote];
    
    Serial.print("Nota: ");
    Serial.print(noteFrequency);
    Serial.print(" - Duración: ");
    Serial.println(noteDuration);

    // Alternar piezoeléctricos
    if (thisNote % 2 == 0) {
      tone(piezoPin1, noteFrequency);
      Serial.println("Tono en piezoPin1");
    } else {
      tone(piezoPin2, noteFrequency);
      Serial.println("Tono en piezoPin2");
    }

    // Determinar qué servo mover basado en la frecuencia
    if (noteFrequency > 440) { // Notas altas (> A4)
      servo3.write(map(noteFrequency, 440, 987, 0, 180)); // Mover servo 3
      Serial.println("Servo 3 moviéndose");
    } else if (noteFrequency > 330) { // Notas medias (330 < frecuencia <= 440)
      servo2.write(map(noteFrequency, 330, 440, 0, 180)); // Mover servo 2
      Serial.println("Servo 2 moviéndose");
    } else { // Notas bajas (<= 330)
      servo1.write(map(noteFrequency, 262, 330, 0, 180)); // Mover servo 1
      Serial.println("Servo 1 moviéndose");
    }

    // Pausa entre las notas
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // Detener el tono de ambos piezoeléctricos
    noTone(piezoPin1);
    noTone(piezoPin2);
    
    Serial.println("Nota finalizada");
  }

  // Pausa al final de la melodía para evitar que se reinicie inmediatamente
  delay(1000);
  Serial.println("Esperando reinicio de la melodía");
}
