// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HelpDlg.h"


// HelpDlg �Ի���

IMPLEMENT_DYNAMIC(HelpDlg, PropertyData_DockBarChildDlg)

HelpDlg::HelpDlg(CWnd* pParent /*=NULL*/)
	: PropertyData_DockBarChildDlg(HelpDlg::IDD, pParent)
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, PropertyData_DockBarChildDlg)
END_MESSAGE_MAP()


// HelpDlg ��Ϣ�������
