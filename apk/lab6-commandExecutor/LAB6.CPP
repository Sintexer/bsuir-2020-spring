#include <iostream.h>
#include <dos.h>
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

union REGS i, o;
const int SIZE = 17;

// void init_vect();
void call_int16(int chr);
int index;
int wait;
int clear;
int in=0;
void buffer_clear();
int should_call;
int combo[] = {29, 42, 18};
//const char str[]={13,'l','a','b','4','.','e','x','e',13,'1', 13};
const char input[SIZE] = {13,'l','a','b','5',13, '1', 13, '2', 13, '2', '0', '0', '0', 13, '0', 13};

struct VIDEO
{
	unsigned char symbol;
	unsigned char attribute;
};

VIDEO far* screen = (VIDEO far*)MK_FP(0xB800, 0);
char color = 0x04;

void interrupt(*oldint08) (...);
void interrupt newint08(...);
void interrupt(*oldint09) (...);
void interrupt newint09(...);

int main() {
	oldint09 = getvect(0x09);
	oldint08 = getvect(0x08);
	setvect(0x08, newint08);
	setvect(0x09, newint09);
	unsigned far *fp;                                                 

	printf("%s\n", "Ctrl+Shift+E");

	FP_SEG(fp) = _psp;                          
	FP_OFF(fp) = 0x2c;                          
	_dos_freemem(*fp);                          

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1); 
												
	return 0;
}

void interrupt newint08(...){
	// if(clear){
	// 	call_int16(8);
	// 	if(!wait){
			
	// 		clear = 0;	
	// 	}
	// }
	// else if (wait<1 && should_call){
	// 	if(in<SIZE){
	// 		call_int16(input[in++]);
	// 	}
	// 	else {
	// 		should_call = 0;
	// 	}
	// 	wait = 8;
	// }
	// --wait;
	if (should_call){
		call_int16(input[in++]);
		if (in==SIZE) should_call=0;
	}
 
	
	//oldInt08h();
	oldint08();
}

void interrupt far newint09(...){
 
	_disable();
	int data=inp(0x60);
 
	if (data<128){
 
		if (data==combo[index]) { 
			++index;
			if (index>2) {
				should_call=1;
				index=0;
				in=0;
			}
		}
		else oldint09();
	}
 
	_enable();
	outp(0x20,0x20);
 
}

// void interrupt newint09(...) {
// 	_disable();
// 	int a = inp(0x60);

// 	if(a<128){
// 		i.h.ah = 0x02;
// 		int86(0x16, &i, &i);
// 		// if(a==18 && (i.h.al&4))
// 		// 	{
// 		// 			should_call = 1;
// 		// 			in = 0;
// 		// 			index  = 0;
// 		// 			wait = 100;
// 		// 			clear = 1;
// 		// 		}
// 		if(a==combo[index]){
// 				++index;
// 				if(index>2){
// 					should_call = 1;
// 					in = 0;
// 					index  = 0;
// 					wait = 50;
// 					clear = 1;
// 				}
// 		}
// 		else if(index){
// 			if(a==combo[index-1])
// 				a=a;
// 		}
// 		else{
// 			oldint09();
// 		}
		
// 	}
// 	_enable();
// 	outp(0x20, 0x20);
// }

void call_int16(int chr) {
	i.h.ah = 0x05;
	i.h.cl = chr;
	i.h.ch = 0;
	int86(0x16, &i, &i);
}
