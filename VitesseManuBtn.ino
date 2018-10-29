void refreshVitesseManuBtn(){
  lcd.setCursor(9,1);
  lcd.print("       ");
  lcd.setCursor(9,1);
  lcd.print(vitesse);
}

void VitesseManuBtn(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("Vitesse Manu Btn");
  lcd.setCursor(0,1);
  lcd.print("Fleche=V Carre=0");

  delay(1500);
  lcd.clear();
  lcd.print("Vitesse Manu Btn");
  refreshVitesseManuBtn();

  //Boucle de la fonction

  while(token == true){
    setVitesseMot(vitesse);    
        
 lcd_key = read_LCD_buttons();

if(lcd_key != memoire_bouton){
    lcd.setCursor(0,1);
    switch(lcd_key){
      case btnUP:
           lcd.print("+100     ");
           vitesse = vitesse + 100;
           refreshVitesseManuBtn();
        break;
      case btnDOWN:
           lcd.print("-100     ");
           vitesse = vitesse - 100;
           refreshVitesseManuBtn();
        break;
      case btnLEFT:
           lcd.print("-10      ");
           vitesse = vitesse - 10;
           refreshVitesseManuBtn();
        break;
      case btnRIGHT:
           lcd.print("+10      ");
           vitesse = vitesse + 10;
           refreshVitesseManuBtn();
        break;
      case btnSELECT:
            if (vitesse == 0){
              token = false;  // Condition de sortie
            }
            else{
              lcd.print("RAZ      ");
              vitesse = 0;
              refreshVitesseManuBtn();
            }
        break;
      default:
        break;
    }
  }
    memoire_bouton = lcd_key;
  }
  
}

