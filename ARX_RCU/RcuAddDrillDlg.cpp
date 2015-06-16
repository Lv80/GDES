// RcuAddDrillDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RcuAddDrillDlg.h"


// RcuAddDrillDlg �Ի���

IMPLEMENT_DYNAMIC(RcuAddDrillDlg, RcuAcUiBaseDlg)

RcuAddDrillDlg::RcuAddDrillDlg(CWnd* pParent /*=NULL*/)
	: RcuAcUiBaseDlg(RcuAddDrillDlg::IDD, pParent)
	, m_name(_T(""))
	, m_leftOrRight(0)
	, m_width(0)
	, m_height(0)
	, m_dist(0)
	, m_index(0)
{

}

RcuAddDrillDlg::~RcuAddDrillDlg()
{
}

void RcuAddDrillDlg::DoDataExchange(CDataExchange* pDX)
{
	RcuAcUiBaseDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DRIL_NAME_EDIT, m_name);
	DDX_Text(pDX, IDC_DRILL_WIDTH_EDIT, m_width);
	DDX_Text(pDX, IDC_DRILL_HEIGHT_EDIT, m_height);
	DDX_Text(pDX, IDC_DRILL_DIS_EDIT, m_dist);
	DDX_Text(pDX, IDC_DRILL_INDEX_EDIT, m_index);
	DDX_Control(pDX, IDC_LOCA_COMBO, m_locaCombBox);
}


BEGIN_MESSAGE_MAP(RcuAddDrillDlg, RcuAcUiBaseDlg)
	ON_BN_CLICKED(IDOK, &RcuAddDrillDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RcuAddDrillDlg ��Ϣ�������

void RcuAddDrillDlg::OnBnClickedOk()
{
	UpdateData( TRUE );
	m_leftOrRight = m_locaCombBox.GetCurSel();
	OnOK();
}

void RcuAddDrillDlg::writeToDataLink( DrillSiteLink& ds_link )
{
	ds_link.m_name = m_name;
	ds_link.m_leftOrRight = m_leftOrRight;
	ds_link.m_dist = m_dist;
	ds_link.m_width = m_width;
	ds_link.m_height = m_height;
	ds_link.m_start = m_index;
}

BOOL RcuAddDrillDlg::OnInitDialog()
{
	RcuAcUiBaseDlg::OnInitDialog();
	m_locaCombBox.AddString(_T("����곡"));
	m_locaCombBox.AddString(_T("�Ұ��곡"));
	m_locaCombBox.SetCurSel(m_leftOrRight);
	UpdateData(FALSE);
	return TRUE; 
}