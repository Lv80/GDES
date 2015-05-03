

// Reg.cpp: implementation of the CReg class.
//
//////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "Reg.h"
#include <ctime>
#include <cstring>
#include <cstdlib>

CReg::CReg()
{
	m_pMachineNum = new char[17];
	m_pRegNum = new char[17];
}

CReg::~CReg()
{
	delete m_pMachineNum;
	delete m_pRegNum;
}

CString CReg::GetRegNum( CString userID )
{
	CString strTmp;

	srand( ( unsigned )time( NULL ) );
	memset( m_pRegNum, '\0', 17 );

	// Ϊʲô��9λ,ע��IDΪ8λ,ѡ�����Ϊ1λ
	long tmpIntRegNum[ 9 ] = { '\0' };
	
	// ��ÿһλ�����������.
	for ( int i = 0; i < userID.GetLength(); i++ )
	{
		strTmp = userID.GetAt( i );
		tmpIntRegNum[ i ] = atoi(strTmp);
	}

	for ( int j = 0; j < userID.GetLength() - 1; j++ )
	{
		while ( true )
		{
			// ���������0~90;
			char tmpChar = rand() % 91;

			// ���������������.
			if ( tmpChar >= 48 && tmpChar <= 57 )
			{
				m_pRegNum[ userID.GetLength() + j - 1 ] = tmpChar;

				// �����Ӻ��ֵ������9.
				if ( ( ( tmpIntRegNum[ j ] + tmpChar ) - 57 ) > 0 )
				{
					m_pRegNum[ j ] = ( tmpIntRegNum[ j ] + tmpChar ) % 57 + 47;
				}
				else
				{
					m_pRegNum[ j ] = tmpIntRegNum[ j ] + tmpChar;
				}
				break;
			}
			else if ( tmpChar >= 65 && tmpChar <= 90 )   // ����Ǵ�д��ĸ
			{
				m_pRegNum[ userID.GetLength() + j - 1 ] = tmpChar;

				if ( ( ( tmpIntRegNum[ j ] + tmpChar ) - 90 ) > 0 )
				{
					m_pRegNum[ j ] = ( tmpIntRegNum[ j ] + tmpChar ) % 90 + 64;
				}
				else
				{
					m_pRegNum[ j ] = tmpIntRegNum[ j ] + tmpChar;
				}
				break;
			}
			else
			{
				continue;
			}
		}
	}

	// ����Ϊ��������(��16λ).
	// tmpIntRegNum[ 8 ]Ϊ��ѡ���ʹ�ô���������: 0��1��2��3
	m_pRegNum[ 15 ] = tmpIntRegNum[ 8 ] + ( ( m_pRegNum[ 13 ] + m_pRegNum[ 14 ] ) % 23 ) + 65;

	if ( ( ( tmpIntRegNum[ 7 ] + m_pRegNum[ 15 ] ) - 90 ) > 0 )
	{
		m_pRegNum[ 7 ] = ( tmpIntRegNum[ 7 ] + m_pRegNum[ 15 ] ) % 90 + 64;
	}
	else
	{
		m_pRegNum[ 7 ] = tmpIntRegNum[ 7 ] + m_pRegNum[ 15 ];
	}

	m_pRegNum[ 16 ] = '\0';
	
	strTmp = m_pRegNum;
	
	return strTmp;
}

CString CReg::DisPoseID( CString machineNum )
{
	CString strProcess;    // �澭���������û�ID

	strcpy( m_pMachineNum, machineNum );
	int i;
	for ( i = 0; i < machineNum.GetLength(); i++ )
	{
		// ����Ǵ�Сд��ĸ��������Ϊ��Ӧ������.
		// ��: a - 0 �� A - 0.
		if ( m_pMachineNum[ i ] >= 65 && m_pMachineNum[ i ] <= 90 )
		{
			m_pMachineNum[ i ] = ( ( m_pMachineNum[ i ] - 65 ) % 10 ) + 48;
		}
		else if ( m_pMachineNum[ i ] >= 97 && m_pMachineNum[ i ] <= 122 )
		{
			m_pMachineNum[ i ] = ( ( m_pMachineNum[ i ] - 97 ) % 10 ) + 48;
		}
		else  if ( m_pMachineNum[ i ] >= 48 && m_pMachineNum[ i ] <= 57 )
		{
			;  // ��������־Ͳ���
		}
		else   // ����Ǵ�Сд��ĸ����ľ�������0
		{
			m_pMachineNum[ i ] = 48;
		}
	}
	
	m_pMachineNum[ i + 1 ] = '\0';
	
	strProcess = m_pMachineNum;
	return strProcess;
}


int CReg::CmpReg(CString userID, CString userReg)
{
	long    nTmpUserID[9] = { '\0' };    // ������ֻ�����û�ID.
	int     nDate;                       // ���ѡ��Ĵ�������.

	CString strTmp;                    // ��ʱ����
	char    cmpTmp;                    // ��ʱ����

	strcpy( m_pMachineNum, userReg );

	for ( int i = 0; i < userID.GetLength(); i++ )
	{
		strTmp = userID.GetAt( i );
		nTmpUserID[ i ] = atoi(strTmp); 

		int l = userID.GetLength();
		// ������Ƚϵ�������.
		if ( m_pMachineNum[ userID.GetLength() + i ]  >= 48
			&&  m_pMachineNum[ userID.GetLength() + i ]  <= 57 )
		{
			if ( ( ( nTmpUserID[ i ] + m_pMachineNum[ userID.GetLength() + i ] ) 
				- 57 ) > 0 )
			{
				cmpTmp = ( nTmpUserID[ i ] + m_pMachineNum[ userID.GetLength() + i ] ) % 57 + 47;
			}
			else
			{
				cmpTmp = nTmpUserID[ i ] + m_pMachineNum[ userID.GetLength() + i ];
			}
		}

		// ������Ƚϵ��Ǵ�д��ĸ.
		else
		{
			if ( ( ( nTmpUserID[ i ] + m_pMachineNum[ userID.GetLength() + i ] ) 
				- 90 ) > 0 )
			{
				cmpTmp = ( nTmpUserID[ i ] + m_pMachineNum[ userID.GetLength() + i ] ) % 90 + 64;
			}
			else
			{
				cmpTmp = nTmpUserID[ i ] + m_pMachineNum[ userID.GetLength() + i ];
			}
			
		}

		if ( cmpTmp != m_pMachineNum[ i ] )
		{
			// ע�������.
			return 0;
		}
	}

	// ������ں��1��Ϊ�˷���.
	//nDate = m_pMachineNum[ 15 ] - 65 - ( ( m_pMachineNum[ 13 ] + 
	//	m_pMachineNum[ 14 ] ) % 23 ) + 1;
	//
	//// ����ʹ�ô���. 
	//switch ( nDate )
	//{
	//case 1:
	//	return 1;   // 30��
	//case 2:
	//	return 2;   // 60��
	//case 3:
	//	return 3;   // 90��
	//case 4:
	//	return 4;   // ����
	//}

	// ע��������,�����ڴ���,������������������Է��ֹ���.
	return 4;
}

int CReg::JmValue( int nValue ,int nSelect )
{
	nValue = nValue + nSelect;
	nValue = nValue ^ 111;

	return nValue;
}

int CReg::UnJmValue( int nJmValue, int nSelect ) 
{
	nJmValue = nJmValue ^ 111;
	nJmValue = nJmValue - nSelect;
	
	return nJmValue;    
}


