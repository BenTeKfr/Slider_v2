void Credits(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print(" www.BenTeK.fr  ");
  lcd.setCursor(0,1);
  lcd.print("Version 1.2     ");

  delay(500);

  //Boucle de la fonction

  while(token == true){
    lcd_key = read_LCD_buttons();
  if(lcd_key != memoire_bouton){
    token = false;  // Condition de sortie
    }
    memoire_bouton = lcd_key;
  }
}
