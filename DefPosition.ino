int curseurPosition = 0;
int positionVoulue = 0;
int signePosition = 1;

void DefPosition(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction

  if(OrigineAutoOK == false){
  lcd.print("Fait OrigineAuto");
  lcd.setCursor(0,1);
  lcd.print("      Avant     ");
  delay(2000);
  lcd.clear();
  }

  lcd.clear();
  lcd.print("Definir position");
  lcd.setCursor(0,1);
  lcd.print(" Entrer Valeur  ");

  delay(800);

  char posi[8];
  sprintf(posi, "%.5d", positionVoulue);
  
  lcd.clear();
  lcd.print("Definir position");
  lcd.setCursor(0,1);
    if(posi[0] == 32){
    posi[0] = 48;
  }
  if(posi[1] == 32){
    posi[1] = 48;
  }
    if(posi[2] == 32){
    posi[2] = 48;
  }
    if(posi[3] == 32){
    posi[3] = 48;
  }
  lcd.print("+");
  lcd.print(posi[1]);
  lcd.print(posi[2]);
  lcd.print(posi[3]);
  lcd.print(posi[4]);
  lcd.print(" (");
  lcd.print(positionMin);
  lcd.print(":");
  lcd.print(positionMax);
  lcd.print(")");
  
  curseurPosition = 1;
  lcd.setCursor(curseurPosition,1);
  lcd.blink();

    while(token == true){
 
     lcd_key = read_LCD_buttons();
    
    if(lcd_key != memoire_bouton){
      
        switch(lcd_key){
          case btnUP:
            if(curseurPosition > 0 && curseurPosition < 5){
              if(posi[curseurPosition] < 57){
              posi[curseurPosition] = posi[curseurPosition] + 1;
              lcd.print(posi[curseurPosition]);
              lcd.setCursor(curseurPosition,1);
              }
            }
            if(curseurPosition == 0){
              signePosition = 1;
              lcd.print("+");
              lcd.setCursor(curseurPosition,1);
            }
            break;
          case btnDOWN:
            if(curseurPosition > 0 && curseurPosition < 5){
              if(posi[curseurPosition] > 48){
              posi[curseurPosition] = posi[curseurPosition] - 1;
              lcd.print(posi[curseurPosition]);
              lcd.setCursor(curseurPosition,1);
              }
            }
            if(curseurPosition == 0){
              signePosition = -1;
              lcd.print("-");
              lcd.setCursor(curseurPosition,1);
            }
            break;
          case btnLEFT:
                if(curseurPosition > 0){
               curseurPosition = curseurPosition - 1;
               lcd.setCursor(curseurPosition,1);
                }
            break;
          case btnRIGHT:
                if(curseurPosition < 4){
               curseurPosition = curseurPosition + 1;
               lcd.setCursor(curseurPosition,1);
                }
            break;
          case btnSELECT:
                char positionFinale[4];
                positionFinale[0] = posi[1];
                positionFinale[1] = posi[2];
                positionFinale[2] = posi[3];
                positionFinale[3] = posi[4];
                positionVoulue = atoi (positionFinale);
                if(positionVoulue >= positionMin && positionVoulue <= positionMax){
                  allerA(signePosition*positionVoulue);  
                }
                else{
                  lcd.clear();
                  lcd.print("! Hors limites !");
                  delay(2000);
                  lcd.clear();
                  DefPosition();
                }

                if(stepper.currentPosition()==positionVoulue){
                  token = false;
                }
            break;
          default:
            break;
        }
      }
        memoire_bouton = lcd_key;
  }
  
}
