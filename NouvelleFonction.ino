void nouvelleFonction(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("    Nouvelle   ");
  lcd.setCursor(0,1);
  lcd.print(" Fonction ");

  delay(1500);
  lcd.clear();

  lcd.print("    Amusez   ");
  lcd.setCursor(0,1);
  lcd.print(" Vous ");
  
  //Boucle de la fonction

  while(token == true){

    
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
