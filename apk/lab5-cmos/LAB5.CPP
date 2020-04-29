#include <iostream.h>
#include <dos.h>
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>

struct VIDEO
{
	unsigned char symbol;
	unsigned char attribute;
};

const long long FLACTUATIONS = 1193180;

int ticks;
void interrupt(*oldint08) (...);
void interrupt(*oldint4a) (...);

void showAlarm();

void showTime();
void delayer(int delay_size);
void interrupt newint08(...);
void interrupt newint4a(...);
void init_interrupt();
int getInBounds(int lb, int rb);
void getDMYhms(int* D, int* M, int* Y, int* h, int* m, int*s);
void set_cmos(int day, int month,int year, int hours, int minutes, int seconds);
int getport(int port);

void set_alarm();
void before_alarm();
int safeGetTime(int port);
int getSeconds();
int getMinutes();
int getHours();

void disableAlarm();

int main() {
	int temp;

	outp(0x70, 0x0B);
	temp = inp(0x71);
	temp|=4;
	outp(0x71, temp);

	char c;
	do {
		cout << "1: out time\n"
			<< "2: delay\n"
			<< "3: set cmos\n"
			<< "4: set alarm\n"
			<< "5: time before alarm\n"
			<< "6: disable alarm\n"
			<< "0: exit\n" << endl;
		while (cin.peek() < '0' || cin.peek() > '9')
			cin.get();
		cin.get(c);
		switch (c)
		{
		case '1':
			showTime();
			break;
		case '2':{
			int temp;
			cout << "Input delay" << endl;
			temp = getInBounds(0, 32767);
			delayer(temp);
			break;
		}
		case '3':{
			int day, month, year, hour, minute, second;
			cout<< "Enter: DD MM YYYY hh mm ss" << endl;
			getDMYhms(&day, &month, &year, &hour, &minute, &second);
			set_cmos(day, month, year, hour, minute, second);
			break;
		}
		case '4':
			set_alarm();
			break;
		case '5':
			before_alarm();
			break;
		case '6':
			disableAlarm();
			break;
		case '0':
			break;
		default:
			cout << "Wrong input" << endl;
			break;
		}
		
	} while (c!='0');

	return 0;
}

void showAlarm(){
	VIDEO far* screen = (VIDEO far *)MK_FP(0xB800, 0);  
	char color = 0x26;
	screen->symbol = 'A';
	screen->attribute = color;
	++screen;
	screen->symbol = 'L';
	screen->attribute = color;
	++screen;
	screen->symbol = 'A';
	screen->attribute = color;
	++screen;
	screen->symbol = 'R';
	screen->attribute = color;
	++screen;
	screen->symbol = 'M';
	screen->attribute = color;
}

int getInBounds(int lb, int rb){
	int temp;
	cin >> temp;
	while(!cin.good() || temp<lb || temp>rb){
		cin.ignore(32768, '\n');
		cin.clear();
		cout << "Invalid input, input number between " << lb << " and " << rb << endl;
		cin >> temp;
	}
	return temp;
}

void getDMYhms(int* D, int* M, int* Y, int* h, int* m, int*s){
	cout << "Input day" << endl;
	*D = getInBounds(1, 31);
	cout << "Input month" << endl;
	*M = getInBounds(1, 12);
	cout << "Input year" << endl;
	*Y = getInBounds(1970, 2034);
	cout << "Input hour" << endl;
	*h = getInBounds(0, 23);
	cout << "Input minute" << endl;
	*m = getInBounds(0, 59);
	cout << "Input second" << endl;
	*s = getInBounds(0, 59);
}

void showTime(){
	int hours, minutes, seconds;
	int year, month, day, cent;
	int temp;
	int cnt= 1;
	do{
		outp(0x70, 0x0A);
		temp=inp(0x71);
		cnt = temp & 128;
	} while(!cnt);

	outp(0x70, 0x04);
	hours = inp(0x71);
	outp(0x70, 0x02);
	minutes = inp(0x71);
	outp(0x70, 0x00);
	seconds = inp(0x71);

	outp(0x70, 0x07);
	day = inp(0x71);
	outp(0x70, 0x08);
	month = inp(0x71);
	outp(0x70, 0x09);
	year = inp(0x71);

	outp(0x70, 0x32);
	cent = inp(0x71);

	int c1 = cent>>4, c2=cent&15;
	//printf("%2d.%2d.%2d%2d %2d:%2d:%2d", day, month, cent, year, hours, minutes, seconds);
	cout << day/10 << day%10 << "." << month/10 << month%10 << "." << c1 <<c2 << year/10 << year%10 << " " 
	<<  hours/10 << hours%10 << ":" << minutes/10 << minutes%10 << ":" << seconds/10 << seconds%10 <<endl;
	return;
}



void interrupt newint08(...){
	++ticks;
	oldint08();
}

void interrupt newint4a(...){
	showAlarm();
	disableAlarm();
}

void set_intmask(){
	
	int temp = inp(0xA1);
	temp&=0xFE;
	_disable();

	outp(0xA1, temp);

	_enable();
}


