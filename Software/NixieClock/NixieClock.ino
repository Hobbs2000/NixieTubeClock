const byte ZERO  = B00000001;
const byte ONE   = B00000000;
const byte TWO   = B00001001;
const byte THREE = B00001000;
const byte FOUR  = B00000111;
const byte FIVE  = B00000110;
const byte SIX   = B00000101;
const byte SEVEN = B00000100;
const byte EIGHT = B00000011;
const byte NINE  = B00000010;

//THIS IS THE TIME THAT THE CLOCK STARTS ON WHEN BOOTING UP
int startHour = 11;
int startMin = 20;

//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 4;

void setup() {
  //set pins to output because they are addressed in the main loop
  //Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  int d1 = (startHour / 10) % 10;
  int d2 = startHour % 10;
  int d3 = (startMin / 10) % 10;
  int d4 = startMin % 10;
  outputNixieTubes(d1, d2, d3, d4);
}

void loop() {
  unsigned long curTime;
  unsigned long lastTime = millis();
  int hour = startHour;
  int minute = startMin;
  while (true) {
    curTime = millis();
    if (curTime-lastTime >= 60000) { //Every second (1000 milliseconds)
      minute++;
      if (minute >= 60) {
        minute = 0;
        hour++;
        if (hour > 12) {
          hour = 1;
        }
      }
      int d1 = (hour / 10) % 10;
      int d2 = hour % 10;
      int d3 = (minute / 10) % 10;
      int d4 = minute % 10;
      outputNixieTubes(d1, d2, d3, d4);
      lastTime = millis();
    }
  }
}





/*Nixies from left to right*/
void outputNixieTubes(int n1, int n2, int n3, int n4) {
  byte nixie1 = correctNumForNixie(n1);
  byte nixie2 = correctNumForNixie(n2);
  byte nixie3 = correctNumForNixie(n3);
  byte nixie4 = correctNumForNixie(n4);
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, (nixie1<<4)|nixie2);
  shiftOut(dataPin, clockPin, MSBFIRST, (nixie3<<4)|nixie4);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, HIGH);
}

/*Converts an integer into the corresponding byte sequence for IN-14 Nixie tubes*/
byte correctNumForNixie(int num) {
  if (num==0) {
    return ZERO; 
  }
  else if (num==1){
    return ONE;
  }
  else if (num==2) {
    return TWO;
  }
  else if (num==3) {
    return THREE;
  }
  else if (num==4) {
    return FOUR;
  }
  else if (num==5) {
    return FIVE;
  }
  else if (num==6) {
    return SIX;
  }
  else if (num==7) {
    return SEVEN;
  }
  else if (num==8) {
    return EIGHT;
  }
  else if (num==9) {
    return NINE;
  }
}
