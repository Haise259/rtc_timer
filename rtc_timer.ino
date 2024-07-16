/*
Test of RTC DS1307 via I2C.
 Counts 
 Seconds, 
 Minutes, 
 Hours, 
 Date of the Month, 
 Month, 
 Day of the week, and 
 Year with Leap-Year
 
 56 bytes battery backed RAM
 Square Wave Output
 
 11/17/2012- Updated for Wire.write & Wire.read commands
 1/18/13 - fixed unclear reference to 0x00
 */


/*
Modified to Run thru IDE Serial port
*/
#include <Wire.h>


//variables
byte zeroByte = 0;
byte seconds_address = 0x00;
byte seconds; // bit 7 = Clock Halt, Enabled = 0, Halt = 1
// bits 6-5-3 = tens of seconds 0-6,  bits 3-2-1-0 = units of seconds, 0-9


byte minutes_address = 0x01;
byte minutes;  // bits 6-5-4 = tens of minutes, bits 3-2-1-0 = units of minutes


byte hours_address = 0x02; 
byte hours;  // 7=0. 6 = 1 for 12 hr, 0 for 24 hr.
// bit 5: 12 hr mode = AM(0)/PM(1). 24 hr mode = upper tens of hrs
// bit 4 =  lower tens of hrs, bits 3-2-1-0 = units of hours (0-9)


byte day_week_address = 0x03; 
byte day_week = 0; // range 01-07


byte date_month_address = 0x04;
byte date_month = 0; // range 01-31


byte month_address = 0x05;
byte month = 0; // range 01-12


byte year_address = 0x06;
int year = 0; // upper byte 0-9, lower byte 0-9


byte square_address = 0x07;
byte sqwe = 0;  // square wave enable
// Out-0-0-Sqwe-0-0-RS1-RS0
// Out, Sqwe = 0/0 - Square wave output = 0
// Out, Sqwe = 1/0 - Square wave output = 1
// Out, Sqwe = 0/1 or 1/1 - Square wave output per RS1/RS0
// RS1/RS0 = 00 = 1 Hz
// RS1/RSo = 01 = 4 KHz
// RS1/RS0 = 10 = 8 KHz
// RS1/RS0 = 11 = 32 KHz


byte RTC_ram_address = 0x08; //range = 08-63, 0x08-0x3F


int RTC_address = 0x57; // 1101 000 


byte incomingCommand = 0;
byte RTC_write_command = 0;
byte RTC_read_command = 0;
byte RTC_ram_command = 0;


// use F0xx, F1xx,F2xx, F3xx, F4xx, F5xx, F6xx, F7xx
// to send one register write commands
// use E0xx to read registers back - not coded yet
// use C0xx to read RAM back - not coded yet


byte incomingRegister = 0;
byte RTC_register = 0;
byte incomingData1 = 0;
byte incomingData2 = 0;
byte new_data = 0;
byte outgoingData = 0;
int delay_time = 100;


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long duration = 5000;


void setup() {
  Wire.begin(); // no address, we are master
  Serial.begin (9600);  
  Serial.flush();
  currentMillis = millis();  
}


void loop() {


  if (Serial.available() >3){
    incomingCommand = Serial.read();
    incomingRegister = Serial.read();
    incomingData1 = Serial.read();
    incomingData1 = incomingData1 - 0x30; // convert ASCII to HEX
    incomingData2 = Serial.read();
    incomingData2 = incomingData2 - 0x30;  // convert ASCII to HEX
    new_data = (incomingData1 << 4) + incomingData2;  // put the Upper/Lower nibbles together
    Serial.print ("command ");
    Serial.println (incomingCommand);
    Serial.print ("register ");
    Serial.println(incomingRegister);
    Serial.print ("data1 ");
    Serial.println (incomingData1, HEX);
    Serial.print ("data2 ");
    Serial.println (incomingData2, HEX);
    Serial.print ("combined data ");    
    Serial.println (new_data, HEX);
    
  }
  // *******************************************
//  RTC_write_command = incomingCommand & 0xF0;  // mask off high byte
//  if (RTC_write_command == 0xF0){  // check for Write command
if ((incomingCommand == 'F') | (incomingCommand == 'f')){
  incomingCommand = 0;  // reset for next pass
//    RTC_register = incomingCommand & 0x0F;  // mask off low btye
//    incomingCommand = 0;
//    new_data = incomingData;
    Serial.println (" Sending a command ");
//    switch (RTC_register){
switch (incomingRegister){
  case '0': // write seconds
        Serial.println ("Seconds ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(seconds_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
      delay (delay_time);
      break;
    case '1': // write minutes
    Serial.println ("Minutes ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(minutes_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
      delay (delay_time);
      break;
    case '2': // write hours
        Serial.println ("Hours ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(hours_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
    case '3': // write day
        Serial.println ("Day ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(day_week_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
    case '4': // write date of month
        Serial.println ("Day of Month ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(date_month_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
    case '5': // write month
        Serial.println ("Month ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(month_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
    case '6': // write year
        Serial.println ("Year ");
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(year_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
    case '7': // write square wave
        Serial.println ("Square Wave ");
    Serial.println (RTC_register, HEX);
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(square_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
    case '8': // write RAM
        Serial.print ("RAM ");
    Serial.println (RTC_register, HEX);
      Wire.beginTransmission(RTC_address); // select device
      Wire.write(RTC_ram_address);          // queue the register
      Wire.write(new_data);                  // queue data
      Wire.endTransmission();            // send it
     delay (delay_time);
      break;
      // all others,do nothing
      Serial.println ("Invalid command ");
    }  // end Switch
  } // end if command == 'F'
  // ************************************


  currentMillis = millis();
  if ( (currentMillis - previousMillis) >= duration){
    previousMillis = currentMillis;  
    // Reset the register pointer  
    Wire.beginTransmission(RTC_address);  
    Wire.write(zeroByte);  
    Wire.endTransmission();   


    Wire.requestFrom(RTC_address,8 );  
    seconds = Wire.read();  
    minutes = Wire.read();  
    hours = Wire.read();  
    day_week = Wire.read();  
    date_month = Wire.read();  
    month = Wire.read();  
    year = Wire.read();  
    sqwe = Wire.read();


    // Seconds 
    // bit 7 = Clock Halt, Enabled = 0, Halt = 1
    // bits 6-5-3 = tens of seconds 0-6,  bits 3-2-1-0 = units of seconds, 0-9 


    // Hours
    // 7=0. 6 = 1 for 12 hr, 0 for 24 hr.
    // bit 5: 12 hr mode = AM(0)/PM(1). 24 hr mode = upper tens of hrs
    // bit 4 =  lower tens of hrs, bits 3-2-1-0 = units of hours (0-9)


    Serial.print ("Hrs " );
    Serial.print (hours, HEX);
    Serial.print (" Mins ");
    Serial.print (minutes, HEX);
    Serial.print (" Secs ");
    Serial.print (seconds, HEX);
    Serial.print (" Day ");
    Serial.print (day_week, HEX);
    Serial.print (" Date ");
    Serial.print (date_month, HEX);
    Serial.print (" Month ");
    Serial.print (month, HEX);
    Serial.print (" Year 20");
    Serial.print (year, HEX);
    Serial.print (" Square Wave ");
    Serial.println (sqwe, HEX);


  }
}
