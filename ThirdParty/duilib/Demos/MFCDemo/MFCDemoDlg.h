// MFCDemoDlg.h : ͷ�ļ�
//

#pragma once

class ComputerExamineUI : public CContainerUI
{
public:
	ComputerExamineUI(CPaintManagerUI& paintManager)
	{
		CDialogBuilder builder;
		CContainerUI* pComputerExamine = static_cast<CContainerUI*>(builder.Create(_T("ComputerExamine.xml"), (UINT)0, 0, &paintManager));
		if( pComputerExamine ) {
			this->Add(pComputerExamine);
		}
		else {
			this->RemoveAll();
		}
	}
};

class CDialogUI:public WindowImplBase
{
public:
	CDialogUI(){};
	~CDialogUI(){};
	LPCTSTR GetWindowClassName() const { return _T("UIDialog"); };
	UINT GetClassStyle() const { return CS_DBLCLKS; };
	virtual CDuiString GetSkinFile() { return _T("skin.xml"); }
	virtual CDuiString GetSkinFolder() { return _T("../skin/360SafeRes"); }

	CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		if( _tcscmp(pstrClass, _T("ComputerExamine")) == 0 ) return new ComputerExamineUI(m_PaintManager);
		return NULL;
	}
	//����ؼ���Ϣ
	void Notify(TNotifyUI& msg)
	{
		if( msg.sType == _T("click") ) {
			if( msg.pSender->GetName() == _T("closebtn") ) {
				PostQuitMessage(0);
				return; 
			}
			else if( msg.pSender->GetName() == _T("minbtn") ) { 
				SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
			else if( msg.pSender->GetName() == _T("maxbtn") ) { 
				SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
			else if( msg.pSender->GetName() == _T("restorebtn") ) { 
				SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
		}
		else if(msg.sType==_T("setfocus"))
		{
			CDuiString name = msg.pSender->GetName();
			CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("switch")));
			if(name==_T("examine"))
				pControl->SelectItem(0);
			else if(name==_T("trojan"))
				pControl->SelectItem(1);
			else if(name==_T("plugins"))
				pControl->SelectItem(2);
			else if(name==_T("vulnerability"))
				pControl->SelectItem(3);
			else if(name==_T("rubbish"))
				pControl->SelectItem(4);
			else if(name==_T("cleanup"))
				pControl->SelectItem(5);
			else if(name==_T("fix"))
				pControl->SelectItem(6);
			else if(name==_T("tool"))
				pControl->SelectItem(7);
		}
	}
};

// CMFCDemoDlg �Ի���
class CMFCDemoDlg : public CDialog
{
// ����
public:
	CMFCDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CDialogUI m_dlgWnd;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
