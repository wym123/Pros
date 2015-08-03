//#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include <dsound.h>
#include <stdio.h>
#include "Piano.h"

#define TAG_SIZE 4
#define WAV_FMT_SIZE 16
#define ALPHABET_LIST 26
#define DSBUF_NUM 64
#define FILE_NAME_LEN 16


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


//�󶨾��帨������Ľṹ�壬����ĳһ����������
typedef struct tagNote						//�����ļ���do��re��mi��
{
	WavHeader wavHeader;					//���е���������һ���ļ�ͷ
	LPBYTE buf;
}Note;

DSBUFFERDESC g_dsbd;						//�ڴ�������
Note g_note[ALPHABET_LIST];					//Ҫ���ŵ�A~~Z������
LPDIRECTSOUND8 g_lpDS;						//DirectSound�豸
LPDIRECTSOUNDBUFFER8 g_lpDSBuf[DSBUF_NUM];	//Ӳ���ĸ�������buf 64��
int g_nCnt;									//������

BOOL LoadNotes()
{
	int i;
	WCHAR sFilename[FILE_NAME_LEN];
	long fileLen;
	FILE *fp;
	//	LPBYTE pContent;

	for (i = 0; i < ALPHABET_LIST; i++)
	{
		//����wav�ļ�
		wsprintf(sFilename, L"res\\Sound_%c.wav", L'A' + i);
		fp = _wfopen(sFilename, L"rb");

		fseek(fp, 0, SEEK_END);
		fileLen = ftell(fp);									//����ļ����ȡ���������
		rewind(fp);

		// fread �Ƕ����ƶ�ȡ���� fscanf ���ı���ȡ
		fread(&g_note[i].wavHeader, sizeof(WavHeader), 1, fp);
		g_note[i].buf = new BYTE[g_note[i].wavHeader.dwDataSize];//��������
		if (!g_note[i].buf)
		{
			fclose(fp);
			return FALSE;
		}
		fread(g_note[i].buf, sizeof(BYTE), g_note[i].wavHeader.dwDataSize, fp);
		fclose(fp);
	}
	return TRUE;
}

BOOL DSInit(HWND hWnd)
{
	if (DirectSoundCreate8(NULL, &g_lpDS, NULL) != DS_OK)			//�����豸��������
		//return FALSE;
	if (g_lpDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL) != DS_OK)	//����Э���ȼ�
		//return FALSE;
	if (!LoadNotes())
		//return FALSE;
	return TRUE;
}



void PlayOneNote(BYTE ch)
{
	WAVEFORMATEX wfx;											//���������渳ֵ
	DWORD dwDSLockedBufferSize;
	LPVOID pDSLockedBuffer;
	LPDIRECTSOUNDBUFFER lpDSBuf;								//����һ�������棬������������������
	
	//�������������Լ�����ĺ��ļ�ͷ��������wav��ʽ���ļ���Ȼ��
	//������DS�ļ��ĸ�ʽҪ��Ҳ����˵���Լ���һ��ģ�ߺ�DS�ļ�Ҫ���Ӧ��ȥ
	wfx.cbSize = 0;												//wfx����	
	memcpy(&wfx, &g_note[ch - 'A'].wavHeader.wFmtTag, sizeof(WAVEFORMATEX) - sizeof(wfx.cbSize));
	/*wfx.nAvgBytesPerSec = g_note[ch - 'A'].wavHeader.dwAvgBytesPerSec;
	wfx.nBlockAlign = g_note[ch - 'A'].wavHeader.wBlockAlign;
	wfx.nChannels = g_note[ch - 'A'].wavHeader.wChannels;
	wfx.nSamplesPerSec = g_note[ch - 'A'].wavHeader.dwSamplesPerSec;
	wfx.wBitsPerSample = g_note[ch - 'A'].wavHeader.wBitsPerSample;
	wfx.wFormatTag = g_note[ch - 'A'].wavHeader.wFmtTag;*/

	//g_dsbd�ڴ�����
	g_dsbd.dwSize = sizeof(DSBUFFERDESC);						//�ṹ���С
	g_dsbd.dwBufferBytes = g_note[ch - 'A'].wavHeader.dwDataSize;			//Ҫ�������ڴ�
	g_dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;		//����Ч��
	g_dsbd.lpwfxFormat = &wfx;

	//�Ƿ��Ѿ�����

	if (!g_lpDSBuf[g_nCnt])
	{
		//�����洴��
		if (g_lpDS->CreateSoundBuffer(&g_dsbd,&lpDSBuf, NULL) != DS_OK)
		return ;
		//������������
		if (lpDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&g_lpDSBuf[g_nCnt]) != DS_OK)
		return ;
	}
	
	//���ڴ�
	if (g_lpDSBuf[g_nCnt]->Lock(0, g_dsbd.dwBufferBytes, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0) == DSBSTATUS_BUFFERLOST)
	{
		g_lpDSBuf[g_nCnt]->Restore();
		g_lpDSBuf[g_nCnt]->Lock(0, g_dsbd.dwBufferBytes, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0);
	}

	//�����ڴ�
	memcpy(pDSLockedBuffer, g_note[ch - 'A'].buf, dwDSLockedBufferSize);
	//�����ڴ�
	if (g_lpDSBuf[g_nCnt]->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, NULL) == DSBSTATUS_BUFFERLOST)
	{
		g_lpDSBuf[g_nCnt]->Restore();
		g_lpDSBuf[g_nCnt]->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, NULL);
	}
	g_lpDSBuf[g_nCnt++]->Play(0, 0, 0);
	if (g_nCnt == DSBUF_NUM)
		g_nCnt = 0;
}
void Stop()
{
	int i;
	for (i = 0; i < DSBUF_NUM; i++)
	{
		if (g_lpDSBuf[i])
			g_lpDSBuf[i]->Release();
	}

}

void DsRelease()
{
	int i;
	for (i = 0; i < DSBUF_NUM; i++)
		g_lpDSBuf[i]->Release();
	for (i = 0; i < ALPHABET_LIST; i++)
		delete[] g_note[i].buf;
	g_lpDS->Release();
}