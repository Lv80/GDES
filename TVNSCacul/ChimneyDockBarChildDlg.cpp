#include "stdafx.h"
#include "ChimneyDockBarChildDlg.h"

#include "../MineGE/ConstData.h"
#include "../MineGE/HelperClass.h"
#include "../ArxHelper/HelperClass.h"

extern CString ReadAlpha(CString chimType, CString diam);
extern CString ReadIntStringDatas(int intData,CString typeName);
extern int ReadStringIntDatas(CString strData,CString typeName);

IMPLEMENT_DYNAMIC(ChimneyDockBarChildDlg, PropertyData_DockBarChildDlg)

ChimneyDockBarChildDlg::ChimneyDockBarChildDlg(CWnd* pParent /*=NULL*/)
	: PropertyData_DockBarChildDlg(ChimneyDockBarChildDlg::IDD, pParent)
	, m_name(_T(""))
	, m_hmWindage(_T(""))
{

}

ChimneyDockBarChildDlg::~ChimneyDockBarChildDlg()
{
}

void ChimneyDockBarChildDlg::DoDataExchange(CDataExchange* pDX)
{
	PropertyData_DockBarChildDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHINMEY_NAME_EDIT, m_name);
	DDX_Text(pDX, IDC_CHIMNEY_LENTH_EDIT, m_lenth);
	DDX_Text(pDX, IDC_CHIMNEY_DIAMETER_EDIT, m_diameter);
	DDX_Text(pDX, IDC_CHIMNEY_BEND_EDIT, m_bend);
	DDX_Text(pDX, IDC_CHIMNEY_JOINT_EDIT, m_joints);
	DDX_Text(pDX, IDC_CHIMNEY_FRICTION_EDIT, m_friction);
	DDX_Control(pDX, IDC_CHIMNEY_MATERIAL_COMBO, m_material);
	DDX_Text(pDX, IDC_CHIMNEY_HM_WINDAGE_EDIT, m_hmWindage);
}


BEGIN_MESSAGE_MAP(ChimneyDockBarChildDlg, PropertyData_DockBarChildDlg)
	ON_EN_KILLFOCUS(IDC_CHIMNEY_DIAMETER_EDIT, &ChimneyDockBarChildDlg::OnEnKillfocusChimneyDiameterEdit)
	ON_CBN_SELCHANGE(IDC_CHIMNEY_MATERIAL_COMBO, &ChimneyDockBarChildDlg::OnCbnSelchangeChimneyMaterialCombo)
	ON_EN_KILLFOCUS(IDC_CHIMNEY_FRICTION_EDIT, &ChimneyDockBarChildDlg::OnEnKillfocusChimneyFrictionEdit)
	ON_EN_SETFOCUS(IDC_CHIMNEY_FRICTION_EDIT, &ChimneyDockBarChildDlg::OnEnSetfocusChimneyFrictionEdit)
END_MESSAGE_MAP()

BOOL ChimneyDockBarChildDlg::OnInitDialog()
{
	PropertyData_DockBarChildDlg::OnInitDialog();

	m_material.AddString( _T( "������Ͳ" ) );
	m_material.AddString( _T( "������Ͳ" ) );
	
	return TRUE;
}

void ChimneyDockBarChildDlg::readPropertyData()
{
	DataHelper::GetPropertyData( m_objId, _T( "����" ), m_name );
	DataHelper::GetPropertyData( m_objId, _T( "ֱ��" ), m_diameter );
	DataHelper::GetPropertyData( m_objId, _T( "����" ), m_lenth);
	DataHelper::GetPropertyData( m_objId, _T( "���" ), m_bend );
	DataHelper::GetPropertyData( m_objId, _T( "Ħ��ϵ��" ), m_friction );
	DataHelper::GetPropertyData( m_objId, _T( "��ͷ��" ), m_joints );
	DataHelper::GetPropertyData( m_objId, _T( "���׷���" ), m_hmWindage );

	CString v;
	DataHelper::GetPropertyData( m_objId, _T( "����" ), v );
	
	int idx = ReadStringIntDatas(v,_T("��Ͳ����"));

	m_material.SetCurSel(idx);
	
	initDatas();
	
	UpdateData(FALSE);
}

