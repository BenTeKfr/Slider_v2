byte flecheBas[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
};

byte flecheHaut[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
};

byte flecheBasHaut[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
};

void Programmes(){

  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("   Choisir le   ");
  lcd.setCursor(0,1);
  lcd.print("   Programme    ");

  delay(1500);
          lcd.clear();
          lcd.print("   En continue  ");
          lcd.setCursor(0,1);
          lcd.print("<--     ");
          lcd.createChar(2, flecheBas);  
          lcd.setCursor(8,1);
          lcd.write(byte(2));
          lcd.setCursor(9,1);
          lcd.print("    -->");
  
  //Boucle de la fonction
  int num_prog = 0;
  int new_num_prog = 0;

  while(token == true){
    
    if(new_num_prog != num_prog){
      num_prog = new_num_prog;
      switch(num_prog){
          case 0:
            lcd.clear();
            lcd.print("   En continue  ");
            lcd.setCursor(0,1);
            lcd.print("<--     ");
            lcd.createChar(2, flecheBas);  
            lcd.setCursor(8,1);
            lcd.write(byte(2));
            lcd.setCursor(9,1);
            lcd.print("    -->");
          break;
          case 1:            
            lcd.clear();
            lcd.print("Gauss croissante");
            lcd.setCursor(0,1);
            lcd.print("<--     ");
            lcd.createChar(3, flecheBasHaut);  
            lcd.setCursor(8,1);
            lcd.write(byte(3));
            lcd.setCursor(9,1);
            lcd.print("    -->");
          break;
          case 2:
            lcd.clear();
            lcd.print("Gauss decroissan");
            lcd.setCursor(0,1);
            lcd.print("<--     ");
            lcd.createChar(3, flecheBasHaut);  
            lcd.setCursor(8,1);
            lcd.write(byte(3));
            lcd.setCursor(9,1);
            lcd.print("    -->");
          break;
          case 3:
            lcd.clear();
            lcd.print(" Lin croissante ");
            lcd.setCursor(0,1);
            lcd.print("<--     ");
            lcd.createChar(3, flecheBasHaut);  
            lcd.setCursor(8,1);
            lcd.write(byte(3));
            lcd.setCursor(9,1);
            lcd.print("    -->");
          break;
          case 4:
            lcd.clear();
            lcd.print("Lin decroissante");
            lcd.setCursor(0,1);
            lcd.print("<--     ");
            lcd.createChar(4, flecheHaut);  
            lcd.setCursor(8,1);
            lcd.write(byte(4));
            lcd.setCursor(9,1);
            lcd.print("    -->");
          break;
      }
    }

     lcd_key = read_LCD_buttons();

      if(lcd_key != memoire_bouton){
          lcd.setCursor(0,1);
          switch(lcd_key){
            case btnUP:
                 if(num_prog > 0){
                  new_num_prog--;
                 }
              break;
            case btnDOWN:
                 if(num_prog < 4){
                  new_num_prog++;
                 }
              break;
            case btnLEFT:
                 //aller a la position max droite
                 allerA(positionMax);
                 //definir l'allure pour aller à la gauche selon le num_prog
                 switch(num_prog){
                  case 0:
                    allerA(positionMin, vitesseProg, 10000);
                  break;
                  case 1:
                    allerA(positionMin);
                  break;
                  case 2:
                    allerA(positionMin, vitesseProg, -acceleration);
                  break;
                  case 3:
                  break;
                  case 4:
                  break;
                 }
                  
                 
              break;
            case btnRIGHT:
                 //aller a la position max gauche
                 allerA(positionMin);
                 //definir l'allure pour aller à la droite selon le num_prog
                 switch(num_prog){
                  case 0:
                    allerA(positionMax, vitesseProg, 10000);
                  break;
                  case 1:
                    allerA(positionMax);
                  break;
                  case 2:
                    allerA(positionMax, vitesseProg, -acceleration);
                  break;
                  case 3:
                  break;
                  case 4:
                  break;
                 }
              break;
            case btnSELECT:
                    token = false;  // Condition de sortie
          }
      }
      memoire_bouton = lcd_key;
  }
}
