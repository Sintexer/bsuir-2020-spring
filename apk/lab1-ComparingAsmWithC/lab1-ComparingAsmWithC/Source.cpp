#include <stdio.h>
#include <time.h>

#define BEGIN 0
#define END 200000
#define STEP 0.001

void printInfo(const char* info, double result, double time) {
	printf("%s\n", info);
	printf("Result: %.5lf\n", result);
	printf("Time: %lf\n\n", time / CLOCKS_PER_SEC);
}

void cWhile() {
	double x = BEGIN, f = 0, step = STEP;
	time_t start = clock(), end;
	while (x < END)
	{
		f += (x + 1) / (x * x + 1);
		x += step;
	}
	end = clock();
	printInfo("C While", f, (double)end - start);
}


void cFor() {
	double x = BEGIN, f = 0, step = STEP;
	time_t start = clock(), end;
	for (x; x < END; x += step)
	{
		f += (x + 1) / (x * x + 1);
	}
	end = clock();
	printInfo("C For", f, (double)end - start);
}

void asmWhile() {
	double x = BEGIN, f = 0, step = STEP, one = 1;
	time_t start = clock(), end;
	while (x < END) {
		_asm {
			FLD x
			FADD one
			FLD x
			FMUL x
			FADD one
			FDIVP ST(1), ST(0)
			FADD f
			FSTP f
		}
		x += step;
	}
	end = clock();
	printInfo("asm While", f, (double)end - start);
}

void asmFor() {
	double x = BEGIN, f = 0, step = STEP, one = 1;
	time_t start = clock(), end;
	for (x; x < END; x += step) {
		_asm {
			FLD x
			FADD one
			FLD x
			FMUL x
			FADD one
			FDIVP ST(1), ST(0)
			FADD f
			FSTP f
		}
	}
	end = clock();
	printInfo("asm For", f, (double)end - start);
}

void asmLoop() {
	double x = BEGIN, f = 0, step = STEP, one = 1;
	int counter = (END - BEGIN) / STEP + 1;
	if (counter < (END - BEGIN) / STEP + 1)
		++counter;
	time_t start = clock(), end;
	_asm {
		mov ecx, counter
		cycle :
		FLD x
			FADD one
			FLD x
			FMUL x
			FADD one
			FDIVP ST(1), ST(0)
			FADD f
			FSTP f
			FLD x
			FADD step
			FSTP x
			loop cycle
	}
	end = clock();
	printInfo("asm Loop", f, (double)end - start);
}

int main(void) {
	cWhile();
	cFor();
	asmWhile();
	asmFor();
	asmLoop();
	return 0;
}