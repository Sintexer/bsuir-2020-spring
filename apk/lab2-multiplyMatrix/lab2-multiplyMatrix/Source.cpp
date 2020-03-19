#include <stdio.h>
#include <time.h>
const int SIZE = 4;
const int ITERATIONS = 1'000'000;
typedef short word;
const int mmx_count = SIZE / 4;
const int qw = 8;

using namespace std;

void printTime(const char* str, double time) {
	printf("%s\ntime: %f\n\n", str, time);
}

void mmxCode() {
	word matrix1[SIZE * SIZE] = { 1, 2, 3, 4, 5,6,7,8,9,10,11,12,13,14,15,16 },
		matrix2[SIZE * SIZE] = { 1, 2, 3, 4, 5,6,7,8,9,10,11,12,13,14,15,16 };
	int result[SIZE * SIZE]{};
	//long long c = 0x0002'0002'0002'0002;
	word temp[4]{};
	int m{};
	int sz{ SIZE }, dsz{ SIZE * 2 };
	long c{};
	clock_t start, stop;
	start = clock();
	_asm {
		mov ecx, ITERATIONS
		repeat ://Цикл по числу итераций
		push ecx//
			xor esi, esi
			xor edi, edi
			xor eax, eax
			mov ecx, sz//Цикл по строкам
			loop0 :
		push ecx//
			push esi//
			mov ecx, sz//Цикл по столбцам
			xor edi, edi
			loopj :
		push ecx//
			push edi//
			push esi//
			mov result[eax], 0//Обнуление матрицы результата для внешнего цикла по итерациям
			mov ecx, mmx_count//Цикл по числу qw в столбце(строке)
			loop1 :
		///Этот код нужен для того, чтобы извлечь фрагмент текущей колонки в qw (массив temp)
	get_column:
		push esi//
			push eax//
			push edi//
			push ecx//
			xor eax, eax
			mov eax, mmx_count	//Переход к нужному qw в колонке, edi - номер колонки
			sub eax, ecx		//j=(mmx_count-ecx)*8*sz+edi
			mul qw
			mul sz
			add eax, edi
			mov esi, eax
			xor eax, eax
			xor eax, eax
			mov eax, sz
			dec eax
			mul qw
			add eax, edi
			mov esi, eax
			mov ecx, 4//Цикл по qw в колонке
			four_loop:
		psllq MM1, 16
			xor eax, eax
			mov ax, matrix2[esi]
			movd MM2, eax
			paddw MM1, MM2
			xor eax, eax
			mov eax, 1
			mul qw
			sub esi, eax
			loop four_loop
			pop ecx//
			pop edi//
			pop eax//
			pop esi//
			///


			movq MM0, matrix1[esi]
			pmaddwd MM0, MM1
			movq MM1, MM0
			psrlq MM1, 32
			paddd MM0, MM1
			xor ebx, ebx
			movd ebx, MM0
			add result[eax], ebx //Сохранение результата
			add esi, qw //Переход к следующему qw в строке
			dec ecx
			cmp ecx, 0
			jne loop1
			pop esi//
			pop edi//
			pop ecx//
			add edi, 2	//Переход к следующему столбцу
			add eax, 4	//переход к следующему элементы выходного массива
			dec ecx
			cmp ecx, 0
			jne loopj
			emms
			pop esi//
			push eax//
			xor eax, eax
			mov eax, qw
			mul mmx_count
			add esi, eax
			pop eax//
			pop ecx//
			dec ecx
			cmp ecx, 0
			jne loop0
			pop ecx//
			dec ecx
			cmp ecx, 0
			jne repeat
	}
	stop = clock() - start;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			printf("%4d", result[i * SIZE + j]);
		}
		printf("\n");
	}

	printTime("MMX", (double)stop / CLOCKS_PER_SEC);
}

void asmCode() {
	word matrix1[SIZE * SIZE] = { 1, 2, 3, 4, 5,6,7,8,9,10,11,12,13,14,15,16 },
		matrix2[SIZE * SIZE] = { 1, 2, 3, 4, 5,6,7,8,9,10,11,12,13,14,15,16 };
	int result[SIZE * SIZE]{};
	int m{};
	int sz{ SIZE };
	long c{};
	clock_t start, stop;
	start = clock();
	_asm {
		mov ecx, ITERATIONS
		repeat :
		push ecx
			xor esi, esi
			xor edi, edi
			xor edx, edx
			mov ecx, sz;
	loop0:
		push ecx
			mov ecx, sz
			loop1 :
		push ecx
			xor ebx, ebx
			push ebx
			mov ecx, sz
			loop2 :
		pop ebx
			push esi
			push edi
			mov eax, esi
			mul sz
			add eax, m
			mov esi, eax
			mov eax, m
			mul sz
			add eax, edi
			mov edi, eax
			mov ax, matrix1[esi]
			mov dx, matrix2[edi]
			mul dx

			add ebx, eax
			pop edi
			pop esi
			add m, 2
			push ebx
			loop loop2
			pop ebx
			pop ecx
			mov eax, esi
			mul sz
			mov dx, 2
			mul dx
			add eax, edi
			add eax, edi
			mov result[eax], ebx
			mov m, 0
			add edi, 2
			loop loop1
			pop ecx
			add esi, 2
			xor edi, edi
			dec ecx
			cmp ecx, 0
			jne loop0
			pop ecx
			dec ecx
			cmp ecx, 0
			jne repeat
	}
	stop = clock() - start;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			printf("%4d", result[i * SIZE + j]);
		}
		printf("\n");
	}

	printTime("ASM", (double)stop / CLOCKS_PER_SEC);
}

void cCode() {
	word matrix1[SIZE][SIZE] = { {1, 2, 3, 4}, {5,6,7,8} , {9,10,11,12}, {13,14,15,16} },
		matrix2[SIZE][SIZE] = { {1, 2, 3, 4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} },
		result[SIZE][SIZE]{};
	short c{};
	clock_t start, stop;
	start = clock();
	for (int k = 0; k < ITERATIONS; ++k) {

		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				c = 0;
				for (int m = 0; m < SIZE; ++m) {
					c += matrix1[i][m] * matrix2[m][j];
				}
				result[i][j] = c;
			}
		}
	}

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			printf("%4d", result[i][j]);
		}
		printf("\n");
	}

	stop = clock() - start;
	printTime("C", (double)stop / CLOCKS_PER_SEC);
}

int main() {
	cCode();
	asmCode();
	mmxCode();
	return 0;
}