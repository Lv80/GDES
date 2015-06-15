#pragma once

#include "acui.h"
#include "resource.h"
#include "DockBarChildDlg.h"

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
	CListCtrl m_list;
	//�����ť��Ϣ
	afx_msg void OnBnClickedExport();
	//listctrl˫����Ϣ
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//listctrl�Ҽ���Ϣ(���Ե����˵������޷���Ӧ�˵���Ϣ)
	//��Ϊcad��������������ͼ�����ģ̬�Ի���Ľ���(WM_ACAD_KEEPFOCUS)
	//����Ϣӳ����ʱ�����Ҽ���Ϣ
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//Ŀǰ��Щ�˵����޷���Ӧ��ģ̬�Ի������Ϣ
	//�Ա�����Ϊ�Ժ�ѧϰ��
	afx_msg void OnHilightCommand();
	afx_msg void OnModifyCommand();
	afx_msg void OnDeleteCommand();
	afx_msg void OnAddCommand();

	virtual BOOL OnInitDialog();
	virtual void OnClosing();
};
