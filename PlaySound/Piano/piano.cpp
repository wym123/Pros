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


//绑定具体辅助缓存的结构体，比如某一个辅助缓存
typedef struct tagNote						//音符文件，do，re，mi！
{
	WavHeader wavHeader;					//所有的音符都有一个文件头
	LPBYTE buf;
}Note;

DSBUFFERDESC g_dsbd;						//内存描述符
Note g_note[ALPHABET_LIST];					//要播放的A~~Z个音符
LPDIRECTSOUND8 g_lpDS;						//DirectSound设备
LPDIRECTSOUNDBUFFER8 g_lpDSBuf[DSBUF_NUM];	//硬件的辅助缓存buf 64个
int g_nCnt;									//计数器

BOOL LoadNotes()
{
	int i;
	WCHAR sFilename[FILE_NAME_LEN];
	long fileLen;
	FILE *fp;
	//	LPBYTE pContent;

	for (i = 0; i < ALPHABET_LIST; i++)
	{
		//解析wav文件
		wsprintf(sFilename, L"res\\Sound_%c.wav", L'A' + i);
		fp = _wfopen(sFilename, L"rb");

		fseek(fp, 0, SEEK_END);
		fileLen = ftell(fp);									//算出文件长度↑↓共三行
		rewind(fp);

		// fread 是二进制读取，而 fscanf 是文本读取
		fread(&g_note[i].wavHeader, sizeof(WavHeader), 1, fp);
		g_note[i].buf = new BYTE[g_note[i].wavHeader.dwDataSize];//创建缓存
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
	if (DirectSoundCreate8(NULL, &g_lpDS, NULL) != DS_OK)			//创建设备，主缓存
		//return FALSE;
	if (g_lpDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL) != DS_OK)	//设置协作等级
		//return FALSE;
	if (!LoadNotes())
		//return FALSE;
	return TRUE;
}



void PlayOneNote(BYTE ch)
{
	WAVEFORMATEX wfx;											//帮助主缓存赋值
	DWORD dwDSLockedBufferSize;
	LPVOID pDSLockedBuffer;
	LPDIRECTSOUNDBUFFER lpDSBuf;								//定义一个主缓存，由它来创建辅助缓存
	
	//↓这是用我们自己定义的宏文件头解析出来wav格式的文件，然后
	//来定义DS文件的格式要求，也就是说，自己造一个模具和DS文件要求对应上去
	wfx.cbSize = 0;												//wfx描述	
	memcpy(&wfx, &g_note[ch - 'A'].wavHeader.wFmtTag, sizeof(WAVEFORMATEX) - sizeof(wfx.cbSize));
	/*wfx.nAvgBytesPerSec = g_note[ch - 'A'].wavHeader.dwAvgBytesPerSec;
	wfx.nBlockAlign = g_note[ch - 'A'].wavHeader.wBlockAlign;
	wfx.nChannels = g_note[ch - 'A'].wavHeader.wChannels;
	wfx.nSamplesPerSec = g_note[ch - 'A'].wavHeader.dwSamplesPerSec;
	wfx.wBitsPerSample = g_note[ch - 'A'].wavHeader.wBitsPerSample;
	wfx.wFormatTag = g_note[ch - 'A'].wavHeader.wFmtTag;*/

	//g_dsbd内存描述
	g_dsbd.dwSize = sizeof(DSBUFFERDESC);						//结构体大小
	g_dsbd.dwBufferBytes = g_note[ch - 'A'].wavHeader.dwDataSize;			//要拷贝的内存
	g_dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;		//混音效果
	g_dsbd.lpwfxFormat = &wfx;

	//是否已经存在

	if (!g_lpDSBuf[g_nCnt])
	{
		//主缓存创建
		if (g_lpDS->CreateSoundBuffer(&g_dsbd,&lpDSBuf, NULL) != DS_OK)
		return ;
		//创建辅助缓存
		if (lpDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&g_lpDSBuf[g_nCnt]) != DS_OK)
		return ;
	}
	
	//锁内存
	if (g_lpDSBuf[g_nCnt]->Lock(0, g_dsbd.dwBufferBytes, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0) == DSBSTATUS_BUFFERLOST)
	{
		g_lpDSBuf[g_nCnt]->Restore();
		g_lpDSBuf[g_nCnt]->Lock(0, g_dsbd.dwBufferBytes, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0);
	}

	//拷贝内存
	memcpy(pDSLockedBuffer, g_note[ch - 'A'].buf, dwDSLockedBufferSize);
	//解锁内存
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