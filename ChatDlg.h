#pragma once

#include "afxwin.h"

// ChatDlg 对话框

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChatDlg();

// 对话框数据
	enum { IDD = IDD_CHATDLG };
public:
	void UpdateText(CString& strText);  //更新聊天记录

// 实现
protected:
	BOOL WChar2MByte(LPCTSTR lpSrc, LPSTR lpDest, int nlen);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnSend();
	CString m_strSend;
	CString m_caption;//对话框标题设置
	char *touser;
	
};
