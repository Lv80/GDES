#pragma once
#include "GasBaseAcesDlg.h"
#include "afxcmn.h"
#include "CGridListCtrlGroups.h"
#include "afxwin.h"

class ResultDlg : public GasBaseAcesDlg
{
	DECLARE_DYNAMIC(ResultDlg)

public:
	ResultDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ResultDlg();

// �Ի�������
	enum { IDD = IDD_RESULT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CGridListCtrlGroups m_resultCtrlList;

	AcStringArray m_datas;		//��������
	IntArray m_retTrueIndxs;	//���н������ȷ�ı��к�
	CComboBox m_methodCombBox;	//���з�ʽ��ѡ��
	BOOL m_isTrue;			//���н�����Ƿ���ȷ
	CString m_objectName;	//���н��ѡ��Ĵʵ���
	CString m_descObjectName;	//ѡ������ʱ�����Ի������ݱ�����
	AcStringArray m_bookMks;
	BOOL m_isOthers;			//�ж��Ƿ�ѡ������ѡ��
	CString m_reasonsDesc;		//��������
public:
	void setItemDatas(const AcStringArray& datas);
	void setItems();
	void setTrueIndex(const IntArray& trueIndexs,const CString& txtSaveName,const CString& descObjectName);
	void setBookMarks(const AcStringArray& bookMks);

private:
	void InitListCtrl();
	void writeDatasToFile(CString& strConlusion,const CString& strMethod);
	void showReasonsDescDlg(int nIndex);

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickResultList(NMHDR *pNMHDR, LRESULT *pResult);
};
