#include "stdafx.h"
#include "RcuDesignDlg.h"
#include "RcuNewDlg.h"
#include "RcuEditDlg.h"
#include "RcuHelper.h"
#include "RcuDataLink.h"
#include "Rcu.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

#include "../DefGE/RcuGE.h"
#include "../DefGE/Pore.h"
#include "../DefGE/DrillSite.h"
#include "../DefGE/RockGate.h"
#include "../DefGE/CoalSurface.h"

struct ItemData
{
	int iItem;            // �ڼ��е�����
	AcDbObjectId objId;   // ����id
};

static bool CaculCoalFaceParam(const RockGateLink& rg_link,CoalSurfaceLink& cs_link)
{
	AcGePoint3d orign;
	ArxUtilHelper::StringToPoint3d(rg_link.m_pt,orign);
	Rcu rcu;
	rcu.setOrigin(orign);
	rcu.setRockGateParams(rg_link.m_dist,rg_link.m_top,rg_link.m_bottom,rg_link.m_left,rg_link.m_right);
	rcu.setTunnelParams(rg_link.m_height,rg_link.m_width,rg_link.m_width);
	//�ڶ���������ʯ��������ú������ļн�
	//���ǽ�������ʱû�У����Կ���90�ȵ�
	double angle = DegToRad(cs_link.m_angle);
	rcu.setCoalParams(angle,PI*0.5,cs_link.m_thick);
	double w,h;
	rcu.drillExtent(w,h);
	cs_link.m_width = w;
	cs_link.m_height = h;
	acutPrintf(_T("\n����ʱ->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);
	return true;
}

static bool GetRockGateDataFromDlg(RockGateLink& rg_link, CoalSurfaceLink& cs_link)
{
	CAcModuleResourceOverride resourceOverride;
	RcuNewDlg dlg;
	if(IDOK != dlg.DoModal()) return false;

	//�ӶԻ�������ȡ����
	dlg.writeToDataLink(rg_link, cs_link);

	return true;
}

static bool ShowRcuEditDlg(const AcDbObjectId& rock_gate)
{
	CAcModuleResourceOverride resourceOverride;
	RcuEditDlg dlg;
	//����һ��ʯ��
	dlg.m_rock_gate = rock_gate;
	return (IDOK == dlg.DoModal());
}

static void ModifyRockGateToListCtrl(CListCtrl& m_list, int n, RockGateLink& rg_link)
{
	{
		m_list.SetItemText( n, 1, rg_link.m_name );
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_length, value);
		m_list.SetItemText( n, 2, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_width, value);
		m_list.SetItemText( n, 3, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_height, value);
		m_list.SetItemText( n, 4, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_dist, value);
		m_list.SetItemText( n, 5, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_radius, value);
		m_list.SetItemText( n, 6, value);
	}
	{
		m_list.SetItemText( n, 7, rg_link.m_pt);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_left, value);
		m_list.SetItemText( n, 8, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_right, value);
		m_list.SetItemText( n, 9, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_top, value);
		m_list.SetItemText( n, 10, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_bottom, value);
		m_list.SetItemText( n, 11, value);
	}
}

static void InsertRockGateToListCtrl(CListCtrl& m_list, const AcDbObjectId& objId, RockGateLink& rg_link)
{
	int n = m_list.GetItemCount();
	//����һ������
	m_list.InsertItem( n, _T( "xx" ) );

	//���ñ��
	CString num;
	num.Format( _T( "%d" ), n + 1 );
	m_list.SetItemText( n, 0, num );

	//��ÿһ�и�������
	ItemData* pData = new ItemData();
	pData->iItem = n;
	pData->objId = objId;
	m_list.SetItemData( n, ( LPARAM )pData ); // ��������

	//�޸�һ������
	ModifyRockGateToListCtrl(m_list, n, rg_link);

}

static void ClearListCtrlItem( CListCtrl& m_list, int row )
{
	int n = m_list.GetItemCount();
	if(row != LB_ERR && n > 0 && row < n) 
	{
		ItemData* pData = ( ItemData* )m_list.GetItemData( row );
		delete pData;
		m_list.DeleteItem(row);
	}
}

static void InsertDatasToListCtrl( CListCtrl& m_list, const AcStringArray fields, const AcDbObjectIdArray& objIds )
{
	//����ɾ��������
	m_list.DeleteAllItems();

	int len = objIds.length();
	for( int i = 0; i < len; i++ )
	{
		m_list.InsertItem( i, _T( "xx" ) );

		CString num;
		num.Format( _T( "%d" ), i + 1 );
		m_list.SetItemText( i, 0, num );

		ItemData* pData = new ItemData();
		pData->iItem = i;
		pData->objId = objIds[i];
		m_list.SetItemData( i, ( LPARAM )pData ); // ��������

		int n = fields.length();
		for( int j = 0; j < n; j++ )
		{
			//m_list.SetItemData(i, i);
			CString value;
			DataHelper::GetPropertyData( objIds[i], fields[j].kACharPtr(), value );
			m_list.SetItemText( i, j + 1, value );
		}
	}
}

