
// DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDemoDlg 对话框
const CString CDemoDlg::s_strTable = _T("0123456789ABCDEF");//查表数据，用来判断数据的内容
CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)//构造函数
	: CDialogEx(CDemoDlg::IDD, pParent)
	, m_strInputData(_T(""))//这就是我们添加的数据输入的value这个选项
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
	CDialogEx::DoDataExchange(pDX);//当数值和控件发生交互的时候，起到衔接的作用,就是界面和后台交互用
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


// CDemoDlg 消息处理程序

BOOL CDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDemoDlg::CheckValue()//******NO.1先检查数据，整个操作的第一步！！！！！
{
	int i, len;
	double fRadix;

	UpdateData(TRUE);//获取数据
	if (m_nInputRadix < 2 || m_nInputRadix >16 || m_nOutputRadix < 2 || m_nOutputRadix >16)
	{
		MessageBox(_T("输入输出进制必须在2到16范围内"));

		return FALSE;
	}
	i = 0;
	m_nInteger = 0;
	fRadix = static_cast<float>(1.0 / m_nInputRadix);
	len = m_strInputData.GetLength();
	m_bIsNegative = FALSE;
	if (m_strInputData[i] == _T('+') || m_strInputData[i] == _T('-'))//判断是否含有正负号
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
		//上一句告诉我们将整数部分的字符串转化为了int类型，整数的绝对值解决了
		i++;
	}

	m_bHasDot = FALSE;
	m_fFraction = 0.0f;
	if (i < len)	//i<len就退出了，也就是说字符数据里面出现了小数点，下面就解决小数部分
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
				//上一句告诉我们将整数部分的字符串转化为了int类型，小数部分解决了
				i++;
			}
			if (i < len)
			{
				MessageBox(_T("输入数据非法！"));
					return FALSE;
			}
		}
		else
		{
			MessageBox(_T("输入数据非法！"));
				return FALSE;
		}
	}
	return TRUE;
}

CString CDemoDlg::IntegerConvertToRadix(int nRadix)//NO。2转化整数部分
{
	int nInteger = m_nInteger;//防止修改本来的值，所以采用副本，这样的话2进制转了，8进制还能接着用，不然没法转了
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
CString CDemoDlg::FractionConvertToRadix(int nRadix)//NO3小数部分
{
	int nInteger, i;
	CString strTemp;					//临时变量来给数组做衔接用
	double fFraction = m_fFraction;		//也是副本，
	CString strFraction = _T(".");		//用它来返回小数部分的数组

	if (!m_bHasDot)
		return _T("");
	for (i = 0; i < 6; i++)				//最多保存6位小数！！！！！！
	{
		nInteger = static_cast<int>(fFraction * nRadix);//static_cast<int> C++的强制转换，取整数
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
	LPBYTE p = nullptr;//LPBYTE 为 unsigned char*;;p就是个指针
	float fNum = m_nInteger + m_fFraction;//存放整数临时变量+存放小数临时变量
	if (m_bIsNegative)
		fNum = -fNum;
	CString str = _T("小数部分需要单独表示！");
	m_strOrigin = str;
	m_strOpp = str;
	m_strCom = str;
	m_strShift = str;
	m_strFraction = _T("");
	p = reinterpret_cast<BYTE*>(&fNum);//reinterpret_cast是C++里的强制类型转换符。p指针指向4字节的float类型的首地址
	//p[0]指向最低位，p[3]指向最高位
	for (i = sizeof(float) - 1; i >= 0; i--)//把四字节取出来，一字节一字节的读出来
	{
		BYTE tmp = p[i];
		for (j = 0; j < 8; j++)
		{
			strTemp.Format(_T("%d"), (tmp & 0x80)>>7);
			//小段存储：987654321，存的时候是123456789，从后面读进去

			m_strFraction = m_strFraction + strTemp;

			tmp = tmp << 1;//左移

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
		if (m_strOpp[i] != _T('1'))		//这一部分太经典了，去反码加一要考虑进率，我们先反过来算
		{								//如果第31位不是1，那太好了，直接最后补一个1，跳出while循环
			m_strCom = m_strCom + _T("1");//把后面的补码抄上去，最后翻转就可以了
			break;						
		}									
		m_strCom = m_strCom + _T("0");//而如果是第31位是1，那么补码第31位就是0，
										//往前倒一位，看看这一位是不是1，如果不是1直接补码变成1跳出循环		
		i--;						//如果是1，还是补上一个0，再倒下一位，什么时候出来呢？这一位不为1，让这一位变成1，跳出来，
		//去下面这个while里，把剩下的（--i）位的反码抄进补码里面
	}
	while (--i >= 0)
		m_strCom = m_strCom + m_strOpp[i];
	m_strCom.MakeReverse();//最后翻转

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
	// TODO:  在此添加控件通知处理程序代码
	if (!CheckValue())
		return;
	CString strXRadix;//这个是用来改变 “X进制”这行字里面的X这个字
	strXRadix.Format(_T("%d进制"), m_nOutputRadix);
	CString strInteger, strFraction;
	UpdateMemberString(m_strBinary, 2);
	UpdateMemberString(m_strOctal, 8);
	UpdateMemberString(m_strDecimal, 10);
	UpdateMemberString(m_strHex, 16);
	UpdateMemberString(m_strXRadix, m_nOutputRadix);
	GetDlgItem(IDC_STATIC_RADICX)->SetWindowText(strXRadix);
	UpdateData(FALSE);//false 表示把值刷上去，刷到窗口上
}


void CDemoDlg::OnBnClickedBtnCalc()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!CheckValue())
		return;

	if (m_bHasDot)
	{
		CalcFraction();
	}
	else
	{
		m_strFraction = _T("整数用补码表示！");//也就是说，只有整数有源码补码反码之类的，小数另算的
		CalcOrigin();
		CalcOpp();
		CalcCom();
		CalcShift();
		UpdateData(FALSE);
	}
}


void CDemoDlg::OnBnClickedBtnRestore()
{
	// TODO:  在此添加控件通知处理程序代码

	//项目人工添加几个别的变量,此时赋值为零
	m_strTemp = _T("");		//存放临时变量
	m_nInteger = 0;			//存放整数变量
	m_fFraction = 0.0f;		//存放小数临时变量
	m_bIsNegative = FALSE;		//判断符号位的变量
	m_bHasDot = FALSE;


	//对控件的处理
	GetDlgItem(IDC_STATIC_RADICX)->SetWindowText(_T("X 进制"));
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
	
	UpdateData(FALSE);//显示
}


void CDemoDlg::OnEnChangeEditOrgnal()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
