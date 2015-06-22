#pragma once

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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//ʯ���б�
	CListCtrl m_list;
	//�곡�б�
	CListCtrl m_list2;

	//������ť������Ϣ
	afx_msg void OnBnClickedExport();
	//ʯ���б����л�ʱ��������Ϣ
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	//ʯ���б�˫����Ϣ
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//ʯ���б��Ҽ���Ϣ
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//�곡�б�˫����Ϣ
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	//�곡�б��Ҽ���Ϣ
	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);

	//ʯ���б��Ҽ��˵�����Ϣ��Ӧ
	afx_msg void OnHilightRockGateCommand();
	afx_msg void OnModifyRockGateCommand();
	afx_msg void OnDeleteRockGateCommand();
	afx_msg void OnAddRockGateCommand();

	//�곡�б��Ҽ��˵�����Ϣ��Ӧ
	afx_msg void OnAddDrillSiteCommand();
	afx_msg void OnDeleteDrillSiteCommand();
	afx_msg void OnModifyDrillSiteCommand();
	afx_msg void OnHilightDrillSiteCommand();

	//�Ի����麯������
	virtual BOOL OnInitDialog();
	virtual void OnClosing();
	//ˢ�½���
	virtual void update();

private:
	//����ʯ���б�
	void updateRockGateListCtrl();
};
