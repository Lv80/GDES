#pragma once
#include "Resource.h"
#include "../ARX_ReportHelper/GasBaseAcesDlg.h"
#include "CGridListCtrlEx/CGridListCtrlGroups.h"
#include "PreGas_DataModel.h"

#include "afxcmn.h"

class PreGasDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(PreGasDlg)

public:
	PreGasDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PreGasDlg();

// �Ի�������
	enum { IDD = IDD_OUTPRE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	// �˶�������ú��������˹����
	CString m_preMaxGas;
	// ��ɺ������ͻҪ��Ĳ�����˹����
	CString m_leafGas;
	// �󾮻ز���
	CString m_mineReRate;
	// ����ʵ��Ԥ����˹��
	CString m_forGas;
	// �ڽ����Χ����˹����ϵ��
	CString m_gasY;
	// �󾮾����úϵ��
	CString m_TTJ;
	// ��������
	CString m_faceNum;

	CString m_ret;

	CGridListCtrlGroups m_mineFaceList;
	PreGas_DataModel m_dataModel;
	vector<PreGas_DataRecord> m_records;

private:
	void OnInitList();

public:
	afx_msg void OnEnKillfocusFaceNumEdit();
	afx_msg void OnBnClickedOk();
};
