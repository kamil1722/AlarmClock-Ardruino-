#include "RTClib.h"
#include <LiquidCrystal_I2C.h> 
 
#define stateHour A0
#define stateMinute A1
#define StateAlarm 2

boolean btn_hour_state = 1;
boolean btn_minute_state = 1;
boolean btn_alarm_state = 0;

int pussCounter = 0;

int alarmHour;
int alarmMinute;

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,20,4); 

void setup () { 
    rtc.begin();
    lcd.init();
    lcd.backlight(); 
}
void loop () {
    printRealTime();
    printAlarmTime();
    StartTone(pussCounter);
    countClicks();
    delay(10);
}
void printRealTime(){
    DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print(now.hour(),DEC);
    lcd.print(":");
    lcd.print(now.minute(),DEC);
    lcd.print(":");
    lcd.print(now.second(),DEC);
    lcd.println();
}

void printAlarmTime(){
    alarmHour = ChangeButtonHourse(alarmHour, stateHour);
    alarmMinute = ChangeButtonMinute(alarmMinute, stateMinute);

    lcd.setCursor(0,1);
    if(alarmHour < 10){
      lcd.print("0");
      lcd.print(alarmHour);
    }
    else
      lcd.print(alarmHour);

    lcd.print(":");

    if(alarmMinute < 10){
      lcd.print("0");
      lcd.print(alarmMinute);
    }
    else
      lcd.print(alarmMinute);
}

int ChangeButtonHourse(int counter, byte stateHour){
  boolean btn_add = analogRead(stateHour);
  if (btn_add && btn_add != btn_hour_state && counter < 24)
    counter++;
  if(counter == 24) 
    counter = 0;
  btn_hour_state = btn_add;
  
  return counter;
}

int ChangeButtonMinute(int counter, byte stateMinute){
  boolean btn_add = analogRead(stateMinute);
  if (btn_add && btn_add != btn_minute_state && counter < 60)
    counter++;
  if(counter == 60) 
    counter = 0;
  btn_minute_state = btn_add;
  
  return counter;
}

void countClicks() {
  boolean btn = digitalRead(StateAlarm);
  if (btn && btn != btn_alarm_state)
    pussCounter++;
  btn_alarm_state = btn;
}

void StartTone(int pussCounter){

  if(pussCounter != 0 && rtc.now().hour() == alarmHour
   && rtc.now().minute() == alarmMinute){
     for(int i=0; i< 5;i++){
        delay(500);
        tone(A3, 262, 250);
        delay(500);
        noTone(A3);
      }
  }
}





