
// DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

 BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoDlg �Ի���
const CString CDemoDlg::s_strTable = _T("0123456789ABCDEF");//������ݣ������ж����ݵ�����
CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)//���캯��
	: CDialogEx(CDemoDlg::IDD, pParent)
	, m_strInputData(_T(""))//�����������ӵ����������value���ѡ��
	, m_nInputRadix(10)
	, m_nOutputRadix(2)
	, m_strBinary(_T(""))
	, m_strOctal(_T(""))
	, m_strDecimal(_T(""))
	, m_strHex(_T(""))
	, m_strXRadix(_T(""))
	, m_strOrigin(_T(""))
	, m_strOpp(_T(""))
	, m_strCom(_T(""))
	, m_strShift(_T(""))
	, m_strFraction(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);//����ֵ�Ϳؼ�����������ʱ�����νӵ�����,���ǽ���ͺ�̨������
	DDX_Text(pDX, IDC_EDIT_INPUTDATA, m_strInputData);

	DDX_Text(pDX, IDC_EDIT_INPUTRADIX, m_nInputRadix);
	DDX_Text(pDX, IDC_EDIT_OUTPUTRADIX, m_nOutputRadix);
	DDX_Text(pDX, IDC_EDIT_BINARY, m_strBinary);
	DDX_Text(pDX, IDC_EDIT_OCTAL, m_strOctal);
	DDX_Text(pDX, IDC_EDIT_DECIMAL, m_strDecimal);
	DDX_Text(pDX, IDC_EDIT_HEX, m_strHex);
	DDX_Text(pDX, IDC_EDIT_XRADIX, m_strXRadix);
	DDX_Text(pDX, IDC_EDIT_ORGNAL, m_strOrigin);
	DDX_Text(pDX, IDC_EDIT_OPP, m_strOpp);
	DDX_Text(pDX, IDC_EDIT_COMP, m_strCom);
	DDX_Text(pDX, IDC_EDIT_SHIFT, m_strShift);
	DDX_Text(pDX, IDC_EDIT_FRACTION, m_strFraction);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BTN_TRANSFORM, &CDemoDlg::OnBnClickedBtnTransform)
	ON_BN_CLICKED(IDC_BTN_CALC, &CDemoDlg::OnBnClickedBtnCalc)
	ON_BN_CLICKED(IDC_BTN_RESTORE, &CDemoDlg::OnBnClickedBtnRestore)
	ON_EN_CHANGE(IDC_EDIT_ORGNAL, &CDemoDlg::OnEnChangeEditOrgnal)
END_MESSAGE_MAP()


// CDemoDlg ��Ϣ�������

BOOL CDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDemoDlg::CheckValue()//******NO.1�ȼ�����ݣ����������ĵ�һ������������
{
	int i, len;
	double fRadix;

	UpdateData(TRUE);//��ȡ����
	if (m_nInputRadix < 2 || m_nInputRadix >16 || m_nOutputRadix < 2 || m_nOutputRadix >16)
	{
		MessageBox(_T("����������Ʊ�����2��16��Χ��"));

		return FALSE;
	}
	i = 0;
	m_nInteger = 0;
	fRadix = static_cast<float>(1.0 / m_nInputRadix);
	len = m_strInputData.GetLength();
	m_bIsNegative = FALSE;
	if (m_strInputData[i] == _T('+') || m_strInputData[i] == _T('-'))//�ж��Ƿ���������
	{
		if (m_strInputData[i] == _T('-'))
			m_bIsNegative = TRUE;
		i++;
	}
	while (i < len)
	{
		if (m_strInputData[i] < s_strTable[0] || m_strInputData[i] > s_strTable[m_nInputRadix - 1])
			break;
		m_nInteger = (m_nInteger*m_nInputRadix + (m_strInputData[i] <= _T('9') ? m_strInputData[i] - _T('0') : m_strInputData[i] - _T('A') + 10));
		//��һ��������ǽ��������ֵ��ַ���ת��Ϊ��int���ͣ������ľ���ֵ�����
		i++;
	}

	m_bHasDot = FALSE;
	m_fFraction = 0.0f;
	if (i < len)	//i<len���˳��ˣ�Ҳ����˵�ַ��������������С���㣬����ͽ��С������
	{
		if (m_strInputData[i] == _T('.'))
		{
			i++;
			m_bHasDot = TRUE;
			while (i < len)
			{
				if (m_strInputData[i] < s_strTable[0] || m_strInputData[i] > s_strTable[m_nInputRadix - 1])
					break;
				m_fFraction = static_cast<float>(m_fFraction + (m_strInputData[i] <= _T('9') ? m_strInputData[i] - _T('0') : m_strInputData[i] - _T('A') + 10)*fRadix);
				fRadix = fRadix / m_nInputRadix;
				//��һ��������ǽ��������ֵ��ַ���ת��Ϊ��int���ͣ�С�����ֽ����
				i++;
			}
			if (i < len)
			{
				MessageBox(_T("�������ݷǷ���"));
					return FALSE;
			}
		}
		else
		{
			MessageBox(_T("�������ݷǷ���"));
				return FALSE;
		}
	}
	return TRUE;
}