void delayer(int delay_size){

	ticks = 0;

	int temp;

	temp = getport(0x0A);
	temp|=6;
	outp(0x71, temp);

	outp(0x70, 0x0B);
	temp = inp(0x71);
	temp|=64;
	outp(0x71, temp);

	
	oldint08 = getvect(0x70);
	setvect(0x70, newint08);
	set_intmask();	
	while(delay_size>ticks){}
	setvect(0x70, oldint08);
	return;

}

int to_bcd(int num){
	int temp;
	temp = (num/10);
	temp<<=4;
	temp+=num%10;
	return temp;
}

void set_cmos(int day, int month,int year, int hours, int minutes, int seconds){

	int temp, bl=1;
	outp(0x70, 0x0A);

	do{
		temp = inp(0x71);
		bl = 128&temp;
	}while(bl);

	outp(0x70, 0x0B);
	temp = inp(0x71);
	temp|=128;
	outp(0x71, temp);

	outp(0x70, 0x07);
	outp(0x71, day);
	outp(0x70, 0x08);
	outp(0x71, month);
	outp(0x70, 0x09);
	outp(0x71, year&15);
	outp(0x70, 0x32);
	outp(0x71, to_bcd(year/100));

	outp(0x70, 0x04);
	outp(0x71, hours);
	outp(0x70, 0x02);
	outp(0x71, minutes);
	outp(0x70, 0x00);
	outp(0x71, seconds);

	outp(0x70, 0x0B);
	temp&=127;
	outp(0x71, temp);
}

int getport(int port){
	int temp;
	outp(0x70, port);
	temp = inp(0x71);
	return temp;
}

void set_alarm(){

	int temp;
	int h, m, s;

	oldint4a = getvect(0x4a);
	setvect(0x4a, newint4a);
	cout << "timer for 5 sec or set alarm time?\n"
		<<"1: 5 seconds\n"
		<<"2: set alarm time" << endl;
	temp = getInBounds(1, 2);
	switch(temp){
		case 1:{
			h = getport(0x04);
			m = getport(0x02);
			s = getport(0x00);	
			s+=5;
			if(s>59){
				s%=59;
				++m;
				if(m>=59){
					m=0;
					++h;
					if(h>=23)
						h=0;
				}
			}
			break;
		}
		case 2:{
			cout << "Input alarm hour" << endl;
			h = getInBounds(0, 23);
			while(h<getHours()){
				cout << "Alarm hour should be later";
				h = getInBounds(0,23);
			}
			cout << "Input alarm minute" << endl;
			m = getInBounds(0, 59);
			while(h<getHours()){
				cout << "Alarm minuten should be later";
				m = getInBounds(0,59);
			}
			cout << "Input alarm second" << endl;
			s = getInBounds(0, 59);
			while(h<getHours()){
				cout << "Alarm second should be later";
				s = getInBounds(0,59);
			}
			break;
		}
	}
	getport(0x05);
	outp(0x71, h);
	getport(0x03);
	outp(0x71, m);
	getport(0x01);
	outp(0x71, s);


	temp = getport(0x0B);
	temp|=32;
	outp(0x71, temp);
	set_intmask();

}

void before_alarm(){
	int h, m, s, ch, cm, cs;
	h = getHours();
	m = getMinutes();
	s = getSeconds();
	ch = getport(0x05);
	cm = getport(0x03);
	cs = getport(0x01);
	if((ch==h && cm==m && cs>=s)||(ch==h && cm>m)||(ch>h)){
		if(cs<s){
			cs = cs + 60-s;
			if(cs>59){
				cs%=59;
				++cm;
			}
			
			--cm;
		}
		else
			cs-=s;
		if(cm<m){
			cm = cm + 60-m;
			if(cm>59){
				cm%=59;
				++ch;
			}
			--ch;
		}
		else
			cm-=m;
		ch-=h;
		cout << ch/10 << ch%10 << ":" << cm/10 << cm%10 << ":" << cs/10 << cs%10 << " before alarm" << endl;
	}
	else
		cout << "You should set alarm first" << endl;
}

int safeGetTime(int port){
	int temp;
	int cnt= 1;
	do{
		outp(0x70, 0x0A);
		temp=inp(0x71);
		cnt = temp & 128;
	} while(!cnt);
	temp = getport(port);
	return temp;
}

int getSeconds(){
	int temp;
	temp = safeGetTime(0x00);
	return temp;
}

int getMinutes(){
	int temp;
	temp = safeGetTime(0x02);
	return temp;
}

int getHours(){
	int temp;
	temp = safeGetTime(0x04);
	return temp;
}

void disableAlarm(){
	if(oldint4a == NULL)
		return;
	int temp;
	_disable();
	setvect(0x4a, oldint4a);

	temp = getport(0x0B);
	temp&=0xDF;
	outp(0x71, temp);

	temp = inp(0xA);
	temp|=1;
	outp(0xA1, temp);

	_enable();
}