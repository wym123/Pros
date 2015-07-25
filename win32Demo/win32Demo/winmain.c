#include <Windows.h>
#include"resource.h"

//并不是很懂Windows变成的运行机制，但是感觉和写扫雷差不多，回去看看六月份的视频！！！！！！！

#define WIN32_LEAN_AND_MEAN//从Windows库中排出极少用的库

HINSTANCE g_hInst;
LPCTSTR g_lpszClassName = L"wym Win32Demo";//类名
LPCTSTR g_lpszTittleName = L"";//标题名

ATOM MyRegisterClass(HINSTANCE hInst);//窗口类设计与注册

int InitInstance(HINSTANCE hInst, int nCmdShow);//实例化

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//窗口过程，消息泵！！引爆器！！

VOID CALLBACK TimerProc(HWND hWnd, UINT msg, UINT_PTR idEvent, DWORD dwTime);//时间过程函数

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_hInst = hInstance;
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nShowCmd);
	//WINDOWS消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}

ATOM MyRegisterClass(HINSTANCE hInst)//窗口类设计与注册
{
	WNDCLASS wc;
	wc.cbWndExtra = 0;//窗口的额外信息置为零
	wc.cbClsExtra = 0;//额外的窗口信息置为零
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//窗口的背景颜色画刷，默认白色
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//载入光标，默认的
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//载入默认的图标
	wc.hInstance = hInst;//这个窗口类属于哪个进程，属于hInst进程
	wc.lpfnWndProc = WndProc;//窗口里的一切函数由wndproc来响应，就是下面的wndproc函数来响应
	wc.lpszClassName = g_lpszClassName;//
	wc.lpszMenuName = NULL;//没有菜单，所以置空
	wc.style = CS_HREDRAW | CS_VREDRAW;//水平重绘，和竖直重绘
	return RegisterClass(&wc);

}

int InitInstance(HINSTANCE hInst, int nCmdShow)//实例化
{
	//将窗口类，实现出来，显示出来
	HWND hWnd;
	hWnd = CreateWindow(g_lpszClassName, g_lpszTittleName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,
		hInst,NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);//发送paint的信息，来重绘
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	RECT rect;
	HDC hDC, hDCMem;	//在设备上绘制，加载bitmap的
	HBITMAP hBmp;		//位图的句柄
	PAINTSTRUCT ps;		//绘图的结构
	BITMAP bmp;
	HGDIOBJ hGdiObj;

	static int x = 0, y = 0;
	static BOOL bDtX = TRUE, bDtY = TRUE;


	//编写自定义的消息的处理方式
	switch (msg)
	{
	case WM_CREATE:
		MessageBeep(MB_ICONINFORMATION);
		MessageBox(NULL, L"窗口创建了！！", L"WM_CREATE",MB_OK | MB_ICONINFORMATION);
		SetTimer(hWnd, IDE_TIMER, 10, TimerProc);//定时器事件,每隔是毫秒调用一次TimerProc
		break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);//退出,发送WM_quit
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rect);
		hDC = BeginPaint(hWnd, &ps);
		hDCMem = CreateCompatibleDC(hDC);//创建兼容内存的DC
		hBmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_xinxin));
		GetObject(hBmp,sizeof(BITMAP),&bmp);
		hGdiObj = SelectObject(hDCMem, hBmp);
		BitBlt(hDC, x, y, bmp.bmWidth, bmp.bmHeight, hDCMem, 0, 0, SRCCOPY);//就是用x,y控制位置变化
		if ((bDtX && ++x == rect.right - rect.left - bmp.bmWidth) || (!bDtX && --x == 0))
			bDtX = 1 - bDtX;
		if ((bDtY && ++y == rect.bottom - rect.top - bmp.bmHeight) || (!bDtY && --y == 0))
			bDtY = 1 - bDtY;
		// ReleaseDC() 与 GetDC() 相对
		DeleteDC(hDCMem);
		DeleteObject(hGdiObj);

		EndPaint(hWnd,&ps);

		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);//Windows默认的消息处理
}
VOID CALLBACK TimerProc(HWND hWnd, UINT msg, UINT_PTR idEvent, DWORD dwTime)
{
	if (idEvent == IDE_TIMER)
	{
		RECT rect;
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd, &rect, TRUE);//发送WM_Paint
	}
}