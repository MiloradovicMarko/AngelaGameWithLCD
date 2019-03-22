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
bool decisioneMeta;
bool primaVolta;
void setup() {
  // put your setup code here, to run once:
  turno = 0;
  somma = 0;
  meta = 30;
  giocataPre = 0;
  turnoStart = true;
  t = 1000;
  decisioneMeta = false;
  primaVolta = true;
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  lcd.begin(16, 2);
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
    if (somma > meta)
    {
      winOrLose();
    }
    if (giocataPre == 0);
    {
      caso4(assegnaValore());
    }
    if (giocataPre == 1 || giocataPre == 6)
    {
      caso1(assegnaValore());
    }
    if (giocataPre == 2 || giocataPre == 5)
    {
      caso2(assegnaValore());
    }
    if (giocataPre == 3 || giocataPre == 4)
    {
      caso3(assegnaValore());
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
  ritardo();
  while (digitalRead(btn2) == HIGH)
  {
    if (digitalRead(btn1) == LOW)
    {
      ritardo();
      if (giocata > 0)
      {
        lcd.setCursor(0, 0);
        lcd.print("Giocata corrente");
        giocata--;
        lcd.setCursor(0, 1);
        lcd.print(String(giocata));
      }
    }
    if (digitalRead(btn3) == LOW)
    {
      ritardo();
      if (giocata < 6)
      {
        lcd.setCursor(0, 0);
        lcd.print("Giocata corrente");
        giocata++;
        lcd.setCursor(0, 1);
        lcd.print(String(giocata));
      }
    }
  }
  return giocata;
}



void caso0(int giocata)
{
  if (giocata == 0)
  {
    delay(t);
    sistemaCursore(0, 0); lcd.print(String(giocata)); delay(t);
  }
  else
  {
    selezioneCorretta(giocata);
    lcd.clear();
  }
  sistemaCursore(0, 0); lcd.print("Gioca il secondo giocatore"); delay(t);
  turno = -1;
  nuovaGiocata();
}


void caso1(int giocata)
{
  sistemaCursore(0, 0); lcd.print(giocata);
  assegnaValore();
  if (digitalRead(btn2) == LOW)
  {
    if (giocata == 1 || giocata == 6 || giocata == 0)
    {
      sistemaCursore(0, 0); lcd.print("Non barare"); delay(t); nuovaGiocata();
    }
    else
    {
      selezioneCorretta(giocata);
      lcd.clear();
      switchTurno();
    }
  }
}


void caso2(int giocata)
{
  sistemaCursore(0, 0); lcd.print(giocata);
  assegnaValore();
  if (giocata == 2 || giocata == 5 || giocata == 0)
  {
    sistemaCursore(0, 0); lcd.print("Non barare"); delay(t); nuovaGiocata();
  }
  else
  {
    selezioneCorretta(giocata);
    lcd.clear();
    switchTurno();
  }
}


void caso3(int giocata)
{ sistemaCursore(0, 0); lcd.print(giocata);
  assegnaValore();
  if (giocata == 3 || giocata == 4)
  {
    sistemaCursore(0, 0); lcd.print("Non barare"); delay(t); nuovaGiocata();
  }
  else
  {
    selezioneCorretta(giocata);
    lcd.clear();
    switchTurno();
  }
}


void caso4(int giocata)
{
  sistemaCursore(0, 0); lcd.print(giocata);
  assegnaValore();
  if (giocata == 0)
  {
    sistemaCursore(0, 0); lcd.print("Non barare"); delay(t); nuovaGiocata();
  }
  else {
    selezioneCorretta(giocata);
    lcd.clear();
    switchTurno();
  }
}


void cambioMeta()
{
  if (decisioneMeta == false)
  {
    sistemaCursore(0, 0);
    lcd.print("Selezionare Meta");
    lcd.setCursor(0, 1);
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
        lcd.setCursor(0, 1);
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
        lcd.setCursor(0, 1);
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
    sistemaCursore(0, 0);
    turno = 1;
    lcd.print("Gioca il primo");
    delay(t);
  }
  else if (turno == 1)
  {
    sistemaCursore(0, 0);
    turno = -1;
    lcd.print("Gioca il secondo");
    delay(t);
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
