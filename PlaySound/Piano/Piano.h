#pragma once

#ifdef _MSC_VER//如果是微软的编译器
#ifdef LIB_EXPORT
#define LIB __declspec(dllexport)
#else
#define LIB __declspec(dllimport)
#endif
#else
#define LIB
#endif // _MSC_VER//如果是微软的编译器

//以下函数都用来导出的函数，外部接口
//强制导出C接口，提高兼容性
#ifdef __cplusplus
extern "C"
{
#endif
	LIB BOOL DSInit(HWND hWnd);
	//BOOL LoadNotes(LPCTSTR sPath);这是个内部函数，不暴露出来
	LIB void PlayOneNote(BYTE ch);
	LIB void Stop();
	LIB void DsRelease();
#ifdef __cplusplus
};
#endif