CString CDemoDlg::IntegerConvertToRadix(int nRadix)//NO��2ת����������
{
	int nInteger = m_nInteger;//��ֹ�޸ı�����ֵ�����Բ��ø����������Ļ�2����ת�ˣ�8���ƻ��ܽ����ã���Ȼû��ת��
	CString strInterger = _T("");
	if (!nInteger)
		return _T("0");
	while (nInteger)
	{
		strInterger += s_strTable[nInteger % nRadix];
		nInteger = nInteger / nRadix;
	}
	strInterger.MakeReverse();

		return strInterger;
}
CString CDemoDlg::FractionConvertToRadix(int nRadix)//NO3С������
{
	int nInteger, i;
	CString strTemp;					//��ʱ���������������ν���
	double fFraction = m_fFraction;		//Ҳ�Ǹ�����
	CString strFraction = _T(".");		//����������С�����ֵ�����

	if (!m_bHasDot)
		return _T("");
	for (i = 0; i < 6; i++)				//��ౣ��6λС��������������
	{
		nInteger = static_cast<int>(fFraction * nRadix);//static_cast<int> C++��ǿ��ת����ȡ����
		strTemp.Format(_T("%d"), nInteger);//
		strFraction = strFraction + strTemp;
		fFraction = fFraction * nRadix - nInteger;
	}
	return strFraction;
}
CString CDemoDlg::Combination(CString strInteger, CString strFraction)
{
	CString strAnswer = _T("");
	if (m_bIsNegative)
		strAnswer = strAnswer + _T("-");
	else
		strAnswer = strAnswer + _T("+");
	strAnswer = strAnswer + strInteger + strFraction;
	return strAnswer;
}

void CDemoDlg::UpdateMemberString(CString& str,int nRadix)
{
	CString strInteger, strFraction;
	strInteger = IntegerConvertToRadix(nRadix);
	strFraction = FractionConvertToRadix(nRadix);
	str = Combination(strInteger, strFraction);
}

void CDemoDlg::CalcFraction()
{
	int i,j;
	CString strTemp;
	LPBYTE p = nullptr;//LPBYTE Ϊ unsigned char*;;p���Ǹ�ָ��
	float fNum = m_nInteger + m_fFraction;//���������ʱ����+���С����ʱ����
	if (m_bIsNegative)
		fNum = -fNum;
	CString str = _T("С��������Ҫ������ʾ��");
	m_strOrigin = str;
	m_strOpp = str;
	m_strCom = str;
	m_strShift = str;
	m_strFraction = _T("");
	p = reinterpret_cast<BYTE*>(&fNum);//reinterpret_cast��C++���ǿ������ת������pָ��ָ��4�ֽڵ�float���͵��׵�ַ
	//p[0]ָ�����λ��p[3]ָ�����λ
	for (i = sizeof(float) - 1; i >= 0; i--)//�����ֽ�ȡ������һ�ֽ�һ�ֽڵĶ�����
	{
		BYTE tmp = p[i];
		for (j = 0; j < 8; j++)
		{
			strTemp.Format(_T("%d"), (tmp & 0x80)>>7);
			//С�δ洢��987654321�����ʱ����123456789���Ӻ������ȥ

			m_strFraction = m_strFraction + strTemp;

			tmp = tmp << 1;//����

		}
	}
	UpdateData(FALSE);
}

