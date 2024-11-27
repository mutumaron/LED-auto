#include <Arduino.h>


//put function declarations here:
int redPin = 2;
int greenPin = 4;
int yellowPin = 7;

bool isOscillating = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);

  Serial.begin(9600);
  Serial.println("Arduino is ready.");
}

void loop() {

  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
   
    String command = Serial.readStringUntil('\n');
    command.trim();

    if(command == "RLED_ON"){
      digitalWrite(redPin,HIGH);//Turn on LED
    }else if (command == "RLED_OFF"){
      digitalWrite(redPin,LOW);
    }else if(command == "GLED_ON"){
      digitalWrite(greenPin,HIGH);
    }else if(command == "GLED_OFF"){
      digitalWrite(greenPin,LOW);
    }else if(command == "YLED_ON"){
      digitalWrite(yellowPin,HIGH);
    }else if(command == "YLED_OFF"){
      digitalWrite(yellowPin,LOW);
    }
    
    
    else if(command == "OLED_ON"){
      isOscillating = true;
      while(isOscillating){
             digitalWrite(redPin,HIGH);
      digitalWrite(greenPin,LOW);
      digitalWrite(yellowPin,LOW);
      delay(250);

      digitalWrite(redPin,LOW);
      digitalWrite(greenPin,HIGH);
      digitalWrite(yellowPin,LOW);
      delay(250);

      digitalWrite(redPin,LOW);
      digitalWrite(greenPin,LOW);
      digitalWrite(yellowPin,HIGH);
      delay(250);

      if(Serial.available() > 0){
        String stopCommand = Serial.readStringUntil('\n');
        stopCommand.trim();
        if(stopCommand == "OLED_OFF"){
           isOscillating = false;
         digitalWrite(redPin,LOW);
         digitalWrite(greenPin,LOW);
         digitalWrite(yellowPin,LOW);
        }
      }
      }
    }
    else if(command == "OLED_OFF"){
      isOscillating = false;  // Set flag to stop oscillation
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);  // Turn off all LEDs
    }
    else{
      Serial.println("Unknown command");
    }
  }
}
