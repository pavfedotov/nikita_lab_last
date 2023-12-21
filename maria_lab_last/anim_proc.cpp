/********************************************************************/
/*                           anim_proc                              */
/*                           =========                              */
/*    Функции для анимации  произвольного набора плоских объектов   */
/*                                                                  */
/********************************************************************/
#include "tdef.cpp"
#include <random>

#include "resource.h"
#include <random>
using namespace std;
 // свойства приложения
HINSTANCE hiApp;                           // адрес модуля
char aczAppName[] = "Диалоговые элементы"; // имя
HICON hiconAppSmall, hiconAppBig;          // дескрипторы пиктограмм

// --- главное окно ---
HWND hwndMain;                                                    // дескриптор
LPCSTR pczMainWndClassName = "MainWndClass";                      // имя класса
LPCSTR pczMainWndTitle = "Клавиша 'F1' запуск/остановка";  // текст заголовка
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
double fRand(double fMin, double fMax);
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

#define ALL_STEP       1000        // число  временных  интервалов
#define X_SPACE_ANIM   100.0      // Размер области вывода по X
#define Y_SPACE_ANIM    70.0      // Размер области вывода по Y
#define DX X_SPACE_ANIM/ALL_STEP  // шаг анимации по X
#define DY Y_SPACE_ANIM/ALL_STEP  // шаг анимации по Y

#define  K_SCALE  0.1           // коэффициент пропорциональности

#define  K_SC     X_SPACE_ANIM * K_SCALE  // масштабный коэфф.


#define  K_GAB    0.1           // Габаритный  коэффициент отступа
								//  выводимого изображение от края границы вывода

#define  PI       3.14159265
HDC hdc;

HBRUSH 	hbr[] = { CreateSolidBrush(RGB(255, 0, 0)),
				  CreateSolidBrush(RGB(0, 255, 0)),
				  CreateSolidBrush(RGB(0, 0, 255)),
				  CreateSolidBrush(RGB(255, 255, 255)),
				  CreateSolidBrush(RGB(255, 205, 72)),
				  CreateSolidBrush(RGB(127, 199, 255)),
	CreateSolidBrush(RGB(193, 68, 14)),
	CreateSolidBrush(RGB(173, 173, 173)),
	CreateSolidBrush(RGB(227, 187, 118))
},
hbr_prv;


int pr_start = 0, all_br = sizeof(hbr) / sizeof(hbr[0]),znak = 1;;
CMatr  mpr;
int action = 0;
int k = 0;
int sc_start = 0;
double v;
double v2;
double vec = 0, vec_2 = 0;
double vec_x = 0, vec_2x = 0;
/********************************************************************/
/*                        anim_main                                 */
/*                        ==========                                */
/*      Управляющая  процедура  отрисовки  полёта  квадрата         */
/********************************************************************/

CVect  kv1[ALL_PT] =
{ {  -0.6,   -0.5  },
	{  -0.6,   0.5 },
	{  0.6,   0.5 },
	{  0.6,   -0.5 }
};
CVect  kv2[ALL_PT] =
{ {  -0.6,   -0.5  },
	{  -0.6,   0.5 },
	{  0.6,   0.5 },
	{  0.6,   -0.5 }
};
CVect k1[ALL_PT], k2[ALL_PT];




GO_SHAPE

KV1(kv1, 4, DX, DY, 0, K_SC, K_SC,
	X_SPACE_ANIM, 0, SUN, X_SPACE_ANIM),
	KV2(kv2, 4, DX, DY, 0, -K_SC, K_SC,
		X_SPACE_ANIM, 0, RED, X_SPACE_ANIM);


