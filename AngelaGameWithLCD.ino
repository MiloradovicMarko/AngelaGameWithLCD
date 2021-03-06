#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
const int btn1 = 11;
const int btn2 = 13;
const int btn3 = 12;
int turno;
int somma;
int meta;
int giocataPre;
int t;
bool decisioneMeta;
bool primaVolta;
void setup() {
  // put your setup code here, to run once:
  turno = 0;
  somma = 0;
  meta = 30;
  giocataPre = 0;
  t = 1000;
  decisioneMeta = false;
  primaVolta = true;
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("  ANGELA  GAME  ");
  lcd.setCursor(0,1);
  lcd.print(" Fatto da Marko");
  delay(t*3);
  lcd.clear();
}

void loop() {
  cambioMeta();
  nuovaGiocata();
  winOrLose();
}

void nuovaGiocata()
{
  ritardo();
  if (turno == 0)
  {
    caso0(assegnaValore());
  }
  else if (turno == 1 || turno == -1)
  {
    if (somma >= meta) {
      winOrLose();
    }
    else
    {
      if (giocataPre == 0) {
        caso4(assegnaValore());
      }
      else {
        casoEX(assegnaValore());
      }
    }
  }
}


int assegnaValore()
{
  int giocata = 0;
  if (decisioneMeta == true && primaVolta == true)
  {
    sistemaCursore(4, 0); lcd.print("Gioca G1");
    primaVolta = false;
    decisioneMeta == false;
  }
  while (digitalRead(btn2) == HIGH)
  {
    if (digitalRead(btn3) == LOW)
    {
      ritardo();
      giocata++;
      if (giocata > 6)
      {
        giocata = 0;
      }
       lcd.setCursor(0, 0);
       lcd.print("Giocata corrente");
       lcd.setCursor(0, 1);
       lcd.print(String(giocata));
       lcd.setCursor(1,1),lcd.print("                         ");  
    }
    if (digitalRead(btn1) == LOW)
    {
      ritardo();
      giocata--;
      if(giocata < 0)
      {
        giocata = 6;
      }
      lcd.setCursor(0, 0);
      lcd.print("Giocata corrente");
      lcd.setCursor(0, 1);
      lcd.print(String(giocata));
      lcd.setCursor(1,1),lcd.print("                         ");  
    }
  }
  return giocata;
}



void caso0(int giocata)
{
  if (giocata == 0)
  {
    sistemaCursore(0, 1); 
    lcd.print(String(giocata)); 
    lcd.setCursor(0,0);
    lcd.print("Punteggio Totale");
    delay(t);
  }
  else
  {
    selezioneCorretta(giocata);
    lcd.clear();
  }
  sistemaCursore(4, 0); lcd.print("Gioca G2"); delay(t);
  turno = -1;
  nuovaGiocata();
}


void casoEX(int giocata)
{
  assegnaValore();
  if (giocataPre == giocata || giocataPre == (7 - giocata) ||giocata == 0)
  {
    selezioneErrata(giocata);
  }
  else
  {
    selezioneCorretta(giocata);
    lcd.clear();
    switchTurno();
  }
  nuovaGiocata();
}

void caso4(int giocata)
{
  sistemaCursore(0, 0); lcd.print(giocata);
  assegnaValore();
  if (giocata == 0)
  {
    selezioneErrata(giocata);
  }
  else {
    selezioneCorretta(giocata);
    lcd.clear();
    switchTurno();
  }
  nuovaGiocata();
}


void cambioMeta()
{
  if (decisioneMeta == false)
  {
    sistemaCursore(0, 0);
    lcd.print("Selezionare Meta");
    lcd.setCursor(6, 1);
    lcd.print(String(meta));
    while (digitalRead(btn2) == HIGH)
    {
      if (digitalRead(btn3) == LOW)
      {
        ritardo();
        meta++;
        if (meta > 99)
        {
          meta = 30;
        }
        lcd.setCursor(6, 1);
        lcd.print(String(meta));
      }
      else if (digitalRead(btn1) == LOW)
      {
        ritardo();
        meta--;
        if (meta < 30)
        {
          meta = 99;
        }
        lcd.setCursor(6, 1);
        lcd.print(String(meta));
      }
    }
    decisioneMeta = true;
  }
}



void ritardo()
{
  while (digitalRead(btn1) == LOW || digitalRead(btn2) == LOW || digitalRead(btn3) == LOW)
  {}
}



void switchTurno()
{
  if (turno == -1)
  {
    sistemaCursore(4, 0);
    turno = 1;
    lcd.print("Gioca G1");
    delay(t);
    lcd.setCursor(0, 0);
    lcd.print("Giocata corrente");
    lcd.setCursor(0, 1);
    lcd.print(String(0));
  }
  else if (turno == 1)
  {
    sistemaCursore(4, 0);
    turno = -1;
    lcd.print("Gioca G2");
    delay(t);
    lcd.setCursor(0, 0);
    lcd.print("Giocata corrente");
    lcd.setCursor(0, 1);
    lcd.print(String(0));
  }
}


void winOrLose()
{
  sistemaCursore(0, 0);
  if ((somma == meta && turno == 1) || (somma >= meta && turno == 1))
  {
    sistemaCursore(4, 0);
    lcd.print("Ha vinto");
    lcd.setCursor(0, 1);
    lcd.print("il giocatore 1!");
    delay(t);
    setup();
  }
  else if ((somma == meta && turno == -1) || (somma >= meta && turno == -1))
  {
    sistemaCursore(4, 0);
    lcd.print("Ha vinto");
    lcd.setCursor(0, 1);
    lcd.print("il giocatore 2!");
    delay(t);
    setup();
  }
}


void sistemaCursore(int p1, int p2)
{
  lcd.clear();
  lcd.setCursor(p1, p2);
}


void selezioneCorretta(int giocata)
{
  giocataPre = giocata;
  somma += giocata;
  sistemaCursore(0, 0); lcd.print("Punteggio totale: "); delay(t);
  lcd.setCursor(0, 1); lcd.print(String(somma)); delay(t);
}


void selezioneErrata(int giocata)
{
  sistemaCursore(3, 0);
  lcd.print("Non barare");
  delay(t);
}