static void ClearListCtrlItemDatas( CListCtrl& m_list )
{
	int n = m_list.GetItemCount();
	for( int i = 0; i < n; i++ )
	{
		ItemData* pData = ( ItemData* )m_list.GetItemData( i );
		delete pData;
	}
}

static void BuildListCtrlHeadColumns( CListCtrl& m_list, const AcStringArray fields )
{
	int len = fields.length();

	CRect rect;
	m_list.GetClientRect( &rect );

	int n = len;
	if( n > 10 ) n = 7;
	double dw = rect.Width() / ( n + 1 );

	m_list.InsertColumn( 0, _T( "���" ), LVCFMT_CENTER, dw );
	for( int i = 0; i < len; i++ )
	{
		m_list.InsertColumn( i + 1, fields[i].kACharPtr(), LVCFMT_LEFT, dw );
	}
}

static void CrackHeadColumnWidth(CListCtrl& m_list)
{
	m_list.SetColumnWidth(1, int(m_list.GetColumnWidth(1)*1.2));
	for(int i=5;i<m_list.GetHeaderCtrl()->GetItemCount()+1;i++)
	{
		m_list.SetColumnWidth(i, int(m_list.GetColumnWidth(i)*1.5));
	}
	m_list.SetColumnWidth(7, int(m_list.GetColumnWidth(7)*1.5));
}

static void ClearListCtrl( CListCtrl& m_list )
{
	//����ɾ��������
	m_list.DeleteAllItems();
	//�õ�����
	int n = m_list.GetHeaderCtrl()->GetItemCount();
	//ɾ��������
	for( int i = 0; i < n; i++ )
	{
		m_list.DeleteColumn( 0 );
	}
}

static void ZoomToEntity( const AcDbObjectId& objId )
{
	// �ڷ�ģ̬�Ի������޷�ʹ��
	//ads_name en;
	//if(Acad::eOk != acdbGetAdsName(en, objId)) return;
	//acedCommand(RTSTR, _T("ZOOM"), RTSTR, _T("O"), RTENAME, en, RTSTR, _T(""), 0);

	// ��ʱʹ��sendStringToExecute������Ŷ�λ����
	CString cmd;
	cmd.Format( _T( "ZOOM O \003" ) ); // ���ո����ѡ�����Ȼ��esc(��ֹ����Ŀո��ظ�ִ������)
	acDocManager->sendStringToExecute( curDoc(), cmd, true, false, false );
}

//��ȡ��ǰѡ�����
static int GetCurSelOfList(CListCtrl& m_list)
{
	int row = LB_ERR;
	for( int i = 0; i < m_list.GetItemCount(); i++ )
	{
		if( LVIS_SELECTED == m_list.GetItemState( i, LVIS_SELECTED ) )
		{
			row = i;
			break;
		}
	}
	return row;
}

// RcuDesignDlg �Ի���

IMPLEMENT_DYNAMIC(RcuDesignDlg, DockBarChildDlg)

RcuDesignDlg::RcuDesignDlg(CWnd* pParent /*=NULL*/)
	: DockBarChildDlg(RcuDesignDlg::IDD, pParent)
{

}

RcuDesignDlg::~RcuDesignDlg()
{
	ClearListCtrlItemDatas(m_list);
}

void RcuDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	DockBarChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(RcuDesignDlg, DockBarChildDlg)
	ON_BN_CLICKED(IDC_BUTTON4, &RcuDesignDlg::OnBnClickedExport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &RcuDesignDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &RcuDesignDlg::OnNMRclickList1)
	ON_COMMAND(ID_RCU_LIST_HILIGHT, &RcuDesignDlg::OnHilightCommand)
	ON_COMMAND(ID_RCU_LIST_MODIFY, &RcuDesignDlg::OnModifyCommand)
	ON_COMMAND(ID_RCU_LIST_DELETE, &RcuDesignDlg::OnDeleteCommand)
	ON_COMMAND(ID_RCU_LIST_ADD, &RcuDesignDlg::OnAddCommand)
END_MESSAGE_MAP()

