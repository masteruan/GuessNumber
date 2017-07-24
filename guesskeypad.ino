
#include <LiquidCrystal.h>
 // select the pins used on the LCD panel
 LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

 #define attempts 5 // define numbers of attempts

 // define some values used by the panel and buttons
 int lcd_key     = 0;
 int adc_key_in  = 0;
 int sel_number = 50;
 int num_secret;
 int tent = attempts;
 int light = 50;
 int buttonDelay = 30;
 boolean lcdLux = false;

 #define btnRIGHT  0
 #define btnUP     1
 #define btnDOWN   2
 #define btnLEFT   3
 #define btnSELECT 4
 #define btnNONE   5


 // read the buttons
 int read_LCD_buttons()
 {
   adc_key_in = analogRead(0);      // read the value from the sensor 
   if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
   if (adc_key_in < 50)   return btnRIGHT;  
   if (adc_key_in < 195)  return btnUP; 
   if (adc_key_in < 380)  return btnDOWN; 
   if (adc_key_in < 555)  return btnLEFT; 
   if (adc_key_in < 790)  return btnSELECT;   
   return btnNONE;  // when all others fail, return this...
 }

 void setup()
 {
   Serial.begin(9600);
   randomSeed(analogRead(3));
   lcd.begin(16, 2);
   lcd.setCursor(0,0);
   lcd.print("Right for Secret");
   num_secret = random(0,100);
   Serial.println("START!");
   Serial.print("Number secret is: ");
   Serial.println(num_secret);
   pinMode(10, OUTPUT);
 }
 
 void loop() {
   if (lcdLux) {
     light = 200;
   }
   else
   {
     light = 50;
   }
   
   analogWrite(10, light);
   lcd.setCursor(0,1);
   lcd.print("Your Number: ");
   lcd.setCursor(13,1);
   lcd.print(sel_number);
   lcd_key = read_LCD_buttons();
 
 switch (lcd_key)
 {
    case btnRIGHT:
    {
      num_secret = random(0,100);
      Serial.println("BUTTON Secret");
      Serial.print("Number secret is: ");
      Serial.println(num_secret);
      tent = attempts;
      Serial.println(num_secret);
      lcd.setCursor(0,0);
      lcd.print("Secret number OK");
      delay(2000);
      lcd.clear();
    break;
    }
    
    case btnLEFT:
    {  
      if (buttonDelay != 0) {
        buttonDelay--;
      }
      else {
        lcdLux = !lcdLux;
        buttonDelay = 50;
      }
    break;
    }
   
    case btnUP:
    {
      if (buttonDelay != 0) {
        buttonDelay--;
      }
      else {
        if (sel_number >= 100) {
        }
        else
        {
          lcd.clear();
          sel_number++;
          buttonDelay = 30;
        }
      }
    break;
   }
   
    case btnDOWN:
    {
      if (buttonDelay != 0) {
        buttonDelay--;
      }
      else {
        if (sel_number <= 0) { 
        }
        else
        {
          lcd.clear();
          sel_number--;
          buttonDelay = 30;
        }
      }
    break;
    }
   
    case btnSELECT:
    {  
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("TRY...");
      delay(800);
      
      tent = tent - 1;
      if (sel_number < num_secret) {
          lcd.setCursor(0,0);
          lcd.print("Secret number is");
          lcd.setCursor(0,1);
          lcd.print("Higher!");
          delay(2000);
        }
        else if (sel_number > num_secret) {
          lcd.setCursor(0,0);
          lcd.print("Secret number is");
          lcd.setCursor(0,1);
          lcd.print("Lower!");
          delay(2000);          
        }
        else {
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("Well DONE!!");
          delay(3000);
          lcd.clear();
          num_secret = random(0,100);
          Serial.println("WELL DONE!");
          Serial.print("Number secret is: ");
          Serial.println(num_secret);
          tent = attempts;
          lcd.setCursor(0,0);
          lcd.println("Secret number OK");
          delay(1000);
        }
      if (tent == 0) {
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("GAME");
      lcd.setCursor(6,1);
      lcd.print("OVER");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The secret");
      lcd.setCursor(0,1);
      lcd.print("number was ");
      lcd.setCursor(12,1);
      lcd.print(num_secret);
      delay(2000);
      lcd.clear();
      num_secret = random(0,100);
      Serial.println("GAME OVER!");
      Serial.print("Number secret is: ");
      Serial.println(num_secret);
      tent = attempts;
      lcd.setCursor(0,0);
      lcd.println("Secret number OK");
      delay(1000);
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Leaves only");
      lcd.setCursor(12,0);
      lcd.print(tent);
      lcd.setCursor(0,1);
      lcd.print("attempts...");
      delay(1500);
      break;
    }
   
    case btnNONE:
    {
      delay(30);
      break;
    }
  }
}
