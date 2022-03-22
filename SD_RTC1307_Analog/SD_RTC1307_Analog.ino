//github
//Install library - RTC by Makuna - setting masa dalam brain RTC
//ABlocks

#include <Wire.h>
#include "ABlocks_DS3231rtc.h" //yg nie kena install - cari di arduinoblocks.com
#include <SPI.h>
#include <SD.h>
//---> Set Time for DS1307 using RTC by Makuna. Then try to disconnect and connect. Then upload this code

float temp;
float humidity;

DS3231rtc rtc;

File sd_file;

String rtc_date_text(){
	char rtcbuffer[12];
	sprintf(rtcbuffer,"%02d/%02d/%04d", rtc.getDay(), rtc.getMonth(), (2000+rtc.getYear()) );
	return String(rtcbuffer);
}

String rtc_time_text(){
	char rtcbuffer[10];
	sprintf(rtcbuffer,"%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSecond() );
	return String(rtcbuffer);
}

void serial2() {
  Serial.println(rtc_date_text());
  Serial.println(rtc_time_text());
  Serial.print(String("Temperature:")+String(temp)+String("*C")+String("; "));
  Serial.println(String("Humidity")+String(humidity)+String("%"));
  Serial.println(String("-------------------------------------"));
}

void fnc_sd_print(String _f, String _t, boolean _nl){
	sd_file = SD.open(_f, FILE_WRITE);
	if(sd_file){
		if(_nl)sd_file.println(_t);
		else sd_file.print(_t);
		sd_file.close();
	}
}

void sdcard() {
  fnc_sd_print(String("temprh.txt"),String(String(rtc_date_text())+String(";")+String(rtc_time_text())+String(";")+String(temp)+String(";")+String(humidity)+String(";")),true);
}

void setup()
{
  Serial.begin(9600); Serial.flush(); while(Serial.available()>0)Serial.read();
  rtc.begin();
	SD.begin(10);

}


void loop()
{

    temp = analogRead(A0);
    humidity = temp-100;
    serial2();
    sdcard();
    delay(2000);

}