BOOL  anim_main(HWND hwnd)
{
	

	int    i;
	double dx, dy, ang, f = fRand(0.25, 3), f2 = fRand(0.25, 3);

	extern int timer;
	extern double a_random_double;
	CVect vt, vt_wing;
	double d_ang = PI / 32;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);

	if (pr_start == 0)
	{
		pr_start = 1;
		EndPaint(hwnd, &ps);
		return TRUE;
	}

	// определить размеры клиентской области окна
	if (timer == 0)
	{
		RECT rc;
		GetClientRect(hwnd, &rc);

		mpr = make_matr_pr(rc);
	}

	/*---------------------------------------*/
	/*      Текущая перерисовка              */
	/*---------------------------------------*/
	double dk = double(timer) / (ALL_STEP );
	
	
	
	

	switch (action) {
	case roteKV1:
		KV1.ang += PI / 320;
		k++;
		if (k == 160) {
			action = -1;
			k = 0;
		}
		break;
	case roteKV2:
		KV2.ang += PI / 320;
		k++;
		if (k == 160) {
			action = -1;
			k = 0;
		}
		break;
	case scale:
		for (int i = 0; i < 4; i++)
		{
			if (sc_start == 0)
			{
				for (int j = 0; j < 4; j++) {
					k1[j].x = KV1.kvadro[j].x;
					k1[j].y = KV1.kvadro[j].y;
				}

				KV1.kvadro[i].x = k1[i].x * f;
				KV1.kvadro[i].y = k1[i].y * f;
				KV2.kvadro[i].x = k1[i].x * f2;
				KV2.kvadro[i].y = k1[i].y * f2;
				sc_start = 1;

			}
			else {
				KV1.kvadro[i].x = k1[i].x * f;
				KV1.kvadro[i].y = k1[i].y * f;
				KV2.kvadro[i].x = k1[i].x * f2;
				KV2.kvadro[i].y = k1[i].y * f2;
			}


		}
		action = -1;
	case vec1:
		vec = v;
		vec = vec * k / 160;
		vec_x = v2;
		vec_x = vec_x * k / 160;
		k++;
		if (k == 160) {
			action = -1;
			k = 0; break;
		}
		break;
	case vec2:
		vec_2 = v;
		vec_2x = v2;
		vec_2 = vec_2*k/ 160;
		vec_2x = vec_2x * k / 160;
		k++;
		if (k == 160) {
			action = -1;
			k = 0; break;
		}
		break;
	default:
		break;
	}

	KV1.vt.x = X_SPACE_ANIM / 4 + vec_x;
	KV1.vt.y = Y_SPACE_ANIM / 4 + vec;
	KV2.vt.x = X_SPACE_ANIM - X_SPACE_ANIM / 4 + vec_2x;
	KV2.vt.y = Y_SPACE_ANIM - Y_SPACE_ANIM / 4 + vec_2;

	KV1.move();
	KV2.move();
	/*---------------------------------------*/


	EndPaint(hwnd, &ps);

	return TRUE;
}


/********************************************************************/
/*                        draw_polygon                              */
/*                        ============                              */
/*      Рисование многоугольника  на экране по  вещественным коорд  */
/********************************************************************/
void draw_polygon(HDC hDc, CVect* pVect, int nPoints)
{
	POINT* pPnt = new POINT[nPoints];
	for (int i = 0; i < nPoints; i++) {
		pPnt[i].x = LONG(pVect[i].x);
		pPnt[i].y = LONG(pVect[i].y);
	}
	Polygon(hDc, pPnt, nPoints);
	delete[] pPnt;
}



/********************************************************************/
/*                        make_matr_pr                              */
/*                        ============                              */
/*              Формирование  матрицы  проекции                     */
/********************************************************************/
CMatr  make_matr_pr(RECT& cp)
{
	int a, b, gab_a, gab_b, xc_w, yc_w;
	double x_max, y_max, x_min, y_min, k_scale, k1, k2,
		dx, dy, xc, yc, l_snar, l_pushka;

	CMatr  mt1, ms, mr, mt2;

	CVect  vt;


	/*--------------------------------*/
	/*  Параметры  окна  вывода       */
	/*--------------------------------*/
	a = abs(cp.right - cp.left);
	b = abs(cp.top - cp.bottom);

	gab_a = (int)((double)a * K_GAB);  // отступ по ширине
	gab_b = (int)((double)b * K_GAB);  // отступ по высоте

	a -= gab_a;
	b -= gab_b;

	xc_w = (cp.right + cp.left) / 2;
	yc_w = (cp.top + cp.bottom) / 2;

	/*-----------------------------------------*/
	/*  Определение  масштабного коэффициента  */
	/*-----------------------------------------*/
	x_min = 0;
	y_min = 0;

	x_max = X_SPACE_ANIM;
	y_max = Y_SPACE_ANIM;

	dx = fabs(x_max - x_min);
	dy = fabs(y_max - y_min);

	xc = (x_max + x_min) / 2;
	yc = (y_max + y_min) / 2;

	k1 = a / dx;
	k2 = b / dy;

	k_scale = (k1 < k2) ? k1 : k2;


	vt.x = -xc;
	vt.y = -yc;
	MatrTransl(mt1, vt);
	MatrScale(ms, k_scale, k_scale);
	// Зеркальное отображение
	MatrScale(mr, 1, -1);

	vt.x = xc_w;
	vt.y = yc_w;
	MatrTransl(mt2, vt);

	return (mt1 * ms * mr * mt2);
}

/********************************************************************/
/*                           trans_coor                             */
/*                           ==========                             */
/*  Изменение массива координат  по  матрице  преобразований        */
/********************************************************************/

void trans_coor(CVect* pvOld, CVect* pvNew, int all_pt, CMatr& mpr)
{
	for (int i = 0; i < all_pt; i++)
		pvNew[i] = pvOld[i] * mpr;
}




