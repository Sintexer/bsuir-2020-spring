#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
void main()
{
	/*time_t t;
	t = time(NULL);
	printf("%s%s", ctime(&t), "Child ^^^^\n");*/
    Sleep(3000);
    SYSTEMTIME st;

    GetLocalTime(&st);

    printf("%d-%02d-%02d %02d:%02d:%02d.%03d\nChild^^^\n",
        st.wYear,
        st.wMonth,
        st.wDay,
        st.wHour,
        st.wMinute,
        st.wSecond,
        st.wMilliseconds);
    getchar();
}