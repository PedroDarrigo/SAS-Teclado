// programa nuevo
// ver


#include "Wire.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include <SPI.h>      
#include <MFRC522.h>      
#include <Keypad.h>
 
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(-1); // -1 = no reset pin
#define RST_PIN  9      
#define SS_PIN  10      
MFRC522 mfrc522(SS_PIN, RST_PIN); 
const byte ROWS = 4; 
const byte COLS = 3; 
//int pulsacion = 0;        
int clave = 0;
int cursor = 0;
int keyA = 0;
int keyB = 0;
int keyC = 0;
int keyD = 0;
int claveS = 98;


char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6,7,8}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



int codigo(char valor){
  delay(100);
  
}

void Inicio(){
 display.clearDisplay ();
  display.setTextSize(4);        
  display.setTextColor(1,0);
  display.setCursor(3,3);
  display.println("DESIT");
  display.display ();
  }

void Teclado (){
      display.clearDisplay ();
      display.setCursor(30+cursor*20,6);
      display.println("*");
      display.display ();
    }

void Ok (){
        display.clearDisplay ();
       display.setTextSize(4);     
       display.setCursor(34,6);
       display.println("OK");
}


void Error (){
       display.clearDisplay ();
       display.setTextSize(3);       
       display.setCursor(14,6); 
       display.println("ERROR");
}

void setup () {
  display.begin (SSD1306_SWITCHCAPVCC, OLED_ADDR);
  Inicio (); 
  Serial.begin(9600);     
  SPI.begin();        
  mfrc522.PCD_Init(); 
  Serial.println("programa iniciado");
  display.clearDisplay ();
  display.setTextSize(3);        
  display.setTextColor(1,0);
  
}
 
void loop () {
    

char pulsacion = keypad.getKey();
    
   if (pulsacion){
      Teclado();
      cursor ++;
      delay(200);  
    }
      
    // Rutina de verificacion de codigo
      if (cursor >= 1 && pulsacion > 0 && pulsacion != '#' && pulsacion != '*' ){
          if (cursor < 2){
            keyA = pulsacion;
            keyD = keyA-48;
          }
          } 
      if (cursor >= 2){
           keyB = pulsacion;
           keyC = (keyB-48)+ keyD * 10;
           cursor = 0;
           
           //display.clearDisplay ();
           if (claveS == keyC) {     
                 Serial.println (keyC);
                 Ok();
                }
            else{
                Error ();
                 } 
            display.display ();
            delay(2000);    
            Inicio(); 
      }
    
    // RFID
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    return;         
  
    if ( ! mfrc522.PICC_ReadCardSerial())   
    return;         
    
    Serial.print("UID:");       
    for (byte i = 0; i < mfrc522.uid.size; i++) { 
    if (mfrc522.uid.uidByte[i] < 0x10){   
      Serial.print(" 0");     
      }
      else{         
      Serial.print(" ");      
      }
    Serial.print(mfrc522.uid.uidByte[i], HEX);  
     if (mfrc522.uid.uidByte[i]="7C 53 C1 B2"){
    Ok();
    }
    else{
      Error ();
    }
  } 
      display.display ();
      delay(2000);    
      Inicio();
  Serial.println();       
  mfrc522.PICC_HaltA(); 
 
} 
   
      




  
 
