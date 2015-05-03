#include "stdafx.h"
#include "BaseParamDlg.h"

#include "../MineGE/HelperClass.h"
#include "../ArxHelper/HelperClass.h"

extern CString ReadIntStringDatas(int intData,CString typeName);
extern int ReadStringIntDatas(CString strData,CString typeName);

IMPLEMENT_DYNAMIC(BaseParamDlg, CDialog)

BaseParamDlg::BaseParamDlg(CWnd* pParent /*=NULL*/,AcDbObjectId objId)
: CDialog(BaseParamDlg::IDD, pParent)
, m_name(_T(""))
, m_district(_T(""))
{
	m_objId = objId;
}

BaseParamDlg::~BaseParamDlg()
{
}

void BaseParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Text(pDX, IDC_DISTRICT_EDIT, m_district);
	DDX_Control(pDX, IDC_METHODS_COMBO, m_method);
	DDX_Control(pDX, IDC_WAYS_COMBO, m_way);
}


BEGIN_MESSAGE_MAP(BaseParamDlg, CDialog)
	ON_BN_CLICKED( IDOK, &BaseParamDlg::OnBnClickedOk )
END_MESSAGE_MAP()

void BaseParamDlg::readPropertyData()
{
	//AcDbObjectId objId;
	//SingleDataObjectHelper::GetObjectId( _T( "��������" ), objId );

	DataHelper::GetPropertyData( m_objId, _T( "������" ), m_name );
	DataHelper::GetPropertyData( m_objId, _T( "������(��)��" ), m_district );


	m_method.AddString( _T( "ѹ��ʽ" ) );
	m_method.AddString( _T( "���ʽ" ) );
	m_method.AddString( _T( "�����ѹ" ) );
	m_method.AddString( _T( "��ѹ�̳�" ) );

	
	CString v1;
	DataHelper::GetPropertyData( m_objId, _T( "ͨ�緽��" ), v1 );
	
	int idx1 = ReadStringIntDatas(v1,_T("ͨ�緽��"));
	m_method.SetCurSel( idx1 );

	m_way.AddString( _T( "��������Ͳ" ) );
	m_way.AddString( _T( "������Ͳ" ) );
	m_way.AddString( _T( "��Ϸ�Ͳ" ) );
	//m_way.AddString( _T( "����˫��" ) );
	m_way.AddString( _T( "��������" ) );
	m_way.AddString( _T( "���ͨ��" ) );
	m_way.AddString( _T( "���ͨ��" ) );
	m_way.AddString( _T( "���ͨ��" ) );
	m_way.AddString( _T( "���ͨ��" ) );

	CString v2;
	DataHelper::GetPropertyData( m_objId, _T( "ͨ�緽ʽ" ), v2 );

	int idx2 = ReadStringIntDatas(v2,_T("ͨ�緽ʽ"));
	m_way.SetCurSel( idx2 );
	
	//acutPrintf(_T("\nReading:%d\t%s"),idx2,v2);
	UpdateData( FALSE );
}

void BaseParamDlg::writePropertyData()
{
	UpdateData( TRUE );

	//AcDbObjectId objId;
	//SingleDataObjectHelper::GetObjectId( _T( "��������" ), objId );

	DataHelper::SetPropertyData( m_objId, _T( "������" ), m_name );
	DataHelper::SetPropertyData( m_objId, _T( "������(��)��" ), m_district );

	CString rString1 = ReadIntStringDatas(m_method.GetCurSel(),_T("ͨ�緽��"));
	DataHelper::SetPropertyData( m_objId, _T( "ͨ�緽��" ), rString1 );

	CString rString2 = ReadIntStringDatas(m_way.GetCurSel(),_T("ͨ�緽ʽ"));
	DataHelper::SetPropertyData( m_objId, _T( "ͨ�緽ʽ" ), rString2 );
	
	//acutPrintf(_T("\nWriting:%d\t%s"),m_way.GetCurSel(),rString2);

}

BOOL BaseParamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	readPropertyData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE

}

void BaseParamDlg::OnBnClickedOk()
{
	writePropertyData();
	OnOK();
}
