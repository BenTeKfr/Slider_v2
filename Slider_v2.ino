#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

//Variables de controle moteur pas à pas
#define PinVitesse 45
#define PinDirection 39
#define PinAlimMoteur 37
AccelStepper stepper(1,PinVitesse,PinDirection);
volatile int vitesse = 0;
int vitesseProg;
int curseurVitesseProg;
float acceleration;

//Variables pour les fins de courses
#define PinFC1 26
#define PinFC2 28

//Variables pour écran LCD avec mini-clavier
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
int memoire_bouton = 0;
#define btnNONE   0
#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   3
#define btnLEFT   4
#define btnSELECT 5

//Variables pour JoyPad
int PadX = 0;
int PadY = 0;
int sensiPad = 1;
#define PinPadX 8
#define PinPadY 9
#define PinPadBtn 18

//Controle de postion
long longueurPas = 0;
long valeurMilieu = 0;
long positionMin = 0;
long positionMax = 0;
bool OrigineAutoOK = false;

//Fonction de lecture des boutons sur le module LCD
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 if (adc_key_in > 1000) return btnNONE; 
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;
 return btnNONE;  // when all others fail, return this...
}

void ARU(){
  vitesse = 0;
  digitalWrite(PinAlimMoteur, HIGH);
  lcd.setCursor(0,1);
  lcd.print("!ARRET URGENCE!!");
}

int setVitesseMot(int vitesse){
  if (vitesse == 0) {
                            digitalWrite(PinAlimMoteur, HIGH);
                            //Serial.print("Arret Moteur.");
                          }
                          else{
                            digitalWrite(PinAlimMoteur, LOW);
                          }
        stepper.setSpeed(vitesse);
        stepper.runSpeed();
        return(1);
}

void allerA(long pos){
                stepper.setMaxSpeed(vitesseProg);
                stepper.setAcceleration(acceleration);
                digitalWrite(PinAlimMoteur, LOW);
                stepper.moveTo(pos);
                while(stepper.currentPosition() != pos){
                  stepper.run();
                }
                stepper.stop();
                digitalWrite(PinAlimMoteur, HIGH);
}

void allerA(long pos, int vit, float accel){
                stepper.setMaxSpeed(vit);
                stepper.setAcceleration(accel);
                digitalWrite(PinAlimMoteur, LOW);
                stepper.moveTo(pos);
                while(stepper.currentPosition() != pos){
                  stepper.run();
                }
                stepper.stop();
                digitalWrite(PinAlimMoteur, HIGH);
                stepper.setMaxSpeed(vitesseProg);
                stepper.setAcceleration(acceleration);
}



void loadEEPROM(){
    EEPROM.get(0,acceleration);
  if(isnan(acceleration)){
    EEPROM.put(0, 100.00);
    EEPROM.get(0,acceleration);
  }
  
  EEPROM.get(10,vitesseProg);
    if(isnan(vitesseProg)){
    EEPROM.put(10, 400);
    EEPROM.get(10,vitesseProg);
  }
  
   EEPROM.get(20,longueurPas);
    if(isnan(longueurPas)){
    EEPROM.put(20, 0);
    EEPROM.get(20,longueurPas);
  }
  
    EEPROM.get(30,positionMin);
    if(isnan(positionMin)){
    EEPROM.put(30, 0);
    EEPROM.get(30,positionMin);
  }

    EEPROM.get(40,positionMax);
    if(isnan(positionMax)){
    EEPROM.put(40, 0);
    EEPROM.get(40,positionMax);
  }
  
}

void setup() {

  pinMode(PinVitesse,OUTPUT); //Vitesse
  pinMode(PinDirection,OUTPUT); //Direction
  pinMode(PinAlimMoteur,OUTPUT); //Active_Moteur (0:ON, 1:OFF)
  pinMode(PinPadBtn,INPUT_PULLUP); // Bouton du Pad
  //attachInterrupt(5, ARU, RISING); //Bouton du Pad (18) corresponds à l'interruption 5
  attachInterrupt(digitalPinToInterrupt(18), ARU, RISING);
  digitalWrite(PinAlimMoteur, HIGH);
  pinMode(PinFC1, INPUT_PULLUP);
  pinMode(PinFC2, INPUT_PULLUP);

  loadEEPROM();
  
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print(" www.BenTeK.fr"); // print a simple message
 lcd.setCursor(0,1);
 lcd.print("SliderCam v1 -->");

    TCCR5B = (TCCR5B & 0xF8) | 0x01 ;
    //Serial.begin(9600);
    stepper.setMaxSpeed(4000); //vitesse max du moteur en nombre de steps par seconde
    stepper.setSpeed(0);//Réglage de la vitesse du moteur
    stepper.setAcceleration(100);
    vitesse=0;
}

