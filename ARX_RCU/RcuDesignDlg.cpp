#include "stdafx.h"
#include "RcuDesignDlg.h"
#include "RcuEditRockGateDlg.h"
#include "RcuEditDrillSiteDlg.h"
#include "RcuEditOpenPoreDlg.h"

#include "Rcu.h"
#include "RcuHelper.h"
#include "RcuDataLink.h"
#include "ListCtrlHelper.h"
#include "SwitchHelper.h"

#include "../ArxHelper/HelperClass.h"
#include "../MineGE/HelperClass.h"

#include "../DefGE/RcuGE.h"
#include "../DefGE/Pore.h"
#include "../DefGE/DrillSite.h"
#include "../DefGE/RockGate.h"
#include "../DefGE/CoalSurface.h"

//�Զ�����Ϣ
#include "MyMsg.h"

//΢��list1�ı�ͷ�п��
static void CrackHeadColumnWidth(CListCtrl& m_list)
{
	m_list.SetColumnWidth(1, int(m_list.GetColumnWidth(1)*1.2));
	for(int i=5;i<m_list.GetHeaderCtrl()->GetItemCount()+1;i++)
	{
		m_list.SetColumnWidth(i, int(m_list.GetColumnWidth(i)*1.5));
	}
	m_list.SetColumnWidth(7, int(m_list.GetColumnWidth(7)*1.5));
}

//�޸��곡�б��n�е�����
static void ModifyDrillSiteToListCtrl(CListCtrl& m_list2, int n, const DrillSiteLink& ds_link)
{
	{
		m_list2.SetItemText( n, 1, ds_link.m_name );
	}
	{
		CString value;
		ArxUtilHelper::IntToString(ds_link.m_leftOrRight, value);
		m_list2.SetItemText( n, 2, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_dist, value);
		m_list2.SetItemText( n, 3, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_depth, value);
		m_list2.SetItemText( n, 4, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_height, value);
		m_list2.SetItemText( n, 5, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_radius, value);
		m_list2.SetItemText( n, 6, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(ds_link.m_gap, value);
		m_list2.SetItemText( n, 7, value);
	}
	{
		CString value;
		ArxUtilHelper::IntToString(ds_link.m_start, value);
		m_list2.SetItemText( n, 8, value);
	}
	
	{
		m_list2.SetItemText( n, 9, ArxUtilHelper::Point3dToString(ds_link.m_pt));
	}
}

//�޸�ʯ���б��n�е�����
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
		m_list.SetItemText( n, 6, ArxUtilHelper::Point3dToString(rg_link.m_pt));
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_left, value);
		m_list.SetItemText( n, 7, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_right, value);
		m_list.SetItemText( n, 8, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_top, value);
		m_list.SetItemText( n, 9, value);
	}
	{
		CString value;
		ArxUtilHelper::DoubleToString(rg_link.m_bottom, value);
		m_list.SetItemText( n, 10, value);
	}
}

//��ʯ���б�������һ��
static void InsertRockGateToListCtrl(CListCtrl& m_list, const AcDbObjectId& objId, RockGateLink& rg_link)
{
	int row = ListCtrlHelper::SearchRowOfList(m_list, objId);
	if(row == -1)
	{
		//����һ��
		row = ListCtrlHelper::InsertRowToListCtrl(m_list, objId);
	}
	//����ʯ���б�ĸ�������
	ModifyRockGateToListCtrl(m_list, row, rg_link);
}

//���곡�б�������һ��
static void InsertDrillSiteToListCtrl(CListCtrl& m_list, const AcDbObjectId& objId, const DrillSiteLink& ds_link)
{
	int row = ListCtrlHelper::SearchRowOfList(m_list, objId);
	if(row == -1)
	{
		//����һ��
		row = ListCtrlHelper::InsertRowToListCtrl(m_list, objId);
	}
	//�����곡�б�ĸ�������
	ModifyDrillSiteToListCtrl(m_list, row, ds_link);
}