void CDemoDlg::CalcOrigin()
{
	int i, len;
	m_strTemp = IntegerConvertToRadix(2);
	
	if (m_bIsNegative)
	{
		m_strOrigin = _T("1");
	}
	else
	{
		m_strOrigin = _T("0");
	}
	len = 1 + m_strTemp.GetLength();
	for (i = 0; i < 32 - len; i++)
		m_strOrigin = m_strOrigin + _T("0");

	m_strOrigin = m_strOrigin + m_strTemp;

}
void CDemoDlg::CalcOpp()
{
	int i, len;
	m_strOpp = m_strOrigin[0];
	for (i = 1; i < 32;i++)
	{
		m_strOpp = m_strOpp + (m_strOrigin[i] == _T('0') ? _T("1") : _T("0"));
	}
}
void CDemoDlg::CalcCom()
{
	bool bIsInc = true;
	int i = m_strOpp.GetLength() - 1;
	m_strCom = _T("");
	while (i >= 0)
	{
		if (m_strOpp[i] != _T('1'))		//��һ����̫�����ˣ�ȥ�����һҪ���ǽ��ʣ������ȷ�������
		{								//�����31λ����1����̫���ˣ�ֱ�����һ��1������whileѭ��
			m_strCom = m_strCom + _T("1");//�Ѻ���Ĳ��볭��ȥ�����ת�Ϳ�����
			break;						
		}									
		m_strCom = m_strCom + _T("0");//������ǵ�31λ��1����ô�����31λ����0��
										//��ǰ��һλ��������һλ�ǲ���1���������1ֱ�Ӳ�����1����ѭ��		
		i--;						//�����1�����ǲ���һ��0���ٵ���һλ��ʲôʱ������أ���һλ��Ϊ1������һλ���1����������
		//ȥ�������while���ʣ�µģ�--i��λ�ķ��볭����������
	}
	while (--i >= 0)
		m_strCom = m_strCom + m_strOpp[i];
	m_strCom.MakeReverse();//���ת

}
void CDemoDlg::CalcShift()
{
	int i, len = m_strCom.GetLength();
	m_strShift = (m_strCom[0] == _T('0') ? _T("1") : _T("0"));
	for (i = 1; i < len; i++)
		m_strShift = m_strShift + m_strCom[i];
}


void CDemoDlg::OnBnClickedBtnTransform()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!CheckValue())
		return;
	CString strXRadix;//����������ı� ��X���ơ������������X�����
	strXRadix.Format(_T("%d����"), m_nOutputRadix);
	CString strInteger, strFraction;
	UpdateMemberString(m_strBinary, 2);
	UpdateMemberString(m_strOctal, 8);
	UpdateMemberString(m_strDecimal, 10);
	UpdateMemberString(m_strHex, 16);
	UpdateMemberString(m_strXRadix, m_nOutputRadix);
	GetDlgItem(IDC_STATIC_RADICX)->SetWindowText(strXRadix);
	UpdateData(FALSE);//false ��ʾ��ֵˢ��ȥ��ˢ��������
}


void CDemoDlg::OnBnClickedBtnCalc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!CheckValue())
		return;

	if (m_bHasDot)
	{
		CalcFraction();
	}
	else
	{
		m_strFraction = _T("�����ò����ʾ��");//Ҳ����˵��ֻ��������Դ�벹�뷴��֮��ģ�С�������
		CalcOrigin();
		CalcOpp();
		CalcCom();
		CalcShift();
		UpdateData(FALSE);
	}
}


void CDemoDlg::OnBnClickedBtnRestore()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//��Ŀ�˹���Ӽ�����ı���,��ʱ��ֵΪ��
	m_strTemp = _T("");		//�����ʱ����
	m_nInteger = 0;			//�����������
	m_fFraction = 0.0f;		//���С����ʱ����
	m_bIsNegative = FALSE;		//�жϷ���λ�ı���
	m_bHasDot = FALSE;


	//�Կؼ��Ĵ���
	GetDlgItem(IDC_STATIC_RADICX)->SetWindowText(_T("X ����"));
	m_strInputData = _T("");
	m_nInputRadix = 10;
	m_nOutputRadix = 2;
	m_strBinary=_T("");
	m_strOctal=_T("");
	m_strDecimal=_T("");
	m_strHex=_T("");
	m_strXRadix=_T("");
	m_strOrigin=_T("");
	m_strOpp=_T("");
	m_strCom=_T("");
	m_strShift=_T("");
	m_strFraction=_T("");
	
	UpdateData(FALSE);//��ʾ
}


void CDemoDlg::OnEnChangeEditOrgnal()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