//Position dans le menu
int lvl_menu = 0;
bool token = false;


void MAJMenu(int numMenu){
  lvl_menu = numMenu;
  lcd.clear();
  
  switch(lvl_menu){
    case 0:
      lcd.setCursor(0,0);
      lcd.print(" www.BenTeK.fr");
      lcd.setCursor(0,1);
      lcd.print("SliderCam v1 -->");      
       break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Vitesse Manu Btn");
      lcd.setCursor(0,1);
      lcd.print("      1/10   -->");   
       break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Vitesse Manu Pad");
      lcd.setCursor(0,1);
      lcd.print("<--   2/10   -->");   
       break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("Reg Acceleration");
      lcd.setCursor(0,1);
      lcd.print("<--   3/10   -->");  
       break;
    case 4:
      lcd.setCursor(0,0);
      lcd.print("Reg Vitesse Prog");
      lcd.setCursor(0,1);
      lcd.print("<--   4/10   -->"); 
       break;
    case 5:
      lcd.setCursor(0,0);
      lcd.print("  Origine Auto  ");
      lcd.setCursor(0,1);
      lcd.print("<--   5/10   -->"); 
       break;
    case 6:
      lcd.setCursor(0,0);
      lcd.print("  Def Position  ");
      lcd.setCursor(0,1);
      lcd.print("<--   6/10   -->"); 
       break;
    case 7:
      lcd.setCursor(0,0);
      lcd.print(" Controle Serie ");
      lcd.setCursor(0,1);
      lcd.print("<--   7/10   -->"); 
       break;
    case 8:
      lcd.setCursor(0,0);
      lcd.print("      Test      ");
      lcd.setCursor(0,1);
      lcd.print("<--   8/10   -->"); 
       break;
    case 9:
      lcd.setCursor(0,0);
      lcd.print("   Programmes   ");
      lcd.setCursor(0,1);
      lcd.print("<--   9/10   -->"); 
       break;
    case 10:
      lcd.setCursor(0,0);
      lcd.print("    Credits     ");
      lcd.setCursor(0,1);
      lcd.print("<--   10/10     "); 
       break;
    default:
       ErreurFonction();
       break;
  }
}

void loop() {

  lcd_key = read_LCD_buttons();

    // Si le bouton a un état différent de celui enregistré ET
    // que cet état est "appuyé"

  if(lcd_key != memoire_bouton){
    switch(lcd_key){
      case btnUP:
        break;
      case btnDOWN:
        break;
      case btnLEFT:
        if(lvl_menu != 1){
        MAJMenu(lvl_menu-1);        
        }
        break;
      case btnRIGHT:
        if(lvl_menu != 10){
        MAJMenu(lvl_menu+1);        
        }
        break;
      case btnSELECT:
        switch(lvl_menu){
          case 0:
            MAJMenu(lvl_menu+1);
            break;
          case 1:
            VitesseManuBtn();
            break;
          case 2:
            VitesseManuPad();
            break;
          case 3:
            RegAcceleration();
            break;
          case 4:
            RegVitesseProg();
            break;
          case 5:
            OrigineAuto();
            break;
          case 6:
            DefPosition();
            break;
          case 7:
            ControleSerie();
            break;
          case 8:
            Test();
            break;
          case 9:
            Programmes();
            break;
          case 10:
            Credits();
            break;
          default:
            ErreurFonction();
            break;
        }
        MAJMenu(lvl_menu);
        break;
      default:
        break;
    }
  }

        // on enregistre l'état du bouton pour le tour suivant
    memoire_bouton = lcd_key;
}