static bool UpdateRockGateDataFromDlg(const AcDbObjectId& rock_gate, RockGateLink& rg_link, CoalSurfaceLink& cs_link)
{
	CAcModuleResourceOverride resourceOverride;

	//��ʼ��ʯ�ŶԻ���
	RcuEditRockGateDlg dlg;
	dlg.m_rock_gate = rock_gate;
	//���ʯ��id��Ϊ��,���ȡ���ݲ����µ��Ի���
	dlg.readFromDataLink(rg_link, cs_link);

	if(IDOK != dlg.DoModal()) return false;

	//�ӶԻ�������ȡ����
	dlg.writeToDataLink(rg_link, cs_link);

	//�����ݸ��µ�ͼԪ��
	rg_link.updateData(true);
	cs_link.updateData(true);

	return true;
}

static bool UpdateDrillSiteDataFromDlg(const AcDbObjectId& drill_site, DrillSiteLink& ds_link)
{
	CAcModuleResourceOverride resourceOverride;

	//��ʼ���곡�Ի���
	RcuEditDrillSiteDlg dlg;
	dlg.m_drill_site = drill_site;
	dlg.readFromDataLink(ds_link);

	if(IDOK != dlg.DoModal()) return false;

	//�ӶԻ�������ȡ����
	dlg.writeToDataLink(ds_link);

	if(!drill_site.isNull())
	{
		//�޸��곡�ļ��β���
		RcuHelper::ModifyDrillSiteParam(drill_site, ds_link);
	}

	//�����ݸ��µ�ͼԪ��
	ds_link.updateData(true);
	
	return true;
}

//��ʽ���곡�����ƶԻ���ı���
static CString FormatPoreDlgTitle(const CString& rg_name, const CString& ds_name)
{
	CString name1 = rg_name;
	CString name2 = ds_name;
	name1.Trim();
	name2.Trim();
	if(name1.IsEmpty())
	{
		name1 = _T("***");
	}
	if(name2.IsEmpty())
	{
		name2 = _T("###");
	}

	CString title;
	title.Format(_T("%sʯ��-%s�곡-������"), name1, name2);
	return title;
}

//��ʽ���곡�����ƶԻ����е�λ����Ϣ
static CString FormatDrillSitePostion(double m_dist, int leftOrRight)
{
	CString pos;
	pos.Format(_T("%s������ӭͷ%.2f��"), (leftOrRight==0)?_T("���"):_T("�Ұ�"), m_dist);
	return pos;
}

static bool UpdateOpenPoresFromDlg(const AcDbObjectId& drill_site, RockGateLink& rg_link, DrillSiteLink& ds_link)
{
	CAcModuleResourceOverride resourceOverride;
	
	RcuEditOpenPoreDlg dlg;
	//��ʽ�������ƶԻ���ı���
	dlg.m_title = FormatPoreDlgTitle(rg_link.m_name, ds_link.m_name);
	//��ʽ���곡��λ����Ϣ
	dlg.m_pos = FormatDrillSitePostion(ds_link.m_dist, ds_link.m_leftOrRight);
	//������װ뾶
	dlg.m_radius = ds_link.m_radius;
	//��ȡ��׵ĸ���
	AcDbObjectIdArray pores;
	RcuHelper::GetRelatedOpenPores(drill_site, pores);
	dlg.m_num = pores.length();
	//��ȡ��׵ļ��
	if(!pores.isEmpty())
	{
		dlg.m_gap = ds_link.m_gap;
	}
	else
	{
		dlg.m_gap = 0;
	}

	if(IDOK != dlg.DoModal()) return false;

	//�ӶԻ����ж�ȡ����
	//��׼��
	ds_link.m_gap = dlg.m_gap;
	//�������ݵ����
	ds_link.updateData(true);

	//ɾ���������������
	RcuHelper::ClearRelatedOpenPores(drill_site);

	//�����µ����ͼԪ
	return RcuHelper::CreateOpenPores(drill_site, ds_link);
}

// RcuDesignDlg �Ի���

IMPLEMENT_DYNAMIC(RcuDesignDlg, DockBarChildDlg)

RcuDesignDlg::RcuDesignDlg(CWnd* pParent /*=NULL*/)
	: DockBarChildDlg(RcuDesignDlg::IDD, pParent)
{
}

RcuDesignDlg::~RcuDesignDlg()
{
	//ClearListCtrlItemDatas(m_list);
}

void RcuDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	DockBarChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST3, m_list2);
}

BEGIN_MESSAGE_MAP(RcuDesignDlg, DockBarChildDlg)
	ON_BN_CLICKED(IDC_BUTTON4, &RcuDesignDlg::OnBnClickedExport)
	ON_BN_CLICKED(IDC_BUTTON1, &RcuDesignDlg::OnBnClickedDesignClosePores)
	ON_BN_CLICKED(IDC_BUTTON2, &RcuDesignDlg::OnBnClickedDesignOpenPores)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &RcuDesignDlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &RcuDesignDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &RcuDesignDlg::OnNMRclickList1)
	ON_COMMAND(ID_RCU_LIST_HILIGHT, &RcuDesignDlg::OnHilightRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_MODIFY, &RcuDesignDlg::OnModifyRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_DELETE, &RcuDesignDlg::OnDeleteRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_ADD, &RcuDesignDlg::OnAddRockGateCommand)
	ON_COMMAND(ID_RCU_LIST_UPDATE, &RcuDesignDlg::OnUpdateRockGateListCommand)
	ON_COMMAND(ID_RCU_COAL_HILIGHT, &RcuDesignDlg::OnHilightCoalSurfCommand)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &RcuDesignDlg::OnNMDblclkList2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &RcuDesignDlg::OnNMRclickList2)
	ON_COMMAND(IDR_DRILL_SITE_ADD, &RcuDesignDlg::OnAddDrillSiteCommand)
	ON_COMMAND(IDR_DRILL_SITE_DELETE, &RcuDesignDlg::OnDeleteDrillSiteCommand)
	ON_COMMAND(IDR_DRILL_SITE_MODIFY, &RcuDesignDlg::OnModifyDrillSiteCommand)
	ON_COMMAND(IDR_DRILL_SITE_HILIGHT, &RcuDesignDlg::OnHilightDrillSiteCommand)

	ON_MESSAGE(WM_RCU_ADD, &RcuDesignDlg::OnRcuAddMessage)
	ON_MESSAGE(WM_RCU_DEL, &RcuDesignDlg::OnRcuDelMessage)
	ON_MESSAGE(WM_RCU_MODIFY, &RcuDesignDlg::OnRcuModifyMessage)
	ON_MESSAGE(WM_RCU_UPDATE, &RcuDesignDlg::OnRcuUpdateMessage)

END_MESSAGE_MAP()

BOOL RcuDesignDlg::OnInitDialog()
{
	DockBarChildDlg::OnInitDialog();

	m_list.SetExtendedStyle( m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	AcStringArray rock_fields;
	FieldHelper::GetAllFields(_T("RockGate"), rock_fields);
	//������ͷ�б�
	ListCtrlHelper::BuildListCtrlHeadColumns( m_list, rock_fields );
	CrackHeadColumnWidth(m_list);

	m_list2.SetExtendedStyle( m_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	AcStringArray drill_fields;
	FieldHelper::GetAllFields(_T("DrillSite"), drill_fields);
	//������ͷ�б�
	ListCtrlHelper::BuildListCtrlHeadColumns( m_list2, drill_fields );

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

/**
http://blog.csdn.net/carl2380/article/details/4816392
http://blog.csdn.net/sjls2659/article/details/7580660
http://blog.csdn.net/oldmtn/article/details/9298577
����ListCtrlʱ��LVN_ITEMCHANGED��Ӧ3�ε���Ī������ı���
�������:
	�������´���
		if(LVIF_STATE == pNMLV->uChanged && (pNMLV->uNewState & LVIS_SELECTED))
		{
			int row = pNMLV->iItem;
		}
*/
void RcuDesignDlg::OnLvnItemchangedList1( NMHDR* pNMHDR, LRESULT* pResult )
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>( pNMHDR );
	*pResult = 0;

	if(LVIF_STATE == pNMLV->uChanged && (pNMLV->uNewState & LVIS_SELECTED))
	{
		int row1 = pNMLV->iItem;
		if( row1 != LB_ERR )
		{
			//��ǰѡ���ʯ��
			ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);

			//����곡�б�
			ListCtrlHelper::ClearListCtrl(m_list2);

			//�ĵ����л�
			DocumentLockSwitch lock_switch;

			//����ʯ�Ź������곡
			AcDbObjectIdArray drill_sites;
			RcuHelper::GetRelatedDrillSites(pData1->objId, drill_sites);
			if(drill_sites.isEmpty()) return;

			//�����곡�������ֶ�
			AcStringArray fields;
			FieldHelper::GetAllFields(_T("DrillSite"), fields);
			if(fields.isEmpty()) return;

			//��ӵ��곡�б�
			ListCtrlHelper::InsertDatasToListCtrl(m_list2, fields, drill_sites);

			//���θ����ڶԸ���Ϣ�Ĵ���
			*pResult = 1;
		}
	}
}

void RcuDesignDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int row1 = pNMItemActivate->iItem;
	if( row1 != LB_ERR )
	{
		ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//����ѡ��ͼԪ
		ArxEntityHelper::SelectEntity(pData1->objId);
		//��λ��ͼԪ
		ArxEntityHelper::ZoomToEntityForModeless(pData1->objId);
		//����pResultΪ1,���θ�������Ӧ����Ϣ
		*pResult = 1;
	}
}