void ChimneyDockBarChildDlg::writePropertyData()
{
	UpdateData(TRUE);

	DataHelper::SetPropertyData( m_objId, _T( "����" ), m_name );
	DataHelper::SetPropertyData( m_objId, _T( "ֱ��" ), m_diameter );
	DataHelper::SetPropertyData( m_objId, _T( "����" ), m_lenth);
	DataHelper::SetPropertyData( m_objId, _T( "���" ), m_bend);
	DataHelper::SetPropertyData( m_objId, _T( "Ħ��ϵ��" ), m_friction );
	DataHelper::SetPropertyData( m_objId, _T( "��ͷ��" ), m_joints );
	DataHelper::SetPropertyData( m_objId, _T( "���׷���" ), m_hmWindage );

	CString rString = ReadIntStringDatas(m_material.GetCurSel(),_T("��Ͳ����"));
	//m_material.GetLBText(indx,rString);
	DataHelper::SetPropertyData( m_objId, _T( "����" ), rString );

	//CString v;
	//v.Format( _T( "%d" ), m_material.GetCurSel() );
	////m_material.GetLBTextLen(v);
	//DataHelper::SetPropertyData( m_objId, _T( "����" ), v );

}
// ChimneyDockBarChildDlg ��Ϣ�������


void ChimneyDockBarChildDlg::OnEnKillfocusChimneyDiameterEdit()
{
	readAlpha();
}

void ChimneyDockBarChildDlg::OnCbnSelchangeChimneyMaterialCombo()
{
	readAlpha();
}

void ChimneyDockBarChildDlg::readAlpha()
{
	CString matType;
	int idx = m_material.GetCurSel();
	//acutPrintf(_T("\nxxx:%d"),m_material.GetCurSel());
	//GetLBText(int nIndex, CString& rString)�е�nIndex��֧��-1
	if (-1 == idx)
	{
		idx = 0;
	}
	m_material.GetLBText(idx,matType);

	CString dia;
	GetDlgItem(IDC_CHIMNEY_DIAMETER_EDIT)->GetWindowText(dia);

	CString friction = ReadAlpha(matType,dia);

	//acutPrintf(_T("\nĦ��ϵ����%s"),friction);

	CEdit* pFriction = (CEdit*) GetDlgItem(IDC_CHIMNEY_FRICTION_EDIT);
	pFriction->SetWindowText( friction );	

}

void ChimneyDockBarChildDlg::initDatas()
{

	//Ĭ��ֵ��������
	//double leakage,diameter;

	//ArxUtilHelper::StringToDouble(m_diameter,diameter);
	//ArxUtilHelper::StringToDouble(m_leakage,leakage);

	//if (leakage > 53.31 || leakage < 1.24)
	//{
	//	m_leakage = _T("53.31");
	//}
	//if (0 >= diameter)
	//{
	//	m_diameter = _T("600");
	//}
}
void ChimneyDockBarChildDlg::OnEnKillfocusChimneyFrictionEdit()
{
	CString msg;
	GetDlgItem(IDC_CHIMNEY_FRICTION_EDIT)->GetWindowText(msg);

	//��ʧȥ�����ʱ�������ų������Ƿ�Ϊ��
	//����Ǹ�������ֵ
	if (msg.IsEmpty())
	{
		readAlpha();
	}
}

void ChimneyDockBarChildDlg::OnEnSetfocusChimneyFrictionEdit()
{
	CString msg;
	GetDlgItem(IDC_CHIMNEY_FRICTION_EDIT)->GetWindowText(msg);

	if (_T("���ݿ��޸�ֱ��") == msg)
	{
		msg = _T("");
		CEdit* pFriction = (CEdit*) GetDlgItem(IDC_CHIMNEY_FRICTION_EDIT);
		pFriction->SetWindowText( msg );	
	}
}
