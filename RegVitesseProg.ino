
void RegVitesseProg(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("Vitesse Prog :  ");
  lcd.setCursor(0,1);
  lcd.print(" Entrer Valeur  ");

  delay(800);
  
  EEPROM.get(10,vitesseProg);
  if(isnan(vitesseProg)){
    EEPROM.put(10, 800);
    EEPROM.get(10,vitesseProg);
  }
  char vitprog[8];
  sprintf(vitprog, "%.5d", vitesseProg);
  
  lcd.clear();
  lcd.print("Vitesse Prog :  ");
  lcd.setCursor(7,1);
  lcd.print("pas/sec ");
  lcd.setCursor(1,1);
  if(vitprog[1] == 32){
    vitprog[1] = 48;
  }
  lcd.print(vitprog[1]);
  lcd.print(vitprog[2]);
  lcd.print(vitprog[3]);
  lcd.print(vitprog[4]);
  
  curseurVitesseProg = 2;
  lcd.setCursor(curseurVitesseProg,1);
  lcd.blink();

  while(token == true){
 
     lcd_key = read_LCD_buttons();
    
    if(lcd_key != memoire_bouton){
      
        switch(lcd_key){
          case btnUP:
            if(curseurVitesseProg > 0 && curseurVitesseProg < 5){
              if(vitprog[curseurVitesseProg] < 57){
              vitprog[curseurVitesseProg] = vitprog[curseurVitesseProg] + 1;
              lcd.print(vitprog[curseurVitesseProg]);
              lcd.setCursor(curseurVitesseProg,1);
              }
            }
            break;
          case btnDOWN:
            if(curseurVitesseProg > 0 && curseurVitesseProg < 5){
              if(vitprog[curseurVitesseProg] > 48){
              vitprog[curseurVitesseProg] = vitprog[curseurVitesseProg] - 1;
              lcd.print(vitprog[curseurVitesseProg]);
              lcd.setCursor(curseurVitesseProg,1);
              }
            }
            break;
          case btnLEFT:
                if(curseurVitesseProg > 1){
               curseurVitesseProg = curseurVitesseProg - 1;
               lcd.setCursor(curseurVitesseProg,1);
                }
            break;
          case btnRIGHT:
                if(curseurVitesseProg < 4){
               curseurVitesseProg = curseurVitesseProg + 1;
               lcd.setCursor(curseurVitesseProg,1);
                }
            break;
          case btnSELECT:
                char vitesseProgWrite[4];
                vitesseProgWrite[0] = vitprog[1];
                vitesseProgWrite[1] = vitprog[2];
                vitesseProgWrite[2] = vitprog[3];
                vitesseProgWrite[3] = vitprog[4];
                vitesseProg = atoi (vitesseProgWrite);
                EEPROM.put(10, vitesseProg);
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
