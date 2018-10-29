
int curseurAcceleration;

void RegAcceleration(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("Acceleration :  ");
  lcd.setCursor(0,1);
  lcd.print(" Entrer Valeur  ");

  delay(800);
  
  char accel[8]; // Buffer big enough for 7-character float
  dtostrf(acceleration, 6, 2, accel);
  
  lcd.clear();
  lcd.print("Acceleration :  ");
  lcd.setCursor(7,1);
  lcd.print("pas/sec2");
  lcd.setCursor(0,1);
  if(accel[0] == 32) {
    accel[0] == 48;
  }
  if(accel[1] == 32){
    accel[1] = 48;
  }
  lcd.print(accel[0]);
  lcd.print(accel[1]);
  lcd.print(accel[2]);
  lcd.print(accel[3]);
  lcd.print(accel[4]);
  lcd.print(accel[5]);
  curseurAcceleration = 2;
  lcd.setCursor(curseurAcceleration,1);
  lcd.blink();

  while(token == true){
 
     lcd_key = read_LCD_buttons();
    
    if(lcd_key != memoire_bouton){
      
        switch(lcd_key){
          case btnUP:
            if(curseurAcceleration >= 0 && curseurAcceleration < 6 && curseurAcceleration != 3){
              if(accel[curseurAcceleration] < 57){
              accel[curseurAcceleration] = accel[curseurAcceleration] + 1;
              lcd.print(accel[curseurAcceleration]);
              lcd.setCursor(curseurAcceleration,1);
              }
            }
            break;
          case btnDOWN:
            if(curseurAcceleration >= 0 && curseurAcceleration < 6 && curseurAcceleration != 3){
              if(accel[curseurAcceleration] > 48){
              accel[curseurAcceleration] = accel[curseurAcceleration] - 1;
              lcd.print(accel[curseurAcceleration]);
              lcd.setCursor(curseurAcceleration,1);
              }
            }
            break;
          case btnLEFT:
          if(curseurAcceleration > 0){
               curseurAcceleration = curseurAcceleration - 1;
               lcd.setCursor(curseurAcceleration,1);
          }
            break;
          case btnRIGHT:
          if(curseurAcceleration < 5){
               curseurAcceleration = curseurAcceleration + 1;
               lcd.setCursor(curseurAcceleration,1);
          }
            break;
          case btnSELECT:
                acceleration = atof (accel);
                EEPROM.put(0, acceleration);
                lcd.clear();
                lcd.print("Ecriture memoire");
                lcd.setCursor(6,1);
                lcd.print(".");
                delay(500);
                lcd.print(".");
                delay(500);
                lcd.print(".");
                delay(500);
                lcd.print(".");
                delay(500);
                lcd.clear();
                lcd.print("Ecriture memoire");
                lcd.setCursor(6,1);              
                lcd.print("OK !");
                delay(1000);
                lcd.noBlink();
                token = false;
            break;
          default:
            break;
        }
      }
        memoire_bouton = lcd_key;
  }

}
