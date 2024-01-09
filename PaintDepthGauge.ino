#include <LiquidCrystal.h>


int freqReadPin = 4;

int btnA = 1;
int btnB = 2;

int psu = 0;

const int rs = 15, en = 16, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  pinMode(freqReadPin, INPUT);

  //Serial.begin(9600);

  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);

  pinMode(psu, OUTPUT);

  //enable power transistor
  digitalWrite(psu,1);

  lcd.begin(8, 2);
}

bool current=false;

long count=0;

long offset=0;

void loop() {
  count=0;
  long startTime = micros();
  for(long i=0; i<50000UL; i++){
    bool read = digitalRead(freqReadPin);
    if(read != current && read)
      count++;
    
    current = read;
  }

  long endTime = micros();
  long duration = (endTime-startTime)/1000;
  long freq = count*1000UL / duration;


  lcd.clear();
  long ol = freq-offset;
  lcd.print(ol);
  lcd.print(" hz");

  lcd.setCursor(0, 1);

  //lcd.print(count);
  if(digitalRead(btnB)==0){
    offset = freq;
    lcd.print("--------");
  }
  else{
    if(offset!=0){
      lcd.print("OFFSET!");
    }
    else{
      lcd.print("ABS");
    }
  }

  if(digitalRead(btnA)==0){
    digitalWrite(psu,0);
  }
}
