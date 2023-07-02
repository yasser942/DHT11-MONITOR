#include <dht.h>
#include <LiquidCrystal_I2C.h>

dht DHT;
LiquidCrystal_I2C lcd(0x3f,16,2);
#define button_pin 2
#define DHT11_PIN 7
int btnState =0;
char LCD_LANGUAGE = 'E';

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop(){
  btnState = digitalRead(button_pin);
  Serial.print(btnState);
  int chk = DHT.read11(DHT11_PIN);
  if(btnState == HIGH){
    lcd.clear();
    change_language();
    delay(100);
  }
  if(LCD_LANGUAGE == 'E'){
    lcd.setCursor(0,0);
    if(((DHT.temperature)*1.8+32)<100)
      lcd.print("TEM(F): ");
    else
      lcd.print("TEM(F):");
    lcd.print((DHT.temperature)*1.8+32);
    lcd.setCursor(14,0);
    lcd.print("EN");
    lcd.setCursor(0,1);
    if(DHT.humidity<100)
      lcd.print("HUM(%): ");
    else
      lcd.print("HUM(%):");
    lcd.print(DHT.humidity);
  }else if(LCD_LANGUAGE == 'T'){
    lcd.setCursor(0,0);
    if(DHT.temperature<100)
      lcd.print("SIC(C): ");
    else
      lcd.print("SIC(C):");
    lcd.print(DHT.temperature);
    lcd.setCursor(14,0);
    lcd.print("TR");
    lcd.setCursor(0,1);
    if(DHT.humidity<100)
      lcd.print("NEM(%): ");
    else
      lcd.print("NEM(%):");
    lcd.print(DHT.humidity);
  }
}
void change_language(){
  if(LCD_LANGUAGE == 'E')
    LCD_LANGUAGE = 'T';
  else if(LCD_LANGUAGE =='T')
    LCD_LANGUAGE = 'E';
}