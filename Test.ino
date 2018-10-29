void Test(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("    Mode TEST   ");
  lcd.setCursor(0,1);
  lcd.print(" Carre = retour ");

  delay(1500);
  lcd.clear();
  
  //Boucle de la fonction

  while(token == true){

      lcd.setCursor(0,0);
      lcd.print("FC1:");
      lcd.print(digitalRead(PinFC1));
      lcd.setCursor(0,1);
      lcd.print("FC2:");
      lcd.print(digitalRead(PinFC2));

    
          lcd_key = read_LCD_buttons();

          if(lcd_key != memoire_bouton){
              switch(lcd_key){
                case btnUP:
                     
                  break;
                case btnDOWN:
                     
                  break;
                case btnLEFT:
                     
                  break;
                case btnRIGHT:
                     
                  break;
                case btnSELECT:
                      if (vitesse == 0){
                        token = false;  // Condition de sortie
                      }
                      else{
                        vitesse = 0;
                      }
                  break;
                default:
                  break;
              }
  }
    memoire_bouton = lcd_key;
}


}
