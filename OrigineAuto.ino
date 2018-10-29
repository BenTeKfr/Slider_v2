byte chapeauBas[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B10101,
};

byte petitTrait[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000,
};

void OrigineAuto(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.createChar(0, chapeauBas);
  lcd.setCursor(0,0);  
  lcd.write(byte(0));
  lcd.print("     pour      ");
  lcd.createChar(1, petitTrait);
  lcd.setCursor(0,1);  
  lcd.write(byte(1));
  lcd.print("  Origine Auto ");
  delay(800);
  

  //Boucle de la fonction

  int FirstFC = 0;

  while(token == true){
            lcd_key = read_LCD_buttons();
        
        if(lcd_key != memoire_bouton){
        
            switch(lcd_key){
              case btnUP:

              lcd.blink();
                //-- Sequence OrigineAuto --
                
                //Deplacement vers un fin de course avec vitesseProg
                lcd.clear();
                lcd.print("Deplacement vers");
                lcd.setCursor(0,1);
                lcd.print("   premier FC   ");
                
                while(digitalRead(PinFC1) + digitalRead(PinFC2)!= true){
                 setVitesseMot(vitesseProg);
                }
                setVitesseMot(0);
                
                //On regarde quel capteur a été touché
                FirstFC = 0;
                if(digitalRead(PinFC1) == true){
                  FirstFC = 1;
                  lcd.clear();
                  lcd.print("      FC1       ");
                  lcd.setCursor(0,1);
                  lcd.print("     touche     ");
                }
                else if(digitalRead(PinFC2) == true){
                  FirstFC = 2;
                  lcd.clear();
                  lcd.print("      FC2       ");
                  lcd.setCursor(0,1);
                  lcd.print("     touche     ");
                }
                delay(1500);
                
                //setCurrentPosition pour mettre à zéro dès que le fin de course est atteint
                stepper.setCurrentPosition(0);
                  lcd.clear();
                  lcd.print(" Initialisation ");
                  lcd.setCursor(0,1);
                  lcd.print("Mise a l'origine");
                delay(2000);
                
                
                //Deplacement vers l'autre fin de course avec -vitesseProg
                  lcd.clear();
                  lcd.print("Deplacement vers");
                  lcd.setCursor(0,1);
                  lcd.print("   second FC    ");
                switch(FirstFC){
                  case 1:
                    while(digitalRead(PinFC2)!= true){
                      setVitesseMot(-vitesseProg);
                    }
                    setVitesseMot(0);
                    lcd.clear();
                    lcd.print("      FC2       ");
                    lcd.setCursor(0,1);
                    lcd.print("     touche     ");
                  break;
                  case 2:
                    while(digitalRead(PinFC1)!= true){
                      setVitesseMot(-vitesseProg);
                      }
                      setVitesseMot(0);
                    lcd.clear();
                    lcd.print("      FC1       ");
                    lcd.setCursor(0,1);
                    lcd.print("     touche     ");
                  break;
                  default:
                  break;
                }
                delay(1500);
                
                //Sauvegarde de la valeur currentPosition => nombre de pas moteur pour la longueur de l'axe
                lcd.clear();
                lcd.print("Sauvegarde de la");
                lcd.setCursor(0,1);
                lcd.print("    longueur    ");
                delay(1500);
                longueurPas = stepper.currentPosition();
                EEPROM.put(20, longueurPas);
                lcd.clear();
                lcd.print(" Sauvegarde OK  ");
                lcd.setCursor(0,1);
                lcd.print("L=");
                lcd.print(longueurPas);
                delay(3000);
                
                //Division du nombre de pas de longueur par 2 pour avoir la valeur milieu
                valeurMilieu = longueurPas / 2;
                lcd.clear();
                lcd.print(" Valeur Milieu  ");
                lcd.setCursor(0,1);
                lcd.print("M=");
                lcd.print(valeurMilieu);
                delay(3000);
                
                //SetCurrentPosition à l'origine
                lcd.clear();
                lcd.print("Deplacement vers");
                lcd.setCursor(0,1);
                lcd.print("M=");
                lcd.print(valeurMilieu);
                allerA(valeurMilieu);
                if(stepper.currentPosition() == valeurMilieu){
                  delay(800);
                  stepper.setCurrentPosition(0);
                   lcd.clear();
                   lcd.print("   Origine OK   ");
                }
                delay(1500);
                
                //PositionMin = - nombre de pas de longueur / 2
                  positionMin = longueurPas / 2;
                  
                //PositionMax = + nombre de pas de longueur / 2
                  positionMax = - longueurPas / 2;

                   lcd.clear();
                   lcd.print("Min:");
                   lcd.print(positionMin);
                   lcd.setCursor(0,1);
                   lcd.print("Max:");
                   lcd.print(positionMax);
                delay(3000);

                //allerA(positionMin);
                //allerA(positionMax);
                  
                //Ecrire PositionMin et PositionMax dans l'EEPROM
                lcd.clear();
                lcd.print("Ecriture memoire");
                lcd.setCursor(6,1);
                lcd.print(".");
                delay(500);
                lcd.print(".");
                EEPROM.put(30, positionMin);
                delay(500);
                lcd.print(".");
                delay(500);
                lcd.print(".");
                EEPROM.put(40, positionMax);
                delay(500);
                lcd.clear();
                lcd.print("Ecriture memoire");
                lcd.setCursor(6,1);              
                lcd.print("OK !");
                delay(1000);
                lcd.noBlink();

                //Retour au menu OrigineAuto
                   OrigineAutoOK = true;
                   OrigineAuto();

                break;
              case btnDOWN:
                break;
              case btnLEFT:
                break;
              case btnRIGHT:
                break;
              case btnSELECT:
                      vitesse = 0;
                      token = false;  // Condition de sortie
                break;
              default:
                break;
            }
          }
         
  }
  }
