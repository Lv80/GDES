#include "stdafx.h"
#include "WcyPropertyDlg.h"

#include "../MineGE/DataHelper.h"
#include "../MineGE/FieldHelper.h"
#include "../MineGE/PropertyDataUpdater.h"
#include "../MineGE/FuncFieldHelper.h"
#include "../MineGE/config.h"
#include "../MineGE/CustomProperties.h"

IMPLEMENT_DYNAMIC(WcyPropertyDlg, CDialog)

WcyPropertyDlg::WcyPropertyDlg( CWnd* pParent /*=NULL*/,CString func )
: CDialog( WcyPropertyDlg::IDD, pParent )
{
	m_showAll = true; // Ĭ����ʾȫ������
	m_func = func;
}

WcyPropertyDlg::~WcyPropertyDlg()
{
}

void WcyPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CACUL_MATHOD_COMBO, m_method);
}


BEGIN_MESSAGE_MAP(WcyPropertyDlg, CDialog)
	ON_BN_CLICKED( IDOK, &WcyPropertyDlg::OnBnClickedOk )
	ON_CBN_SELCHANGE(IDC_CACUL_MATHOD_COMBO, &WcyPropertyDlg::OnCbnSelchangeCaculMathodCombo)
END_MESSAGE_MAP()


// WcyPropertyDlg ��Ϣ�������

void WcyPropertyDlg::OnCbnSelchangeCaculMathodCombo()
{
	int indx = m_method.GetCurSel();
	switch(indx)
	{
	case 0:
		//ͨ����˹���������
		m_func = _T("ͨ����˹���������");
		break;

	case 1:
		//ͨ��������˹ѹ������
		m_func = _T("ͨ��������˹ѹ������");
		break;

	default:
		m_func = _T("");
		break;
	}
}

BOOL WcyPropertyDlg::InitPropGridCtrl()
{
	// ����, ��λ, ��ʾCMFCPropertyGridCtrl
	CRect rect;
	GetDlgItem( IDC_PROP_POS2 )->GetWindowRect( &rect );
	ScreenToClient( &rect );
	m_propertyDataList.Create( WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, ( UINT ) - 1 );
	//m_propertyDataList.SetAlphabeticMode(true);
	// ��ȡ��������
	CString type;
	DataHelper::GetTypeName( m_objId, type );

	AcStringArray funcs,funcFieldsInfo;
	if(m_func.IsEmpty())
	{
		FuncFieldHelper::GetFunctions(funcs);
	}
	else
	{
		funcs.append(m_func);
	}
	int funcNum = funcs.length();
	for (int i = 0; i < funcNum; i++)
	{
		AcStringArray fields;
		FuncFieldHelper::GetFields(funcs[i].kACharPtr(),type,fields);
		if(fields.isEmpty()) continue;
		funcFieldsInfo.append(_T("$"));
		funcFieldsInfo.append(funcs[i]);
		for(int j = 0; j < fields.length(); j++)
		{
			funcFieldsInfo.append(fields[j]);
			//acutPrintf(_T("\n����:%s\t�ֶ�:%s"),funcs[i].kACharPtr(),fields[j].kACharPtr());
		}
	}

	PropertyDataUpdater::BuildPropGridCtrl( &m_propertyDataList, type,funcFieldsInfo );

	// �����������
	bool ret = PropertyDataUpdater::ReadDataFromGE( &m_propertyDataList, m_objId );

	// �������ʧ��
	if( !ret )
	{
		m_propertyDataList.EnableWindow( FALSE );
		m_propertyDataList.ShowWindow( SW_HIDE );
	}
	return TRUE;
}


BOOL WcyPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_method.AddString( _T( "ͨ����˹���������" ) );
	m_method.AddString( _T( "ͨ��������˹ѹ������" ) );

	 return InitPropGridCtrl();
	 if(m_func.IsEmpty())
	 {
		 return FALSE;
	 }
	// �����������ݿؼ�


	//return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE

}

void WcyPropertyDlg::setMineGE( const AcDbObjectId& objId )
{
	m_objId = objId;
}

void WcyPropertyDlg::addField( const CString& field )
{
	m_fields.append( field );
}

void WcyPropertyDlg::showAllData( bool bFlag )
{
	m_showAll = bFlag;
}

static void HighlightGridProperty(CMFCPropertyGridCtrl* pPropDataList, bool bHighlight)
{
	int nCount = pPropDataList->GetPropertyCount();
	for ( int i = 0; i < nCount; i++ )
	{
		CMFCPropertyGridProperty* pGroup = pPropDataList->GetProperty( i );
		for(int j = 0; j < pGroup->GetSubItemsCount(); j++)
		{
			CMFCPropertyGridProperty* pProp = pGroup->GetSubItem( j );
			if(!pProp->IsEnabled())
			{
				CustomGridProperty* cProp = (CustomGridProperty*)pProp;
				cProp->highlight(bHighlight);
			}
		}
	}
}

void WcyPropertyDlg::OnBnClickedOk()
{
    UpdateData( TRUE ); // ���¿ؼ�

    // ����ͼԪ����������
    PropertyDataUpdater::WriteDataToGE( &m_propertyDataList, m_objId );
	

	if(m_func.IsEmpty() || _T("������Ϣ") == m_func)
	{
		OnOK();
		return;
	}

	//���㹦��
	//UpdateData(FALSE);
	//if(!caculate())
	//{
	//	//OnOK();
	//	return;
	//}

	SetTimer(100,500,NULL);
	AfxMessageBox(_T("����ɹ�!"));

	HighlightGridProperty(&m_propertyDataList, true);

	// �����������
	bool ret = PropertyDataUpdater::ReadDataFromGE( &m_propertyDataList, m_objId );

	// �������ʧ��
	if( !ret )
	{
		m_propertyDataList.EnableWindow( FALSE );
		m_propertyDataList.ShowWindow( SW_HIDE );
	}

	HighlightGridProperty(&m_propertyDataList, m_objId);
}

void WcyPropertyDlg::OnTimer( UINT_PTR nIDEvent )
{
	CDialog::OnTimer(nIDEvent);
	if (nIDEvent == 100)
	{
		KillTimer(nIDEvent);
		keybd_event(VK_RETURN,0,0,0);
		keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);//ģ��"�س�"����
	}
}