// PlaySound.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "PlaySound.h"
#include <mmsystem.h>
#include <dsound.h>			//	dxsound头文件


#define MAX_LOADSTRING 100
#define TAG_SIZE 4
#define WAV_FMT_SIZE 16

typedef struct tagWavHeader
{
	// RIFF 头
	char szRIFF[TAG_SIZE];			// ‘R’’I’’F’’F’
	DWORD dwRiffSize;				// RIFF 偏移
	char szType[TAG_SIZE];			// ‘W’’A’’V’’E’ 类
	// fmt 字段
	char szFmt[TAG_SIZE];			// ‘f’’m’’t’’ ’
	DWORD dwFmtSize;				// FMT 大小
	WORD wFmtTag;					// 格式标签
	WORD wChannels;					// 声道数目
	DWORD dwSamplesPerSec;			// 采样率标准
	DWORD dwAvgBytesPerSec;			// 平均采样率
	WORD wBlockAlign;				// 内存字节对齐
	WORD wBitsPerSample;			// 单次采样位数
	// data 字段
	char szData[TAG_SIZE];			// 'd''a''t''a'
	DWORD dwDataSize;				// data 偏移
}WavHeader;

//DXsound的全局变量
WavHeader g_wh;
DSBUFFERDESC g_dsbd;//次缓存？
LPDIRECTSOUND8 g_lpDS;	//硬件驱动 ,Manages the device and creates sound buffers
LPDIRECTSOUNDBUFFER8	g_lpDSBuf;//主缓存


// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名


//此处是dxsound代码
BOOL DSInit(HWND hWnd);									//dsound初始化
BOOL AnalysisWavFile(LPCTSTR sFilename);		//要解析的wav文件
BOOL MyPlaySound(LPCTSTR sFilename);			//实现playsound
void DsRelease();								//释放


// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PLAYSOUND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLAYSOUND));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAYSOUND));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PLAYSOUND);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		if (!DSInit(hWnd))
			SendMessage(hWnd,WM_DESTROY,NULL,NULL);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DsRelease();
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		MyPlaySound(L"Sound_Q.wav");
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL DSInit(HWND hWnd)								//dsound初始化
{
	if (DirectSoundCreate8(NULL, &g_lpDS, NULL) != DS_OK)
		return FALSE;
	if (g_lpDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL) != DS_OK)
		return FALSE;
	return TRUE;

}
BOOL AnalysisWavFile(LPCTSTR sFilename)		//要解析的wav文件
{
	long fileLen;
	FILE *fp = _wfopen(sFilename, L"rb");	// 二进制打开
	fseek(fp, 0, SEEK_END);
	fileLen = ftell(fp);
	rewind(fp);
	// fread 是二进制读取，而 fscanf 是文本读取
	fread(&g_wh, sizeof(WavHeader), 1, fp);
	// 不可以用 strcmp，因为 strcmp 还要比较 '\0'
	if (memcmp(g_wh.szRIFF, "RIFF", TAG_SIZE)
		|| memcmp(g_wh.szType, "WAVE", TAG_SIZE)
		|| memcmp(g_wh.szFmt, "fmt ", TAG_SIZE)
		|| memcmp(g_wh.szData, "data", TAG_SIZE)
		|| g_wh.dwRiffSize != fileLen - TAG_SIZE * 2
		|| g_wh.dwFmtSize != WAV_FMT_SIZE
		|| g_wh.dwDataSize != fileLen - sizeof(g_wh))
	{
		fclose(fp);
		return FALSE;
	}
	fclose(fp);
	return TRUE;
}
BOOL MyPlaySound(LPCTSTR sFilename)						//实现playsound
{
	if (AnalysisWavFile(sFilename))
	{
		//内存描述！
		FILE *fp;
		BYTE *pContent;
		WAVEFORMATEX wfx;
		LPVOID pDSLockedBuffer ;
		DWORD dwDSLockedBufferSize;
		LPDIRECTSOUNDBUFFER lpDSBuf;					//这里是主缓存

		g_dsbd.dwSize = sizeof(DSBUFFERDESC);			//结构体大小
		g_dsbd.dwBufferBytes = g_wh.dwDataSize;			//要拷贝的内存
		g_dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;//混音效果
		wfx.cbSize = 0;
		wfx.nAvgBytesPerSec = g_wh.dwAvgBytesPerSec;
		wfx.nBlockAlign = g_wh.wBlockAlign;
		wfx.nChannels = g_wh.wChannels;
		wfx.nSamplesPerSec = g_wh.dwSamplesPerSec;
		wfx.wBitsPerSample = g_wh.wBitsPerSample;
		wfx.wFormatTag = g_wh.wFmtTag;
		g_dsbd.lpwfxFormat = &wfx;						//内存格式描述

		//创建主缓存↓
		if (g_lpDS->CreateSoundBuffer(&g_dsbd, &lpDSBuf, NULL) != DS_OK)
			return FALSE;
		//com创建辅助缓存
		if (lpDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&g_lpDSBuf) != DS_OK)
			return FALSE;
		fp = _wfopen(sFilename, L"rb");
		fseek(fp, sizeof(WavHeader),  SEEK_SET);//跳过头文件，来到播放的声音文件这里
		pContent = new BYTE[g_dsbd.dwBufferBytes];//锁住,要播放的内存
		if (!pContent)
			return FALSE;
		fread(pContent, sizeof(BYTE), g_dsbd.dwBufferBytes, fp);
		//拷贝到辅助缓存中
		if (g_lpDSBuf->Lock(0, g_dsbd.dwBufferBytes, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0) == DSBSTATUS_BUFFERLOST)
		{
			g_lpDSBuf->Restore();
			g_lpDSBuf->Lock(0, g_dsbd.dwBufferBytes, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0);
		}
		memcpy(pDSLockedBuffer, pContent, dwDSLockedBufferSize);
		delete pContent;
		if (g_lpDSBuf->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0) == DSBSTATUS_BUFFERLOST)
		{
			g_lpDSBuf->Restore();
			g_lpDSBuf->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);
		}
		g_lpDSBuf->Play(0, 0, 0);
		return TRUE;
	}
	return FALSE;
}
void DsRelease()										//释放
{
	g_lpDSBuf->Release();
	g_lpDS->Release();
}
