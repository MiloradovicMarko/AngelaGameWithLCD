#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const int btn1 = 4;
const int btn2 = 3;
const int btn3 = 2;
int turno;
int somma;
int meta;
int giocataPre;
bool turnoStart;
int t;

void setup() {
  // put your setup code here, to run once:
turno = 0;
somma = 0;
meta = 30;
giocataPre = 0;
turnoStart = true;
t = 1000;
pinMode(btn1,INPUT_PULLUP);
pinMode(btn2,INPUT_PULLUP);
pinMode(btn3,INPUT_PULLUP);
lcd.begin(16,2);
}

void loop() {
  cambioMeta();
  nuovaGiocata();
  winOrLose();
}

void nuovaGiocata()
{
  ritardo();
   if(turno == 0)
   {
      caso0(assegnaValore());
   }
   else if(turno == 1 || turno == -1)
   {
    if(giocataPre == 0);
    {
      caso4(assegnaValore());  
    }
    if(giocataPre == 1 || giocataPre == 6 || giocataPre == 0)
    {
      caso1(assegnaValore());
    }
    if(giocataPre == 2 || giocataPre == 5 || giocataPre == 0)
    {
      caso2(assegnaValore());
    }
    if(giocataPre == 3 || giocataPre == 4 || giocataPre == 0)
    {
      caso3(assegnaValore());
    }
   }
}


int assegnaValore()
{
  int giocata = 0;
  while(digitalRead(btn2) == HIGH)
  {
  if(digitalRead(btn1) == LOW)
      {
        ritardo();
        if(giocata > 0)
        {
        sistemaCursore(0,0);
        giocata--;
        lcd.print(String(giocata));
        } 
      }
      if(digitalRead(btn3) == LOW)
      {
        ritardo();
        if(giocata < 6)
        {
          sistemaCursore(0,0);
          giocata++;
          lcd.print(String(giocata));
        }
      }
  }
  return giocata;
}

void caso0(int giocata)
{     
        if(giocata == 0)
        {
          delay(t);
          sistemaCursore(0,0);lcd.println(String(giocata));delay(t);
        }
        else
        {
          selezioneCorretta(giocata); 
        }
        turno = -1;
        sistemaCursore(0,0);lcd.println("Gioca il secondo giocatore");delay(t);;
}


void caso1(int giocata)
{
      sistemaCursore(0,0);lcd.print(giocata);  
      assegnaValore();
      if(digitalRead(btn2) == LOW)
      {
        if(giocata == 1 || giocata == 6 || giocata == 0)
        { 
          sistemaCursore(0,0);lcd.println("Non barare");delay(t); 
        } 
        else
        {
          selezioneCorretta(giocata);
          switchTurno(); 
        }
   }  
}
void caso2(int giocata)
{     
        sistemaCursore(0,0);lcd.print(giocata);  
        assegnaValore();
        if(giocata == 2 || giocata == 5 || giocata == 0)
        { 
          sistemaCursore(0,0);lcd.println("Non barare");delay(t);
        } 
        else
        {
          selezioneCorretta(giocata);
          switchTurno();
        }
}
void caso3(int giocata)
{     sistemaCursore(0,0);lcd.print(giocata);
      assegnaValore();
      if(giocata == 3 || giocata == 4)
      { 
        sistemaCursore(0,0);lcd.println("Non barare");delay(t);
      } 
      else
      {
        selezioneCorretta(giocata);
        switchTurno();
      }
}
void caso4(int giocata)
{   
  sistemaCursore(0,0);lcd.print(giocata);
   assegnaValore();
   if(giocata == 0)
   {
    giocataPre = giocata; 
    sistemaCursore(0,0);lcd.println("Non barare");delay(t);}
   else{ 
   selezioneCorretta(giocata);
   switchTurno();
   }
}
void cambioMeta()
{
  sistemaCursore(0,0);
  lcd.print("Selezionare Meta");
  //sistemaCursore(0,1);
  while(digitalRead(btn2) == HIGH)
  {
  if(digitalRead(btn3) == LOW)
  {
    ritardo();
    meta++;
    if(meta > 99)
    {meta = 30;}
    lcd.setCursor(0,1);
    lcd.print(meta);
  }
  else if(digitalRead(btn1) == LOW)
  {
    ritardo();
    meta--;
    if(meta < 30)
    { meta = 99; }
    lcd.setCursor(0,1);
    lcd.print(meta);
  }
  }
}
void ritardo()
{
  while(digitalRead(btn1) == LOW || digitalRead(btn2) == LOW || digitalRead(btn3) == LOW)
    {}
}
void switchTurno()
{ 
    if(turno == -1)
    {sistemaCursore(0,0);turno = 1;lcd.println("Gioca il primo");delay(t);}
    else if(turno == 1)
    {sistemaCursore(0,0);turno = -1;lcd.println("Gioca il secondo");delay(t);}
}


void winOrLose()
{
  attesa();
  sistemaCursore(0,0);
  if((somma == meta && turno == 1) || (somma >= meta && turno == 1))
  {
    sistemaCursore(4,0);
    lcd.println("Ha vinto");
    lcd.setCursor(0,1); 
    lcd.println("il primo giocatore!");
    setup();
  }
  else if((somma == meta && turno == -1) || (somma >= meta && turno == -1))
  {
    sistemaCursore(4,0);
    lcd.println("Ha vinto");
    lcd.setCursor(0,1); 
    lcd.println("il secondo giocatore!");
    setup();
  }
}


void sistemaCursore(int p1,int p2)
{ lcd.clear();lcd.setCursor(p1,p2); } 

 
void selezioneCorretta(int giocata)
{
    somma += giocata;
    giocataPre = giocata;
    sistemaCursore(0,0);lcd.println(String(giocata));delay(t);
    sistemaCursore(0,0);lcd.println("Punteggio raggiunto: ");delay(t);
    sistemaCursore(0,0);lcd.println(somma);delay(t);
}