void RcuDesignDlg::OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

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

void RcuDesignDlg::OnAddRockGateCommand()
{
	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//ѡ��ʯ�ŵĲ��������
	AcGePoint3d pt;
	if(!ArxUtilHelper::PromptPt(_T("\n��ѡ��ʯ�ŵĲ�������꣺"), pt)) return;

	//���öԻ����ȡʯ�ź�ú������
	RockGateLink rg_link;
	CoalSurfaceLink cs_link;
	if(!UpdateRockGateDataFromDlg(AcDbObjectId::kNull, rg_link, cs_link)) return;

	//����ʯ�ź�ú��ͼԪ
	if(RcuHelper::CreateRockGate(pt, rg_link, cs_link))
	{
		//��list1�в���һ��ʯ������
		InsertRockGateToListCtrl(m_list, rg_link.getDataSource(), rg_link);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnDeleteRockGateCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnDeleteRockGateCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//ɾ��ͼԪ
		//ע:EraseObject2ʹ��open/closeɾ������Чʯ�ź͹�����ͼԪ
		//   ��EraseObject����ʹ�õ�������,��һ������Чɾ��!!!
		ArxEntityHelper::EraseObject2(pData1->objId, true);

		//ɾ��ѡ�����
		ListCtrlHelper::DeleteListCtrlItem(m_list, row1);
		ListCtrlHelper::ClearListCtrl(m_list2);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnModifyRockGateCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnLocateCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 == LB_ERR)
	{
		MessageBox( _T( "��ȷ����ǰ��һ�б�ѡ��!" ) );
		return;
	}
	ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

	//�ĵ��л���
	DocumentLockSwitch lock_switch;
	
	//��ȡʯ�ź�ú������
	RockGateLink rg_link;
	CoalSurfaceLink cs_link;
	if(!RcuHelper::GetRockGateAndCoalSurfDatas(pData1->objId, rg_link, cs_link))
	{
		MessageBox(_T("��ȡʯ�Ż�ú��ʧ��!!!"));
		return;
	}

	//�л�controlbar����ʾ
	ControlBarShowSwitch cb_switch(this);

	//�ӶԻ����и�������
	if(UpdateRockGateDataFromDlg(pData1->objId, rg_link, cs_link))
	{
		//�޸ĵ�ǰѡ��ʯ�ŵ�����
		ModifyRockGateToListCtrl(m_list, row1, rg_link);
		//acutPrintf(_T("\n����֮ǰ->���:%.4lf\t�߶�:%.4lf\n"),cs_link.m_width,cs_link.m_height);
		
		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnHilightRockGateCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnHilightRockGateCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//����ѡ��ʯ��ͼԪ
		ArxEntityHelper::SelectEntity(pData1->objId);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnUpdateRockGateListCommand()
{
	//���½���
	updateUI();
}

void RcuDesignDlg::OnHilightCoalSurfCommand()
{
	//MessageBox(_T("RcuDesignDlg::OnHilightCoalSurfCommand"));
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		AcDbObjectId coal_surf;
		RcuHelper::GetRelatedCoalSurface(pData1->objId, coal_surf);

		//��������λú��ͼԪ
		ArxEntityHelper::SelectEntity(coal_surf);
		ArxEntityHelper::ZoomToEntityForModeless(coal_surf);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int row = pNMItemActivate->iItem;
	if( row != LB_ERR )
	{
		ItemData* pData = ( ItemData* )m_list2.GetItemData( row );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//����ѡ��ͼԪ
		ArxEntityHelper::SelectEntity(pData->objId);
		//��λ��ͼԪ
		ArxEntityHelper::ZoomToEntityForModeless(pData->objId);
		
		//����pResultΪ1,���θ�������Ӧ����Ϣ
		*pResult = 1;
	}
}

void RcuDesignDlg::OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ڼ���
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	int row = pNMItemActivate->iItem;
	//��ֹ�ڿհ�����������˵�
	//if (m_list2.GetSelectedCount() > 0)
	{
		//�������δ���, ��������Ӧ��ListCtrl
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_DRILL_SITE_MENU);
		pPopup = menu.GetSubMenu(0);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint); //���λ��
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	//����pResultΪ1,���θ�������Ӧ����Ϣ
	*pResult = 1;
}

