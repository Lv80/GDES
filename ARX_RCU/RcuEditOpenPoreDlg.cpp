// RcuEditClosePoreDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "RcuEditOpenPoreDlg.h"


IMPLEMENT_DYNAMIC(RcuEditOpenPoreDlg, RcuAcUiBaseDlg)

RcuEditOpenPoreDlg::RcuEditOpenPoreDlg(CWnd* pParent /*=NULL*/)
	: RcuAcUiBaseDlg(RcuEditOpenPoreDlg::IDD, pParent)
	, m_num(10)
	, m_gap(0.1)
	, m_radius(0)
{

}

RcuEditOpenPoreDlg::~RcuEditOpenPoreDlg()
{
}

void RcuEditOpenPoreDlg::DoDataExchange(CDataExchange* pDX)
{
	RcuAcUiBaseDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_num);
	DDX_Text(pDX, IDC_EDIT2, m_gap);
	DDX_Text(pDX, IDC_EDIT3, m_radius);
}


BEGIN_MESSAGE_MAP(RcuEditOpenPoreDlg, RcuAcUiBaseDlg)
	ON_BN_CLICKED(IDOK, &RcuEditOpenPoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RcuEditClosePoreDlg ��Ϣ�������

void RcuEditOpenPoreDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

BOOL RcuEditOpenPoreDlg::OnInitDialog()
{
	RcuAcUiBaseDlg::OnInitDialog();

	//�޸ı���
	if(!m_title.IsEmpty())
	{
		this->SetWindowText(m_title);
	}
	//�޸��곡��Ϣ
	this->SetDlgItemText(IDC_DRILL_SITE_TEXT, m_pos);

	//�������ݵ�����
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
