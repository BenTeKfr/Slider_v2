long echelle(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int lecturePad(int S){
  long Y = analogRead(PinPadY);

  switch(S){
    case 1:
      Y = echelle(Y, 1023, 0, -200, 200);
        if (Y<=12 && Y >= -12){
        return(0);
        }
      break;
    case 2:
      Y = echelle(Y, 1023, 0, -400, 400);
        if (Y<=16 && Y >= -16){
        return(0);
        }
      break;
    case 3:
      Y = echelle(Y, 1023, 0, -800, 800);
        if (Y<=32 && Y >= -32){
        return(0);
        }
      break;
    case 4:
      Y = echelle(Y, 1023, 0, -1000, 1000);
        if (Y<=64 && Y >= -64){
        return(0);
        }
      break;
    case 5:
      Y = echelle(Y, 1023, 0, -1500, 1500);
        if (Y<=64 && Y >= -64){
        return(0);
        }
      break;
    case 6:
      Y = echelle(Y, 1023, 0, -2000, 2000);
        if (Y<=96 && Y >= -96){
        return(0);
        }
      break;
    default:
      Y = 0;
      break;
  }

    return(Y);

}

void VitesseManuPad(){
  //Initialisation
  
  lcd.clear();
  
  token = true; //Prise du token de fonction
  lcd.print("Vitesse Manu Pad");
  lcd.setCursor(0,1);
  lcd.print("JoyStick G/D + S");

  delay(1500);

  lcd.clear();
  lcd.print("Vitesse Manu Pad");
  lcd.setCursor(0,1);
  lcd.print("S:");
  lcd.print(sensiPad);

  //Boucle de la fonction

  while(token == true){
    setVitesseMot(vitesse); 
        
 lcd_key = read_LCD_buttons();
 
    if(lcd_key != memoire_bouton){
      
       lcd.setCursor(2,1);
       
    switch(lcd_key){
      case btnUP:
          if(sensiPad < 6){
            sensiPad = sensiPad + 1;
            lcd.print(sensiPad);
          }
        break;
      case btnDOWN:
          if(sensiPad > 1){
            sensiPad = sensiPad - 1;
            lcd.print(sensiPad);
          }
        break;
      case btnLEFT:
          if(sensiPad > 1){
            sensiPad = sensiPad - 1;
            lcd.print(sensiPad);
          }
        break;
      case btnRIGHT:
          if(sensiPad < 6){
            sensiPad = sensiPad + 1;
            lcd.print(sensiPad);
          }
        break;
      case btnSELECT:
            if (vitesse == 0){
              token = false;  // Condition de sortie
            }
            else{
              vitesse = 0;
              lcd.setCursor(5,1);
              lcd.print("RAZ");
              delay(1500);
              lcd.setCursor(5,1);
              lcd.print("   ");
            }
        break;
      default:
        break;
    }
  }
    memoire_bouton = lcd_key;

  vitesse = lecturePad(sensiPad);
  //refreshVitesse();
  }
  
  }
