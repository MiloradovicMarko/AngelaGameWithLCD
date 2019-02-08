#include <LiquidCrystal.h>
const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;
int turno = 0;
int somma = 0;
int meta = 0;
bool turnoStart = true;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // put your setup code here, to run once:
pinMode(btn1,INPUT_PULLUP);
pinMode(btn2,INPUT_PULLUP);
pinMode(btn3,INPUT_PULLUP);
lcd.begin(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:

}






void attesa()
{
    while(digitalRead(btn1) == HIGH || digitalRead(btn2) == HIGH || digitalRead(btn3) == HIGH)
    {}
}
void switchTurno()
{
    if(turno == -1)
    {turno = 1;lcd.println("Gioca il primo");}
    else if(turno == 1)
    {turno = -1;lcd.println("Gioca il secondo");}
}
void winOrLose()
{
  if((somma == meta && turno == 1) || (somma >= meta && turno == 1))
  {
    lcd.println("Ha vinto il primo giocatore!");ricomincia();
    ricomincia();
  }
  else if((somma == meta && turno == -1) || (somma >= meta && turno == -1))
  {
    lcd.println("Ha vinto il secondo giocatore!");ricomincia();
  }
}  
void ricomincia()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("Per ricominciare premere un qualsiasi bottone");
  attesa();
  if(digitalRead(btn1) == LOW || digitalRead(btn2) == LOW || digitalRead(btn3) == LOW)
  {
    lcd.println("Punteggio riavviato");
    turno = 0;
    somma = 0;
    meta = 0;
    turnoStart = true;
  }
}
