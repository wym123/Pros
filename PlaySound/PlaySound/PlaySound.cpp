// PlaySound.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PlaySound.h"
#include <mmsystem.h>
#include <dsound.h>			//	dxsoundͷ�ļ�


#define MAX_LOADSTRING 100
#define TAG_SIZE 4
#define WAV_FMT_SIZE 16

typedef struct tagWavHeader
{
	// RIFF ͷ
	char szRIFF[TAG_SIZE];			// ��R����I����F����F��
	DWORD dwRiffSize;				// RIFF ƫ��
	char szType[TAG_SIZE];			// ��W����A����V����E�� ��
	// fmt �ֶ�
	char szFmt[TAG_SIZE];			// ��f����m����t���� ��
	DWORD dwFmtSize;				// FMT ��С
	WORD wFmtTag;					// ��ʽ��ǩ
	WORD wChannels;					// ������Ŀ
	DWORD dwSamplesPerSec;			// �����ʱ�׼
	DWORD dwAvgBytesPerSec;			// ƽ��������
	WORD wBlockAlign;				// �ڴ��ֽڶ���
	WORD wBitsPerSample;			// ���β���λ��
	// data �ֶ�
	char szData[TAG_SIZE];			// 'd''a''t''a'
	DWORD dwDataSize;				// data ƫ��
}WavHeader;

//DXsound��ȫ�ֱ���
WavHeader g_wh;
DSBUFFERDESC g_dsbd;//�λ��棿
LPDIRECTSOUND8 g_lpDS;	//Ӳ������ ,Manages the device and creates sound buffers
LPDIRECTSOUNDBUFFER8	g_lpDSBuf;//������


// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������


//�˴���dxsound����
BOOL DSInit(HWND hWnd);									//dsound��ʼ��
BOOL AnalysisWavFile(LPCTSTR sFilename);		//Ҫ������wav�ļ�
BOOL MyPlaySound(LPCTSTR sFilename);			//ʵ��playsound
void DsRelease();								//�ͷ�


// �˴���ģ���а����ĺ�����ǰ������: 
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

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PLAYSOUND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLAYSOUND));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��: 
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
		// TODO:  �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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

BOOL DSInit(HWND hWnd)								//dsound��ʼ��
{
	if (DirectSoundCreate8(NULL, &g_lpDS, NULL) != DS_OK)
		return FALSE;
	if (g_lpDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL) != DS_OK)
		return FALSE;
	return TRUE;

}
BOOL AnalysisWavFile(LPCTSTR sFilename)		//Ҫ������wav�ļ�
{
	long fileLen;
	FILE *fp = _wfopen(sFilename, L"rb");	// �����ƴ�
	fseek(fp, 0, SEEK_END);
	fileLen = ftell(fp);
	rewind(fp);
	// fread �Ƕ����ƶ�ȡ���� fscanf ���ı���ȡ
	fread(&g_wh, sizeof(WavHeader), 1, fp);
	// �������� strcmp����Ϊ strcmp ��Ҫ�Ƚ� '\0'
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
BOOL MyPlaySound(LPCTSTR sFilename)						//ʵ��playsound
{
	if (AnalysisWavFile(sFilename))
	{
		//�ڴ�������
		FILE *fp;
		BYTE *pContent;
		WAVEFORMATEX wfx;
		LPVOID pDSLockedBuffer ;
		DWORD dwDSLockedBufferSize;
		LPDIRECTSOUNDBUFFER lpDSBuf;					//������������

		g_dsbd.dwSize = sizeof(DSBUFFERDESC);			//�ṹ���С
		g_dsbd.dwBufferBytes = g_wh.dwDataSize;			//Ҫ�������ڴ�
		g_dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;//����Ч��
		wfx.cbSize = 0;
		wfx.nAvgBytesPerSec = g_wh.dwAvgBytesPerSec;
		wfx.nBlockAlign = g_wh.wBlockAlign;
		wfx.nChannels = g_wh.wChannels;
		wfx.nSamplesPerSec = g_wh.dwSamplesPerSec;
		wfx.wBitsPerSample = g_wh.wBitsPerSample;
		wfx.wFormatTag = g_wh.wFmtTag;
		g_dsbd.lpwfxFormat = &wfx;						//�ڴ��ʽ����

		//�����������
		if (g_lpDS->CreateSoundBuffer(&g_dsbd, &lpDSBuf, NULL) != DS_OK)
			return FALSE;
		//com������������
		if (lpDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&g_lpDSBuf) != DS_OK)
			return FALSE;
		fp = _wfopen(sFilename, L"rb");
		fseek(fp, sizeof(WavHeader),  SEEK_SET);//����ͷ�ļ����������ŵ������ļ�����
		pContent = new BYTE[g_dsbd.dwBufferBytes];//��ס,Ҫ���ŵ��ڴ�
		if (!pContent)
			return FALSE;
		fread(pContent, sizeof(BYTE), g_dsbd.dwBufferBytes, fp);
		//����������������
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
void DsRelease()										//�ͷ�
{
	g_lpDSBuf->Release();
	g_lpDS->Release();
}
