// Reg.h: interface for the CReg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REG_H__DFCE3DF8_5F9B_4DF4_8340_268D3305E2D5__INCLUDED_)
#define AFX_REG_H__DFCE3DF8_5F9B_4DF4_8340_268D3305E2D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ���������ʵ��ID�ŵ����ֻ���ע����Ĳ������Ƚ�ע�����Ƿ���ȷ.


class CReg  
{
public:
	CReg();
	virtual ~CReg();

public:
	int CmpReg( CString userID, CString userReg );   // ��Чע�����Ƿ���ȷ
	int JmValue(int nValue ,int nSelect);            // ����
	int UnJmValue(int nJmValue, int nValue);         // ����
	CString DisPoseID( CString machineNum );         // ���ַ�IDת��������ID
	CString GetRegNum( CString userID );             // ͨ��Ӳ��ID��Bios��ȡע����.

private:
	char *m_pMachineNum;
	char *m_pRegNum;
};

#endif // !defined(AFX_REG_H__DFCE3DF8_5F9B_4DF4_8340_268D3305E2D5__INCLUDED_)
