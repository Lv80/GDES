// RcuDesignDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RcuDesignDlg.h"


// RcuDesignDlg �Ի���

IMPLEMENT_DYNAMIC(RcuDesignDlg, CAcUiDialog)

RcuDesignDlg::RcuDesignDlg(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(RcuDesignDlg::IDD, pParent)
{

}

RcuDesignDlg::~RcuDesignDlg()
{
}

void RcuDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_rcuList);
}


BEGIN_MESSAGE_MAP(RcuDesignDlg, CAcUiDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &RcuDesignDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &RcuDesignDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &RcuDesignDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &RcuDesignDlg::OnBnClickedButton4)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &RcuDesignDlg::OnHdnItemdblclickList1)
END_MESSAGE_MAP()

BOOL RcuDesignDlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// RcuDesignDlg ��Ϣ�������

void RcuDesignDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RcuDesignDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RcuDesignDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RcuDesignDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RcuDesignDlg::OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