/********************************************************************/
/*                            MainWndProc                           */
/*                            ============                          */
/*                      оконная функция главного окна               */
/********************************************************************/

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT  pm;
	pm.x = LOWORD(lParam);
	pm.y = HIWORD(lParam);

	HRGN c1 = CreateEllipticRgn(KV1.kvadro_win[1].x, KV1.kvadro_win[1].y, KV1.kvadro_win[3].x, KV1.kvadro_win[3].y),
		c2 = CreateEllipticRgn(KV2.kvadro_win[1].x, KV2.kvadro_win[1].y, KV2.kvadro_win[3].x, KV2.kvadro_win[3].y);
	switch (msg) {

	case WM_KEYDOWN:
		if (LOWORD(wParam) == VK_F1)
		{

			InvalidateRect(hwnd, NULL, TRUE);
			if (-1 == timer)
				SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
			else
			{
				KillTimer(hwnd, TIMER_ID);
				timer = -1;
			}
		}
		if (LOWORD(wParam) == VK_SPACE)
		{
			
			action = scale;
		}

		break;

	case WM_PAINT:
		return anim_main(hwnd);
		break;
	case WM_TIMER:
		timer++;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:

		
		if(PtInRegion(c1, pm.x, pm.y) == 1)
		{
			action = roteKV1; break;
		}
		if (PtInRegion(c2, pm.x, pm.y) == 1)
		{
			action = roteKV2; break;
		}
		
		break;
	case WM_RBUTTONDOWN:
		v2 = fRand(-20, 20);
		v = fRand(-20, 20);
		if (PtInRegion(c1, pm.x, pm.y) == 1)
		{
			action = vec1; break;
		}
		if (PtInRegion(c2, pm.x, pm.y) == 1)
		{
			action = vec2; break;
		}

		break;
	case WM_DESTROY:
		return MainOnDestroy(hwnd);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0L;
}  //func MainWndProc


/***********************************************/
/*               MainOnDestroy                 */
/*               =============                 */
/*          обработчик WM_DESTROY              */
/***********************************************/

BOOL MainOnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
	return TRUE;
}  //func MainOnDestroy


/***********************************************/
/*               RegisterWndClasses            */
/*               ==================            */
/*     регистрация классов окон в БД Windows   */
/***********************************************/

BOOL RegisterWndClasses()
{
	// инициализация структуры описания класса окон
	WNDCLASSEX wce_main;
	memset(&wce_main, 0, sizeof(WNDCLASSEX));
	wce_main.cbSize = sizeof(WNDCLASSEX);
	wce_main.hInstance = hiApp;
	wce_main.style = CS_VREDRAW | CS_HREDRAW;
	// wce_main.hIcon = LoadIcon(hiApp, MAKEINTRESOURCE(IDI_ICON));
	wce_main.lpfnWndProc = (WNDPROC)MainWndProc;
	wce_main.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce_main.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// wce_main.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wce_main.lpszClassName = pczMainWndClassName;
	return RegisterClassEx(&wce_main);
}  //func RegisterWndClasses


/***************************************************/
/*               UnregisterWndClasses              */
/*               ====================              */
/*   удаление описания классов окон из БД Windows  */
/***************************************************/

void UnregisterWndClasses()
{
	UnregisterClass(pczMainWndClassName, hiApp);
}  //func UnregisterWndClasses


/***************************************************/
/*               CreateWindows                     */
/*               =============                     */
/*     функция создания основных окон              */
/***************************************************/
BOOL CreateWindows()
{
	// определение размеров экрана в пикселах
	int scrw2 = GetSystemMetrics(SM_CXSCREEN) / 2,
		scrh2 = GetSystemMetrics(SM_CYSCREEN) / 2;
	// создание главного окна
	hwndMain = CreateWindow(pczMainWndClassName, pczMainWndTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		scrw2 - 400, scrh2 - 300, 800, 600, NULL, NULL, hiApp, NULL);
	if (!hwndMain)
		return FALSE;
	return TRUE;
}  //func CreateWindows

/***************************************************/
/*               InitializeApp                     */
/*               =============                     */
/*     предварительные действия                    */
/***************************************************/
void InitializeApp()
{
	RegisterWndClasses();
	CreateWindows();
	ShowWindow(hwndMain, SW_SHOW);
	UpdateWindow(hwndMain);
}  //func InitializeApp


/***************************************************/
/*               UninitializeApp                   */
/*               ===============                   */
/*     заключительные  действия                    */
/***************************************************/
void UninitializeApp()
{

	extern HBRUSH hbr[];

	extern int all_br;

	for (int i = 0; i < all_br; i++)
		DeleteObject(hbr[i]);

	UnregisterWndClasses();
}  //func UninitializeApp

/***************************************************/
/*                 WinMain                         */
/*                 =======                         */
/*        Главная  функция                         */
/***************************************************/

int APIENTRY WinMain(HINSTANCE hiApp__, HINSTANCE, LPSTR, int)
{
	MSG msg;
	hiApp = hiApp__;

	InitializeApp();
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);
	UninitializeApp();

	return msg.wParam;
}  //func WINMAIN

double fRand(double fMin, double fMax)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> dis(fMin, fMax);

	return  dis(gen);
}