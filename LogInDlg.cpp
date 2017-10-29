// LogInDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "LogInDlg.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "SessionSocket.h"



// LogInDlg 对话框

IMPLEMENT_DYNAMIC(CLogInDlg, CDialogEx)

CLogInDlg::CLogInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_LOGIN, pParent)
	, m_strUser(_T(""))
{
	//初始化IP地址
	//DWORD 就是unSigned long
	m_dwIP = ntohl(inet_addr("192.168.11.1"));
}

CLogInDlg::~CLogInDlg()
{
}

void CLogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ET_NAME, m_strUser);
}

BEGIN_MESSAGE_MAP(CLogInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOGOIN, &CLogInDlg::OnBnClickedBtnLogoin)
	ON_BN_CLICKED(IDC_BTN_REGIST, &CLogInDlg::to_Regist)
END_MESSAGE_MAP()


void CLogInDlg::OnBnClickedBtnLogoin()
{
	//登录	
	UpdateData();
	if (m_strUser.IsEmpty())
	{
		AfxMessageBox(_T("用户名不能为空！"));
		return;
	}

	if (m_dwIP == 0)
	{
		AfxMessageBox(_T("无效IP地址"));
		return;
	}

	CSessionSocket* pSock = theApp.GetMainSocket();
	IN_ADDR addr;
	addr.S_un.S_addr = htonl(m_dwIP);
	//inet_ntoa返回一个char *,而这个char *的空间是在inet_ntoa里面静态分配
	CString strIP(inet_ntoa(addr));
	//开始只是创建了，并没有连接，这里连接socket，这个5050端口要和服务端监听的端口一直，否则监听不到的。
	CString ip = _T("192.168.11.1");
	pSock->Connect(ip, 5050);

	CString Cm_strUser = m_strUser;
	char from_user[20];
	memset(from_user, 0, sizeof(from_user));
	WideCharToMultiByte(CP_OEMCP, 0, (LPCTSTR)m_strUser, -1, from_user, 260, 0, false);
	//发送
	pSock->m_strUserName = m_strUser;  //将用户名字传递过去
	char* pBuff = new char[m_strUser.GetLength() + 1];
	memset(pBuff, 0, m_strUser.GetLength());  //开辟一个，存储用户名的内存空间
	if (WChar2MByte(m_strUser.GetBuffer(0), pBuff, m_strUser.GetLength() + 1))
		pSock->LogoIn(pBuff, m_strUser.GetLength() + 1, from_user);  //头部空间，和头部长度
	delete pBuff;
	CDialogEx::OnOK();
}

BOOL CLogInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(0);
	((CEdit*)GetDlgItem(IDC_ET_PSW))->SetWindowTextW(_T(""));
	return TRUE;
}

BOOL CLogInDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if (n<nlen)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}


void CLogInDlg::to_Regist()
{
	/*registDlg = new CRegisterDlg();
	registDlg->Create(IDD_REGISTERDLG);
	registDlg->ShowWindow(SW_SHOW);*/
	registDlg = new CRegisterDlg();
	INT_PTR rsp = registDlg->DoModal();
	if (rsp == IDCANCEL) {
		delete registDlg;
	}
	else {
		delete registDlg;
	}
}