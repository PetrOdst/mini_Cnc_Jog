/*  
 *   <==========> Dálkové ovláhání CNCcka <==========>
 *   
 *  vývojová deska: Arduino Leonardo 
    port:cu.usbmodemHID1
    programator:Arduino ISP (ATmega32U4)
    
    /dropbox/CNCJOG/
*/
#include <RotaryEncoder.h>
#include "Keyboard.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

RotaryEncoder encoder1(5,4);
RotaryEncoder encoder2(16, 14);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);



String disposa,dispkrok;
int pos = 0; 
int rotace;
int selekt = 0;
int osa, krok;

#define I2C_SDA 2
#define I2C_SCL 3


#include "OneButton.h"

// Setup a new OneButton on pin A1.  
OneButton button1(6, true);
// Setup a new OneButton on pin A2.  
OneButton button2(15, true);

bool stav;
bool cudlik = false;

void setup() {
  Serial.begin(9600);

osa = 1;
krok = 2;
  

Wire.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.drawRoundRect(1, 1, display.width()-2, display.height()-2, 4, SSD1306_WHITE);
  display.drawFastVLine(35, 1,15, SSD1306_WHITE ) ;
  display.setTextSize(1);            
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(8,4);
  display.println(" Osa ");
  display.drawFastHLine(1, 15,127, SSD1306_WHITE ) ;
  display.setCursor(50,4);             
  display.println(" Posun " ); 
  display.setTextSize(2);
  display.setCursor(4,29);             
  display.println("CNC Jog v2" );                

  display.display();
   
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);

  
  // This initializes the NeoPixel library.  
  

 // Animate bitmaps
}

void xy01(){
 
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
 // Keyboard.press('1');  
  delay(10);
  Keyboard.releaseAll();
  
}
void xy1(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('b');
  //Keyboard.press('2');  
  delay(10);
  Keyboard.releaseAll();  
}
void xy10(){
    Keyboard.begin();
    
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('c');
  //Keyboard.press('3');  
  delay(10);
  Keyboard.releaseAll();
  
}

void xy100(){
      Keyboard.begin();
      
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('d');
  //Keyboard.press('4');  
  delay(10);
  
  Keyboard.releaseAll();
}
  
void xy1000(){
      Keyboard.begin();
      
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('e');
  //Keyboard.press('5');  
  delay(10);
  
  Keyboard.releaseAll();
  
}
void z01(){
    Keyboard.begin();
    
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('f');
  //Keyboard.press('1');  
  delay(10);
  Keyboard.releaseAll();
}
void z1(){
    Keyboard.begin();
    
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('g');
  
  //Keyboard.press('2');  
  delay(10);
  Keyboard.releaseAll();
}
void z10(){
    Keyboard.begin();
    
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('h');
 // Keyboard.press('3');  
  delay(10);
  Keyboard.releaseAll();
}

void xplus(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('u');
  
  delay(10);
  Keyboard.releaseAll();
  
}
void yplus(){
  Keyboard.begin();
 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('w');
  
  delay(10);
  Keyboard.releaseAll();
}
void zplus(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('o');
 
  delay(10);
  Keyboard.releaseAll();
  
}
void xminus(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('p');
  
  delay(10);
  Keyboard.releaseAll();
}
void yminus(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
   
  delay(10);
  Keyboard.releaseAll();
}
void zminus(){
    Keyboard.begin();
    
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('l');
    
  delay(10);
  Keyboard.releaseAll();
}
void xzero(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('x');  
  delay(10);
  Keyboard.releaseAll();
}
void yzero(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('y');  
  delay(100);
  Keyboard.releaseAll();
}
void pokus(){
 Keyboard.begin();
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('p');  
  delay(100);
  Keyboard.releaseAll();
}
void zzero(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('z'); 
  delay(100);
  Keyboard.releaseAll();
}
void zeroall(){
  Keyboard.begin();
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('z'); 
  delay(100);
  Keyboard.releaseAll();
}
void click1() {
  //Serial.println("Button 1 click.");

          osa = osa + 1;
          if (osa >3) {
            osa = 0;
          }
          delay(10);
prepoc();
      disp();
      Serial.println("osa:" + String(osa));
     Serial.println("krok: " + String(krok));
          
} 

void doubleclick1() {
  //Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
 // Serial.println("Button 1 longPress start");
} // longPressStart1


// This function will be called often, while the button1 is pressed for a long time.
void longPress1() {
 // Serial.println("Button 1 longPress...");
} // longPress1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {

zeroall();



