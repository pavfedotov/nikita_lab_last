/********************************************************************/
/*                            lek_graph1.cpp                        */
/*                            ============                          */
/*    Лекции  по  машинной  графике.                                */
/*    Масштабироваие в  экранную  ситему  координат                 */
/********************************************************************/
#define STRICT
#define  PI       3.14159265
#include <stdio.h>
#include <malloc.h>


#include <windows.h>
#include <windowsx.h>

 // файл прототипов и определений общих элементов управления (common controls)
#include <commctrl.h>

 // файл макроопределений идентификаторов ресурсов и элементов управления
 #include "resource.h"
#include "tdef.h"

 // свойства приложения
HINSTANCE hiApp;                           // адрес модуля
char aczAppName[] = "Диалоговые элементы"; // имя
HICON hiconAppSmall, hiconAppBig;          // дескрипторы пиктограмм

// --- главное окно ---
HWND hwndMain;                                                    // дескриптор
LPCSTR pczMainWndClassName = "MainWndClass";                      // имя класса
LPCSTR pczMainWndTitle = "Клавиша 'пробел' запуск/остановка";  // текст заголовка
HMENU  hmenuMain;                                                 // дескриптор меню

// --- диалоговое окно ---
HWND hwndDlg;

// --- оконная функция и обработчики сообщений главного окна ---
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL MainOnCreate(HWND, LPCREATESTRUCT);
BOOL MainOnPaint(HWND);
BOOL polet_snar(HWND);
BOOL MainOnDestroy(HWND);

// --- функции инициализации и завершения ---
BOOL RegisterWndClasses(void);
void UnregisterWndClasses(void);
BOOL CreateWindows(void);
void InitializeApp(void);
void UninitializeApp(void);

// функция - точка входа
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

int* Scale_coor_w(HWND, RECT, double*, int);
double* make_mas_coor(int*);
BOOL   anim_main(HWND hwnd);

/*----------------------------------*/
/*  данные, переменные состояния    */
/*----------------------------------*/
 // --- таймер ---
 // интервал времени (мсек)
#define TIMER_INTERVAL 10
 // идентификатор
#define TIMER_ID 1000


 // --- таймер ---
 // счётчик
int timer = -1;

#define  K_GAB 0.05  // Габаритный  коэффициент отступа
//  выводимого изображение от края границы вывода




