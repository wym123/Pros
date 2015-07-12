// DemoDlg.h : 头文件
//
#pragma once
// CDemoDlg 对话框
class CDemoDlg : public CDialogEx
{
// 构造
public:
	CDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()//****************************//我们添加事件的时候，影响这里
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_strInputData;
	
	int m_nInputRadix;
	int m_nOutputRadix;  
	CString m_strBinary;
	CString m_strOctal;
public:
	afx_msg void OnEnChangeEditBinary();
private:
	CString m_strDecimal;
	CString m_strHex;
	CString m_strXRadix;
	CString m_strOrigin;
	CString m_strOpp;
	CString m_strCom;
	CString m_strShift;
	CString m_strFraction;

	//项目人工添加几个别的变量
	CString m_strTemp;		//存放临时变量
	int m_nInteger;			//存放整数变量
	float m_fFraction;		//存放小数临时变量
	BOOL m_bIsNegative;		//判断符号位的变量
	BOOL m_bHasDot;			//判断小数点
	static const CString s_strTable;
public:
	BOOL CheckValue();							//判断数值是否合法
	CString IntegerConvertToRadix(int nRadix);	//整数部分的转化
	CString FractionConvertToRadix(int nRadix);	//小数部分转化
	CString Combination(CString strInteger, CString strFraction);	//小数和整数的糅合
	void UpdateMemberString(CString& str,int nRadix);
	void CalcOrigin();
	void CalcOpp();
	void CalcCom();
	void CalcShift();
	void CalcFraction();
	
public:
	afx_msg void OnBnClickedBtnTransform();
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnBnClickedBtnRestore();
	afx_msg void OnEnChangeEditOrgnal();
};
