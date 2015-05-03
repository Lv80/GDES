#include "stdafx.h"
#include "FanMethoChoosedDlg.h"
#include "../MineGE/HelperClass.h"

extern CString ReadIntStringDatas(int intData,CString typeName);
extern int ReadStringIntDatas(CString strData,CString typeName);

// FanMethoChoosedDlg �Ի���

IMPLEMENT_DYNAMIC(FanMethoChoosedDlg, PropertyData_DockBarChildDlg)

FanMethoChoosedDlg::FanMethoChoosedDlg(CWnd* pParent /*=NULL*/)
	: PropertyData_DockBarChildDlg(FanMethoChoosedDlg::IDD, pParent)
	, m_fanRank(_T(""))
	, m_ventMethod(_T(""))
	, m_ventWay(_T(""))
{

}

FanMethoChoosedDlg::~FanMethoChoosedDlg()
{
}

void FanMethoChoosedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEATHOD_COMBO, m_method);
	DDX_Text(pDX, IDC_RANK_EDIT, m_fanRank);
	DDX_Text(pDX, IDC_METHOD_DISP_EDIT, m_ventMethod);
	DDX_Text(pDX, IDC_WAY_DISP_EDIT2, m_ventWay);
}


BEGIN_MESSAGE_MAP(FanMethoChoosedDlg, PropertyData_DockBarChildDlg)
END_MESSAGE_MAP()

void FanMethoChoosedDlg::readPropertyData()
{
	DataHelper::GetPropertyData(m_objId,_T("�������"),m_fanRank);
	CString v;
	DataHelper::GetPropertyData( m_objId, _T( "������ʽ" ), v );

	int idx = ReadStringIntDatas(v,_T("������ʽ"));

	m_method.SetCurSel(idx);

	DataHelper::GetPropertyData(m_objId,_T("ͨ�緽ʽ"),m_ventMethod);
	DataHelper::GetPropertyData(m_objId,_T("ͨ�緽��"),m_ventWay);

	if (m_fanRank.IsEmpty())
	{
		m_fanRank = _T("1");
	}
	
	UpdateData(FALSE);
}

void FanMethoChoosedDlg::writePropertyData()
{
	UpdateData(TRUE);
	DataHelper::SetPropertyData(m_objId,_T("�������"),m_fanRank);
	CString rString = ReadIntStringDatas(m_method.GetCurSel(),_T("������ʽ"));
	
	//if (rString.IsEmpty())
	//{
	//	if (_T("ѹ��ʽ") == m_ventWay || _T("��ѹ�̳�") == m_ventWay)
	//	{
	//		rString = _T("ѹ��ʽ");
	//	}
	//	else
	//	{
	//		rString = _T("���ʽ");
	//	}
	//}

	DataHelper::SetPropertyData( m_objId, _T( "������ʽ" ), rString );
	DataHelper::SetPropertyData(m_objId,_T("ͨ�緽ʽ"),m_ventMethod);
	DataHelper::SetPropertyData(m_objId,_T("ͨ�緽��"),m_ventWay);
}

BOOL FanMethoChoosedDlg::OnInitDialog()
{
	PropertyData_DockBarChildDlg::OnInitDialog();

	m_method.AddString( _T( "ѹ��ʽ" ) );
	m_method.AddString( _T( "���ʽ" ) );

	readPropertyData();
	return TRUE;

}
