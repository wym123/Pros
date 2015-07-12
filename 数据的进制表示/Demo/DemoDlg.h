// DemoDlg.h : ͷ�ļ�
//
#pragma once
// CDemoDlg �Ի���
class CDemoDlg : public CDialogEx
{
// ����
public:
	CDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()//****************************//��������¼���ʱ��Ӱ������
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

	//��Ŀ�˹���Ӽ�����ı���
	CString m_strTemp;		//�����ʱ����
	int m_nInteger;			//�����������
	float m_fFraction;		//���С����ʱ����
	BOOL m_bIsNegative;		//�жϷ���λ�ı���
	BOOL m_bHasDot;			//�ж�С����
	static const CString s_strTable;
public:
	BOOL CheckValue();							//�ж���ֵ�Ƿ�Ϸ�
	CString IntegerConvertToRadix(int nRadix);	//�������ֵ�ת��
	CString FractionConvertToRadix(int nRadix);	//С������ת��
	CString Combination(CString strInteger, CString strFraction);	//С�����������ۺ�
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
