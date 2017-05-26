#include<stdio.h>                 
//#include<time.h> 
#include<stdlib.h>
//#include <iostream> 
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
DWORD WINAPI MyThread1(PVOID pvParam)
{
	//for (int a = 0; a<10; a++)
	//{
	//	printf("%d ", a);

	//	Sleep(2000);
	//}
	//int i = PlaySound(L"c:\\test\\t.wav", NULL,  SND_FILENAME | SND_SYNC);
	//PlaySound(TEXT("c:\\test\\vlc.wav"), NULL, SND_FILENAME | SND_SYNC);
	//PlaySound(TEXT("c:\\test\\ForTheWin.wav"), NULL, SND_FILENAME);
	//PlaySound(TEXT("c:\\test\\ForTheWin.wav"), NULL, NULL);
	PlaySound(TEXT("ForTheWin.wav"), NULL, NULL);


	return 0;

}
//#include "mmsystem.h"//导入声音头文件
void main0()
{
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	//PlaySound(TEXT("SystemWelcome"), NULL, SND_ALIAS|SND_SYSTEM);
	//PlaySound(TEXT("w.wma"), NULL, SND_FILENAME);
	//PlaySound(TEXT("c:\\test\\t.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//int i = PlaySound(L"c:\\test\\t.wav", NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);

	//int i = PlaySound(L"c:\\test\\w.wma", NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
	//int i = PlaySound(L"c:\\test\\t.wav", NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
	//int i = sndPlaySound(L"c:\\test\\t.wav", SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
	//int i = sndPlaySound(L"c:\\test\\t.wav", SND_NODEFAULT | SND_FILENAME);
	//int i = sndPlaySound(TEXT("C:\\test\\t.wav"), SND_NODEFAULT | SND_FILENAME | SND_SYNC);
	//int i = PlaySound(TEXT("C:\\test\\t.wav"),NULL, SND_NODEFAULT | SND_FILENAME | SND_SYNC);
	//int i = sndPlaySound(TEXT("c:\\test\\t.wav"),  SND_FILENAME  );
	//PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);
	//printf("%d", i);

	getchar();
	CloseHandle(hThread1);
	system("pause");
}