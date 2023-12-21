/********************************************************************/
/*                            lek_graph1.cpp                        */
/*                            ============                          */
/*    ������  ��  ��������  �������.                                */
/*    �������������� �  ��������  ������  ���������                 */
/********************************************************************/
#define STRICT
#define  PI       3.14159265
#include <stdio.h>
#include <malloc.h>


#include <windows.h>
#include <windowsx.h>

 // ���� ���������� � ����������� ����� ��������� ���������� (common controls)
#include <commctrl.h>

 // ���� ���������������� ��������������� �������� � ��������� ����������
 #include "resource.h"
#include "tdef.h"

 // �������� ����������
HINSTANCE hiApp;                           // ����� ������
char aczAppName[] = "���������� ��������"; // ���
HICON hiconAppSmall, hiconAppBig;          // ����������� ����������

// --- ������� ���� ---
HWND hwndMain;                                                    // ����������
LPCSTR pczMainWndClassName = "MainWndClass";                      // ��� ������
LPCSTR pczMainWndTitle = "������� '������' ������/���������";  // ����� ���������
HMENU  hmenuMain;                                                 // ���������� ����

// --- ���������� ���� ---
HWND hwndDlg;

// --- ������� ������� � ����������� ��������� �������� ���� ---
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL MainOnCreate(HWND, LPCREATESTRUCT);
BOOL MainOnPaint(HWND);
BOOL polet_snar(HWND);
BOOL MainOnDestroy(HWND);

// --- ������� ������������� � ���������� ---
BOOL RegisterWndClasses(void);
void UnregisterWndClasses(void);
BOOL CreateWindows(void);
void InitializeApp(void);
void UninitializeApp(void);

// ������� - ����� �����
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

int* Scale_coor_w(HWND, RECT, double*, int);
double* make_mas_coor(int*);
BOOL   anim_main(HWND hwnd);

/*----------------------------------*/
/*  ������, ���������� ���������    */
/*----------------------------------*/
 // --- ������ ---
 // �������� ������� (����)
#define TIMER_INTERVAL 10
 // �������������
#define TIMER_ID 1000


 // --- ������ ---
 // �������
int timer = -1;

#define  K_GAB 0.05  // ����������  ����������� �������
//  ���������� ����������� �� ���� ������� ������




