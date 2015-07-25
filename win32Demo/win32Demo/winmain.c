#include <Windows.h>
#include"resource.h"

//�����Ǻܶ�Windows��ɵ����л��ƣ����Ǹо���дɨ�ײ�࣬��ȥ�������·ݵ���Ƶ��������������

#define WIN32_LEAN_AND_MEAN//��Windows�����ų������õĿ�

HINSTANCE g_hInst;
LPCTSTR g_lpszClassName = L"wym Win32Demo";//����
LPCTSTR g_lpszTittleName = L"";//������

ATOM MyRegisterClass(HINSTANCE hInst);//�����������ע��

int InitInstance(HINSTANCE hInst, int nCmdShow);//ʵ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//���ڹ��̣���Ϣ�ã�������������

VOID CALLBACK TimerProc(HWND hWnd, UINT msg, UINT_PTR idEvent, DWORD dwTime);//ʱ����̺���

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_hInst = hInstance;
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nShowCmd);
	//WINDOWS��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}

ATOM MyRegisterClass(HINSTANCE hInst)//�����������ע��
{
	WNDCLASS wc;
	wc.cbWndExtra = 0;//���ڵĶ�����Ϣ��Ϊ��
	wc.cbClsExtra = 0;//����Ĵ�����Ϣ��Ϊ��
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ڵı�����ɫ��ˢ��Ĭ�ϰ�ɫ
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//�����꣬Ĭ�ϵ�
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����Ĭ�ϵ�ͼ��
	wc.hInstance = hInst;//��������������ĸ����̣�����hInst����
	wc.lpfnWndProc = WndProc;//�������һ�к�����wndproc����Ӧ�����������wndproc��������Ӧ
	wc.lpszClassName = g_lpszClassName;//
	wc.lpszMenuName = NULL;//û�в˵��������ÿ�
	wc.style = CS_HREDRAW | CS_VREDRAW;//ˮƽ�ػ棬����ֱ�ػ�
	return RegisterClass(&wc);

}

int InitInstance(HINSTANCE hInst, int nCmdShow)//ʵ����
{
	//�������࣬ʵ�ֳ�������ʾ����
	HWND hWnd;
	hWnd = CreateWindow(g_lpszClassName, g_lpszTittleName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,
		hInst,NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);//����paint����Ϣ�����ػ�
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	RECT rect;
	HDC hDC, hDCMem;	//���豸�ϻ��ƣ�����bitmap��
	HBITMAP hBmp;		//λͼ�ľ��
	PAINTSTRUCT ps;		//��ͼ�Ľṹ
	BITMAP bmp;
	HGDIOBJ hGdiObj;

	static int x = 0, y = 0;
	static BOOL bDtX = TRUE, bDtY = TRUE;


	//��д�Զ������Ϣ�Ĵ���ʽ
	switch (msg)
	{
	case WM_CREATE:
		MessageBeep(MB_ICONINFORMATION);
		MessageBox(NULL, L"���ڴ����ˣ���", L"WM_CREATE",MB_OK | MB_ICONINFORMATION);
		SetTimer(hWnd, IDE_TIMER, 10, TimerProc);//��ʱ���¼�,ÿ���Ǻ������һ��TimerProc
		break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);//�˳�,����WM_quit
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rect);
		hDC = BeginPaint(hWnd, &ps);
		hDCMem = CreateCompatibleDC(hDC);//���������ڴ��DC
		hBmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_xinxin));
		GetObject(hBmp,sizeof(BITMAP),&bmp);
		hGdiObj = SelectObject(hDCMem, hBmp);
		BitBlt(hDC, x, y, bmp.bmWidth, bmp.bmHeight, hDCMem, 0, 0, SRCCOPY);//������x,y����λ�ñ仯
		if ((bDtX && ++x == rect.right - rect.left - bmp.bmWidth) || (!bDtX && --x == 0))
			bDtX = 1 - bDtX;
		if ((bDtY && ++y == rect.bottom - rect.top - bmp.bmHeight) || (!bDtY && --y == 0))
			bDtY = 1 - bDtY;
		// ReleaseDC() �� GetDC() ���
		DeleteDC(hDCMem);
		DeleteObject(hGdiObj);

		EndPaint(hWnd,&ps);

		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);//WindowsĬ�ϵ���Ϣ����
}
VOID CALLBACK TimerProc(HWND hWnd, UINT msg, UINT_PTR idEvent, DWORD dwTime)
{
	if (idEvent == IDE_TIMER)
	{
		RECT rect;
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd, &rect, TRUE);//����WM_Paint
	}
}