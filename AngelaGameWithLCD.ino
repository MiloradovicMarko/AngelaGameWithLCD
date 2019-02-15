#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
int btn1 = 2;
int btn2;
int btn3;
int turno;
int somma;
int meta;
int giocataPre;
bool turnoStart;
int t;
int incremento;
void setup() {
  // put your setup code here, to run once:
incremento = 0;
btn1 = 2;
btn2 = 3;
btn3 = 4;
turno = 0;
somma = 0;
meta = 0;
giocataPre = 0;
turnoStart = true;
t = 500;
pinMode(btn1,INPUT_PULLUP);
pinMode(btn2,INPUT_PULLUP);
pinMode(btn3,INPUT_PULLUP);
lcd.begin(16,2); •
}

void loop() {
  // put your main code here, to run repeatedly:
}

void caso0(int giocata)
{ 
      if(giocata == 0)
      {
        turno = -1;
        lcd.println(giocata);sistemaCursore(0,0);delay(t);
        lcd.println("Gioca il secondo giocatore");
      }
      else
      {
        giocataPre = giocata;
        somma += giocata;
        turno = -1;
        lcd.println(giocata);sistemaCursore(0,0);delay(t);
        lcd.println("Punteggio raggiunto: ");sistemaCursore(0,0);delay(t);
        lcd.println(somma);sistemaCursore(0,0);delay(t);
      }

}
void caso1(int giocata)
{
      if(giocata == 1 || giocata == 6 || giocata == 0 && giocata > 6)
      { 
        lcd.println("Non barare");attesa() ;} 
      else
      {
        somma += giocata;
        giocataPre = giocata;
        lcd.println(giocata);sistemaCursore(0,0);delay(t);
        lcd.println("Punteggio raggiunto: ");sistemaCursore(0,0);delay(t);
        lcd.println(somma);sistemaCursore(0,0);delay(t);
        switchTurno();   
      }
      
}
void caso2(int giocata)
{
      if(giocata == 2 || giocata == 5 || giocata == 0 && giocata > 6)
      { 
        lcd.println("Non barare");attesa() ;} 
      else
      {
        somma += giocata;
        giocataPre = giocata;
        lcd.println(giocata);sistemaCursore(0,0);delay(t);
        lcd.println("Punteggio raggiunto: ");sistemaCursore(0,0);delay(t);
        lcd.println(somma);sistemaCursore(0,0);delay(t);
        switchTurno();   
      }
      
}
void caso3(int giocata)
{
      if((giocata == 3 || giocata == 4 || giocata == 0)&& giocata > 6)
      { lcd.println("Non barare");attesa();} 
      else
      {
        somma += giocata;
        giocataPre = giocata;
        lcd.println(giocata);sistemaCursore(0,0);delay(t);
        lcd.println("Punteggio raggiunto: ");sistemaCursore(0,0);delay(t);
        lcd.println(somma);sistemaCursore(0,0);delay(t);
        switchTurno();
      }
}
void caso4(int giocata)
{
    giocataPre = giocata;
    somma += giocata;
    turno = -1;
    lcd.println(giocata);sistemaCursore(0,0);delay(t);
    lcd.println("Punteggio raggiunto: ");sistemaCursore(0,0);delay(t);
    lcd.println(somma);sistemaCursore(0,0);delay(t);
    switchTurno();
}
void cambioMeta()
{
  attesa();
  sistemaCursore(0,1);
  if(digitalRead(btn1) == LOW)
  {
    meta++;
    if(meta > 99)
    {meta = 30;}
    lcd.print(meta);
  }
  else if(digitalRead(btn3) == LOW)
  {
    meta--;
    if(meta < 30)
    { meta = 99; }
    lcd.print(meta);
  }
}
void attesa()
{
    while(digitalRead(btn1) == HIGH || digitalRead(btn2) == HIGH || digitalRead(btn3) == HIGH)
    {}
}
void switchTurno()
{ 
    sistemaCursore(0,0);
    if(turno == -1)
    {turno = 1;;lcd.println("Gioca il primo");}
    else if(turno == 1)
    {turno = -1;lcd.println("Gioca il secondo");}
}
void winOrLose()
{
  sistemaCursore(0,0);
  if((somma == meta && turno == 1) || (somma >= meta && turno == 1))
  {
    lcd.println("Ha vinto il primo giocatore!");setup();
  }
  else if((somma == meta && turno == -1) || (somma >= meta && turno == -1))
  {
    lcd.println("Ha vinto il secondo giocatore!");setup();
  }
}
void sistemaCursore(int p1,int p2)
{ lcd.clear();lcd.setCursor(p1,p2); }  
void setGiocata()
{
  attesa();
  sistemaCursore(0,1);
  if(digitalRead(btn1) == LOW)
  {
    incremento++;
    sistemaCursore(0,1);
    lcd.print(incremento);
  }
  else if(digitalRead(btn3) == LOW)
  {
    incremento--;
    sistemaCursore(0,1);
    lcd.print(incremento);
  }
}
