#pragma once

#ifdef _MSC_VER//�����΢��ı�����
#ifdef LIB_EXPORT
#define LIB __declspec(dllexport)
#else
#define LIB __declspec(dllimport)
#endif
#else
#define LIB
#endif // _MSC_VER//�����΢��ı�����

//���º��������������ĺ������ⲿ�ӿ�
//ǿ�Ƶ���C�ӿڣ���߼�����
#ifdef __cplusplus
extern "C"
{
#endif
	LIB BOOL DSInit(HWND hWnd);
	//BOOL LoadNotes(LPCTSTR sPath);���Ǹ��ڲ�����������¶����
	LIB void PlayOneNote(BYTE ch);
	LIB void Stop();
	LIB void DsRelease();
#ifdef __cplusplus
};
#endif