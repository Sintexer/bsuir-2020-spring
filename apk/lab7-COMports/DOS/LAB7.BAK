#include <stdio.h>
#include <dos.h>
#include <time.h>
#include <string.h>

#define COM2 0x2F8
int regst;

void comPut(char chr);
void comInit();

void showMessage(char* message);
char message1[] = " Secret message ";
char message2[] = " Super secret message ";

struct VIDEO
{
	unsigned char symbol;
	unsigned char attribute;
};

void interrupt(*oldint08) (...);
void interrupt newint08(...);
void interrupt(*oldint09) (...);
void interrupt newint09(...);
void interrupt(*oldint0B) (...);
void interrupt newint0B(...);

int main() {
	comInit();
	unsigned far* f;
	FP_SEG(f) = _psp;
	FP_OFF(f) = 0x2c;
	_dos_freemem(*f);
	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1);
	return 0;
}

void interrupt newint08(...) {
	newint0B();
	oldint08();
}

void interrupt far newint09(...) {

	_disable();
	int data = inp(0x60);

	if (data < 128) {
		comPut(data);
		comPut('\0');
	}

	_enable();

	oldint09();
}

void interrupt newint0B(...){

	while (inp(COM2 + 5) & 0x01)
	{
		int in = inp(COM2);
		if (in == 42)
			showMessage(message2);
		else
			showMessage(message1);
	}
	outp(0x20, 0x20);
	oldint0B();
}

void comPut(char chr){
	while (!(inp(COM2 + 5) & 0x20));
	outp(COM2 + 0, chr);
}

void comInit() {

	oldint08 = getvect(0x08);
	setvect(0x08, newint08);
	oldint09 = getvect(0x09);
	setvect(0x09, newint09);
	oldint0B = getvect(0xB);
	setvect(0xB, newint0B);

	long baud = 0x1;
	int lcr;
	lcr = inp(COM2 + 3);
	outp(COM2 + 3, lcr | 0x80);
	outp(COM2 + 0, baud & 0xFF);
	outp(COM2 + 1, baud >> 8);
	outp(COM2 + 3, lcr & 0x7f);

	outp(COM2 + 1, 0);						//ie				
	outp(COM2 + 3, 0x1b);					//lcr
	outp(COM2 + 4, 0x00);					//mcr
}

void showMessage(char *message) {
	VIDEO far* screen = (VIDEO far*)MK_FP(0xB800, 0);
	
	int color = 14;
	int len = strlen(message);
	int i = 0;
	screen += 80-len;
	for (i = 0; i < len; ++i) {
		screen->symbol = message[i];
		screen->attribute = color;
		++screen;
	}
}