BOOL RcuDesignDlg::OnInitDialog()
{
	DockBarChildDlg::OnInitDialog();

	m_list.SetExtendedStyle( m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	
	AcStringArray fields;
	FieldHelper::GetAllFields(_T("RockGate"), fields);
	// ����Column
	BuildListCtrlHeadColumns( m_list, fields );
	CrackHeadColumnWidth(m_list);

	acDocManager->lockDocument( curDoc() );

	AcDbObjectIdArray objIds;
	RcuHelper::FindAllRockGates(objIds);

	acDocManager->unlockDocument( curDoc() );

	InsertDatasToListCtrl(m_list, fields, objIds);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void RcuDesignDlg::OnClosing()
{
	//ɾ���б���ÿһ�и���������(��Щ���ݶ���new������)
	//ClearListCtrlItemDatas(m_list);
	// �������
	//ClearList(m_list);
}

// RcuDesignDlg ��Ϣ�������

void RcuDesignDlg::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RcuDesignDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row = pNMItemActivate->iItem;
	if( row != LB_ERR )
	{
		ItemData* pData = ( ItemData* )m_list.GetItemData( row );

		acDocManager->lockDocument( curDoc() );
		//����ѡ��ͼԪ
		ArxEntityHelper::SelectEntity(pData->objId);
		//��λ��ͼԪ
		//ArxEntityHelper::ZoomToEntity(pData->objId);
		ZoomToEntity(pData->objId);
		acDocManager->unlockDocument( curDoc() );
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row = pNMItemActivate->iItem;
	//��ֹ�ڿհ�����������˵�
	//if (m_list.GetSelectedCount() > 0)
	{
		//�������δ���, ��������Ӧ��ListCtrl
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_RCU_LIST_MENU);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint); //���λ��
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);  
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnHilightCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnHilightCommand"));
	int row = GetCurSelOfList(m_list);
	if(row != LB_ERR)
	{
		ItemData* pData = ( ItemData* )m_list.GetItemData( row );

		//����ѡ��ʯ��ͼԪ
		acDocManager->lockDocument( curDoc() );
		ArxEntityHelper::SelectEntity(pData->objId);
		acDocManager->unlockDocument( curDoc() );

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnModifyCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnLocateCommand"));
	int row = GetCurSelOfList(m_list);
	if(row == LB_ERR)
	{
		MessageBox( _T( "��ȷ����ǰ��һ�б�ѡ��!" ) );
	}
	else
	{
		ItemData* pData = ( ItemData* )m_list.GetItemData( row );

		//�л�controlbar����ʾ
		ControlBarShowSwitch cb_switch(this);

		acDocManager->lockDocument( curDoc() );
		//�û������"ȷ��"��ť
		//��Ҫ���¸���listctrl�е�����
		if(ShowRcuEditDlg(pData->objId))
		{
			//��ʯ������ȡ����
			RockGateLink rg_link;
			rg_link.setDataSource(pData->objId);
			rg_link.updateData(false);
			//�޸ĵ�ǰѡ���е�����
			ModifyRockGateToListCtrl(m_list, row, rg_link);

			CoalSurfaceLink cs_link;
			cs_link.updateData(false);
			acutPrintf(_T("\n����֮ǰ->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);
			CaculCoalFaceParam(rg_link,cs_link);
			cs_link.updateData(true);
			acutPrintf(_T("\n����֮��->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);

		}

		acDocManager->unlockDocument( curDoc() );
		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnDeleteCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnDeleteCommand"));
	int row = GetCurSelOfList(m_list);
	if(row != LB_ERR)
	{
		ItemData* pData = ( ItemData* )m_list.GetItemData( row );

		//ɾ��ʯ��ͼԪ
		acDocManager->lockDocument( curDoc() );
		ArxEntityHelper::EraseObject(pData->objId, true);
		acDocManager->unlockDocument( curDoc() );

		//ɾ��ѡ�����
		ClearListCtrlItem(m_list, row);
		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnAddCommand()
{
	//��ģ̬�Ի���AutoCAD��ý���
	acedGetAcadDwgView()->SetFocus();

	acDocManager->lockDocument( curDoc() );

	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	AcGePoint3d pt;
	if(!ArxUtilHelper::PromptPt(_T("\n��ѡ��ʯ�ŵĲ�������꣺"), pt)) return;

	//����Datalink����,�����ַ�����ʽ������
	RockGateLink rg_link;
	CoalSurfaceLink cs_link;
	if(!GetRockGateDataFromDlg(rg_link, cs_link)) return;

	//�½�ʯ�Ų����ò��������
	RockGate* pRG = new RockGate();
	pRG->setInsertPt(pt);

	CoalSurface* pCS = new CoalSurface();
	pCS->setInsertPt(AcGePoint3d(pt.x, pt.y+500, pt.z));

	//���ʯ�ŵ�cadͼ�����ݿ�
	if(!ArxUtilHelper::PostToModelSpace(pRG))
	{
		delete pRG; pRG = 0;
	}
	else
	{
		acutPrintf(_T("\n����֮ǰ->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);
		CaculCoalFaceParam(rg_link,cs_link);
		cs_link.updateData(true);
		acutPrintf(_T("\n����֮��->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);

		//ú�������ʯ��
		pCS->setRelatedGE(pRG->objectId());
		//���ú�㵽cadͼ�����ݿ�
		if(!ArxUtilHelper::PostToModelSpace(pCS))
		{
			delete pCS; pCS = 0;
			//ú���ύʧ��,��ɾ������ӵ�ʯ��
			ArxEntityHelper::EraseObject(pRG->objectId(), true);
		}
		else
		{
			//ͨ��DataLink�������ݶ���,��д�뵽ͼԪ��
			rg_link.setDataSource(pRG->objectId());
			rg_link.updateData(true);
			cs_link.setDataSource(pCS->objectId());
			cs_link.updateData(true);

			//��listctrl�в���һ��
			InsertRockGateToListCtrl(m_list, pRG->objectId(), rg_link);
		}
	}
	acDocManager->unlockDocument( curDoc() );
}