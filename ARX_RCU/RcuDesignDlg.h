#pragma once

#include "RcuAcUiBaseDlg.h"
#include "DockBarChildDlg.h"

//ʯ�Ž�ú������Ի���
class RcuDesignDlg : public DockBarChildDlg
{
	DECLARE_DYNAMIC(RcuDesignDlg)

public:
	RcuDesignDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuDesignDlg();

// �Ի�������
	enum { IDD = IDD_RCU_DESIGN_DLG };

private:
	void initRockGateListCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CListCtrl m_list2;

	//�����ť��Ϣ
	afx_msg void OnBnClickedExport();
	//�б�ѡ�е����л�ʱ������Ϣ
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	//listctrl˫����Ϣ
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//listctrl�Ҽ���Ϣ(���Ե����˵������޷���Ӧ�˵���Ϣ)
	//��Ϊcad��������������ͼ�����ģ̬�Ի���Ľ���(WM_ACAD_KEEPFOCUS)
	//����Ϣӳ����ʱ�����Ҽ���Ϣ
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//listrctrl˫����Ϣ
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	//listrctrl�Ҽ���Ϣ
	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);

	//�˵�����Ϣ��Ӧ
	afx_msg void OnAddDrillSiteCommand();
	afx_msg void OnDeleteDrillSiteCommand();
	afx_msg void OnModifyDrillSiteCommand();
	afx_msg void OnHilightDrillSiteCommand();

	//�˵�����Ϣ��Ӧ
	afx_msg void OnHilightRockGateCommand();
	afx_msg void OnModifyRockGateCommand();
	afx_msg void OnDeleteRockGateCommand();
	afx_msg void OnAddRockGateCommand();

	//�麯������
	virtual BOOL OnInitDialog();
	virtual void OnClosing();
};