//  if (osa==1){
//    xzero();
//    //Serial.println("X-zero");
//  } else if (osa==2){
//    yzero();
//    //Serial.println("Y-zero");
//  } else {
//    zzero();
//   // Serial.println("Z-zero");}
//  
//} // longPressStop1
}

// ... and the same for button 2:

void click2() {
  //Serial.println("Button 2 click.");
  selekt=selekt+1;
  if (selekt >1){
    selekt=0;
  }
  if (selekt <0){
    selekt=0;
  }
  if ((1<=osa)&&(osa<=2)){
    
   if (krok == 0){
    xy01();
    }
   if (krok == 1){
      xy1();
      }
   if (krok == 2){
      xy10();  
      } 
      
     if (krok==3){
        xy100();
        }
      
     if (krok==4){
        xy1000();
        }   
  } 
  else {
    if (krok == 0){
    z01();
   } 
   if (krok == 1){
      z1();
      }
   if (krok ==2) {
      z10();  
      } 
   if (krok ==3) {
      z10();  
      } 
    }
  disp();
} // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2


void longPressStart2() {
  Serial.println("Button 2 longPress start");
} // longPressStart2


void longPress2() {
  Serial.println("Button 2 longPress...");
} // longPress2

void longPressStop2() {
  Serial.println("Button 2 longPress stop");
} // longPressStop2

void disp()  {
   display.clearDisplay();
 display.drawRoundRect(1, 1, display.width()-2, display.height()-2, 4, SSD1306_WHITE);
  display.drawFastHLine(1, 15,127, SSD1306_WHITE ) ;
 display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(8,4);// Draw white text
  display.println(" Osa ");
  display.drawFastHLine(1, 15,127, SSD1306_WHITE ) ;
  display.setCursor(50,4);             // Start at top-left corner
  display.println(" Posun " );
 display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(13,29);             // Start at top-left corner
  display.println(disposa);
  display.drawFastVLine(35, 1,63, SSD1306_WHITE ) ;
  display.setCursor(50,29);             // Start at top-left corner
  display.println(dispkrok);
   if (selekt==0){
    display.drawFastHLine(5, 58,27, SSD1306_WHITE ) ; 
  }
  if (selekt==1){
    display.drawFastHLine(40, 58,80, SSD1306_WHITE ) ; 
  }
  display.display();
 
}

void prepoc(){
  if (osa == 1){
    disposa = "X";
    }else if (osa ==2){
    disposa = "Y";
    } else if (osa ==3){
    disposa = "Z";  
    } 


  if (krok == 0){
    dispkrok = "0.1 mm";
  }else if (krok == 1){
    dispkrok = "1 mm";
    }else if (krok == 2){
    dispkrok = "1 cm";
    }else if (krok == 3){
    dispkrok = "10 cm";
    }else if (krok == 4){
    dispkrok = "100 cm";
    } else {
      krok = 0;}
    
}

void rot1(){
   static int pos1 = 0;
   encoder1.tick();
   int newPos1 = encoder1.getPosition();
     if (pos1 != newPos1 ) {
      if (newPos1>pos1){
        if (osa == 3){
          zplus();
          } else if (osa == 2){
            yplus();
            } else {
              xplus();
              }
        
       else {
        if (osa == 3){
          zminus();
          } else if (osa == 2){
            yminus();
            } else {
              xminus();
              }
        
      }
      
      pos1 = newPos1;
      //Serial.println("osa: " + String(osa));
      display.fillScreen(SSD1306_WHITE);
      display.display();
      delay(10);
      prepoc();
      disp();
      }
  
}

void rot2(){
     static int pos2 = 0;
   encoder2.tick();
   int newPos2 = encoder2.getPosition();
     if (pos2 != newPos2 ) {
      if (newPos2>pos2){
        if (selekt == 0 ){
          osa = osa + 1;
          if (osa >3) {
            osa = 3;
          }
          
          } else {
           krok = krok + 1;
           if (osa==3){
            if (krok==4){
              krok=3;}
           } else {
            if (krok==5){
           
              krok=4;}}
              
          }} else if (newPos2<pos2){
        if (selekt == 0 ){
          osa = osa - 1;
          if (osa <1) {
            osa = 1;}
          } else {
            krok = krok - 1;
            if (krok==-1){
              krok=0;}
              }
      }
     
     Serial.println("osa:" + String(osa));
     Serial.println("krok: " + String(krok));
      pos2 = newPos2;
     
     
display.fillScreen(SSD1306_WHITE);
display.display();
delay(10);
prepoc();
      disp();
      }
  

  
}

void loop() {
  button1.tick();
  button2.tick();
  rot1();
  rot2();
}
