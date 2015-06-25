#pragma once

#include "RcuAcUiBaseDlg.h"
#include "RcuDataLink.h"


class RcuEditOpenPoreDlg : public RcuAcUiBaseDlg
{
	DECLARE_DYNAMIC(RcuEditOpenPoreDlg)

public:
	RcuEditOpenPoreDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RcuEditOpenPoreDlg();

// �Ի�������
	enum { IDD = IDD_RCU_OPEN_PORES_DLG };

public:
	//�ⲿ���ñ���
	CString m_title;
	//�ⲿ�����곡λ���ı�
	CString m_pos;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_pore_num;
	double m_pore_gap;
	double m_pore_size;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