void RcuDesignDlg::OnAddDrillSiteCommand()
{
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 == LB_ERR)
	{
		MessageBox(_T("��ָ�������ʯ�ź��ٽ����곡���!"));
		return;
	}

	ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);

	//�л�controlbar����ʾ
	//ControlBarShowSwitch cb_switch(this);

	//�ĵ����л�
	DocumentLockSwitch lock_switch;

	//���öԻ����ȡ�곡����
	DrillSiteLink ds_link;
	if(!UpdateDrillSiteDataFromDlg(AcDbObjectId::kNull, ds_link)) return;

	//����ʯ�ź�ú��ͼԪ
	if(RcuHelper::CreateDrillSite(pData1->objId, ds_link))
	{
		//��list1�в���һ��ʯ������
		InsertDrillSiteToListCtrl(m_list2, ds_link.getDataSource(), ds_link);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnDeleteDrillSiteCommand()
{
	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);
	if(row2 != LB_ERR)
	{
		ItemData* pData2 = ( ItemData* )m_list2.GetItemData(row2);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//ɾ���곡ͼԪ
		ArxEntityHelper::EraseObject2(pData2->objId, true);
		//ɾ��ѡ�����
		ListCtrlHelper::DeleteListCtrlItem(m_list2, row2);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnModifyDrillSiteCommand()
{
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	if(row1 == LB_ERR)
	{
		MessageBox(_T("��ָ�������ʯ�ź��ٽ����곡���!"));
		return;
	}

	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);
	if(row2 == LB_ERR)
	{
		MessageBox( _T( "��ѡ��һ���곡�������!" ) );
		return;
	}

	ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);
	ItemData* pData2 = (ItemData*)m_list2.GetItemData(row2);

	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//��ͼԪ����ȡ�곡����
	DrillSiteLink ds_link;
	if(!RcuHelper::GetDrillSiteData(pData2->objId, ds_link))
	{
		MessageBox(_T("��ȡ�곡����ʧ��!!!"));
		return;
	}

	//�л�controlbar����ʾ
	//ControlBarShowSwitch cb_switch(this);

	//���öԻ�������곡����
	if(UpdateDrillSiteDataFromDlg(pData2->objId, ds_link))
	{
		//��list1�в���һ��ʯ������
		ModifyDrillSiteToListCtrl(m_list2, row2, ds_link);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnHilightDrillSiteCommand()
{
	//ShowOrHideWindow show_hide(this);
	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);
	if(row2 != LB_ERR)
	{
		ItemData* pData2 = (ItemData*)m_list2.GetItemData(row2);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//����ѡ���곡ͼԪ
		ArxEntityHelper::SelectEntity(pData2->objId);

		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnBnClickedDesignClosePores()
{
	MessageBox(_T("�ݲ������տ����!"));
}

void RcuDesignDlg::OnBnClickedDesignOpenPores()
{
	int row1 = ListCtrlHelper::GetCurSelOfList(m_list);
	int row2 = ListCtrlHelper::GetCurSelOfList(m_list2);

	if(row1 == LB_ERR || row2 == LB_ERR)
	{
		MessageBox(_T("��ָ�������һ��ʯ�š��곡���ٽ���������!"));
		return;
	}

	ItemData* pData1 = (ItemData*)m_list.GetItemData(row1);
	ItemData* pData2 = (ItemData*)m_list2.GetItemData(row2);

	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//��ȡʯ������
	RockGateLink rg_link;
	if(!RcuHelper::ReadRockGateData(pData1->objId, rg_link)) return;

	//��ȡ�곡����
	DrillSiteLink ds_link;
	if(!RcuHelper::ReadDrillSiteData(pData2->objId, ds_link)) return;

	//��ʾ�����ƶԻ���
	if(UpdateOpenPoresFromDlg(pData2->objId, rg_link, ds_link))
	{
		//�����곡�б��е�����
		ModifyDrillSiteToListCtrl(m_list2, row2, ds_link);
		//cad���ڻ�ȡ����
		acedGetAcadFrame()->SetFocus();
	}
}

void RcuDesignDlg::OnBnClickedExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RcuDesignDlg::updateRockGateListCtrl(unsigned int op, const AcDbObjectId& rock_gate)
{
	if(rock_gate.isNull()) return;

	int row1 = ListCtrlHelper::SearchRowOfList(m_list, rock_gate);
	if(op == 0)
	{
		if(row1 == LB_ERR)
		{
			//����ʯ��
			addRockGate(rock_gate);
		}
		else
		{
			//�޸�ʯ��
			modifyRockGate(row1);
		}
	}
	else if(op == 1 && row1 != LB_ERR)
	{
		//ɾ��ʯ��
		delRockGate(row1);
	}
	else if(op == 2 && row1 != LB_ERR)
	{
		//�޸�ʯ��
		modifyRockGate(row1);
	}
}

void RcuDesignDlg::updateDrillSiteListCtrl(unsigned int op, const AcDbObjectId& drill_site)
{
	if(drill_site.isNull()) return;

	int row2 = ListCtrlHelper::SearchRowOfList(m_list2, drill_site);
	if(op == 0)
	{
		if(row2 == LB_ERR)
		{
			//�����곡
			addDrillSite(drill_site);
		}
		else
		{
			//�޸��곡
			modifyDrillSite(row2);
		}
	}
	else if(op == 1 && row2 != LB_ERR)
	{
		//ɾ���곡
		delDrillSite(row2);
	}
	else if(op == 2 && row2 != LB_ERR)
	{
		//�޸��곡
		modifyDrillSite(row2);
	}
}

LRESULT RcuDesignDlg::OnRcuAddMessage(WPARAM wParam, LPARAM lParam)
{
	ArxMsg* pMsg = (ArxMsg*)wParam;
	if(pMsg->clsName.CompareNoCase(_T("RockGate")) == 0)
	{
		updateRockGateListCtrl(0, pMsg->objId);
	}
	else if(pMsg->clsName.CompareNoCase(_T("DrillSite")) == 0)
	{
		updateDrillSiteListCtrl(0, pMsg->objId);
	}
	return 0;
} 

LRESULT RcuDesignDlg::OnRcuDelMessage(WPARAM wParam, LPARAM lParam)
{
	ArxMsg* pMsg = (ArxMsg*)wParam;
	if(pMsg->clsName.CompareNoCase(_T("RockGate")) == 0)
	{
		updateRockGateListCtrl(1, pMsg->objId);
	}
	else if(pMsg->clsName.CompareNoCase(_T("DrillSite")) == 0)
	{
		updateDrillSiteListCtrl(1, pMsg->objId);
	}
	return 0;
}

LRESULT RcuDesignDlg::OnRcuModifyMessage(WPARAM wParam, LPARAM lParam)
{
	ArxMsg* pMsg = (ArxMsg*)wParam;
	if(pMsg->clsName.CompareNoCase(_T("RockGate")) == 0)
	{
		updateRockGateListCtrl(2, pMsg->objId);
	}
	else if(pMsg->clsName.CompareNoCase(_T("DrillSite")) == 0)
	{
		updateDrillSiteListCtrl(2, pMsg->objId);
	}
	return 0;
}

LRESULT RcuDesignDlg::OnRcuUpdateMessage(WPARAM wParam, LPARAM lParam)
{
	//���½���
	updateUI();
	return 0;
}

void RcuDesignDlg::addRockGate(const AcDbObjectId& rock_gate)
{
	//�л��ĵ���
	DocumentLockSwitch lock_switch;

	//��ȡʯ������
	RockGateLink rg_link;
	if(!RcuHelper::ReadRockGateData(rock_gate, rg_link)) return;

	//��list1�в���һ��ʯ������
	InsertRockGateToListCtrl(m_list, rock_gate, rg_link);
}

void RcuDesignDlg::delRockGate(int row1)
{
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData( row1 );

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//ɾ��ͼԪ
		//ע:EraseObject2ʹ��open/closeɾ������Чʯ�ź͹�����ͼԪ
		//   ��EraseObject����ʹ�õ�������,��һ������Чɾ��!!!
		ArxEntityHelper::EraseObject2(pData1->objId, true);

		//ɾ��ѡ�����
		ListCtrlHelper::DeleteListCtrlItem(m_list, row1);
		ListCtrlHelper::ClearListCtrl(m_list2);
	}
}

void RcuDesignDlg::modifyRockGate(int row1)
{
	if(row1 != LB_ERR)
	{
		ItemData* pData1 = ( ItemData* )m_list.GetItemData(row1);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		RockGateLink rg_link;
		//��ȡʯ�Ź������������ݲ���䵽�Ի�����
		if(!RcuHelper::ReadRockGateData(pData1->objId, rg_link)) return;

		//�޸ĵ�ǰѡ��ʯ�ŵ�����
		ModifyRockGateToListCtrl(m_list, row1, rg_link);
	}
}

void RcuDesignDlg::addDrillSite(const AcDbObjectId& drill_site)
{
	//�ĵ����л�
	DocumentLockSwitch lock_switch;

	//���öԻ����ȡ�곡����
	DrillSiteLink ds_link;
	if(!RcuHelper::ReadDrillSiteData(drill_site, ds_link)) return;

	//��list2�в���һ���곡����
	InsertDrillSiteToListCtrl(m_list2, drill_site, ds_link);
}

void RcuDesignDlg::delDrillSite(int row2)
{
	if(row2 != LB_ERR)
	{
		ItemData* pData2 = ( ItemData* )m_list2.GetItemData(row2);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;
		//ɾ���곡ͼԪ
		ArxEntityHelper::EraseObject2(pData2->objId, true);
		//ɾ��ѡ�����
		ListCtrlHelper::DeleteListCtrlItem(m_list2, row2);
	}
}

void RcuDesignDlg::modifyDrillSite(int row2)
{
	if(row2 != LB_ERR)
	{
		ItemData* pData2 = ( ItemData* )m_list2.GetItemData(row2);

		//�ĵ����л�
		DocumentLockSwitch lock_switch;

		//��ȡ�곡����
		DrillSiteLink ds_link;
		if(!RcuHelper::ReadDrillSiteData(pData2->objId, ds_link)) return;

		//�޸ĵ�ǰѡ���곡������
		ModifyDrillSiteToListCtrl(m_list, row2, ds_link);
	}
}

void RcuDesignDlg::updateUI()
{
	//����곡�б��ʯ���б�
	ListCtrlHelper::ClearListCtrl(m_list);
	ListCtrlHelper::ClearListCtrl(m_list2);

	//�ĵ����л�
	DocumentLockSwitch lock_switch;

	AcStringArray fields;
	FieldHelper::GetAllFields(_T("RockGate"), fields);
	if(fields.isEmpty()) return;

	AcDbObjectIdArray objIds;
	RcuHelper::FindAllRockGates(objIds);
	if(objIds.isEmpty()) return;

	ListCtrlHelper::InsertDatasToListCtrl(m_list, fields, objIds);

	//ѡ�е�1��,����LVN_ITEMCHANGED��Ϣ
	m_list.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list.EnsureVisible(0, FALSE);
	m_list.SetFocus();
}
