#include "stdafx.h"
#include <fstream>
// ��Ҫ����<fstream>����ʹ��
#include "AcFStream.h"

CString GetAppPathDir()
{
	TCHAR szModulePath[_MAX_PATH];
	GetModuleFileName( _hdllInstance, szModulePath, _MAX_PATH );

	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	_tsplitpath( szModulePath, drive, dir, NULL, NULL );

	TCHAR szPath[_MAX_PATH] = {0};
	_tmakepath( szPath, drive, dir, NULL, NULL );

	return CString( szPath );
}

CString BuildPath( const CString& dir, const CString& fileName )
{
	CString path;
	path.Format( _T( "%s%s" ), dir, fileName );
	return path;
}

CString ReadAlpha(CString chimType, CString diam)
{
	CString dataDirName = _T( "Datas\\" );
	CString fileName;
	if (_T("������Ͳ") == chimType)//������Ͳ
	{
		fileName =BuildPath ( BuildPath( GetAppPathDir(), dataDirName ),_T( "����ϵͳ-������Ͳ-ֱ��.txt" ) );
	}

	else//Ĭ��Ϊ������Ͳ
	{
		fileName =BuildPath ( BuildPath( GetAppPathDir(), dataDirName ),_T( "����ϵͳ-������Ͳ-ֱ��.txt" ) );
	}

	AcIfstream inFile( fileName );
	if( !inFile ) return _T("��ȡʧ��");
	
	CString alphaRet;
	while( !inFile.eof() )
	{
		ACHAR diamater[_MAX_PATH], alpha[_MAX_PATH];
		inFile >> diamater >> alpha;
		if(inFile.fail()) break;

		CString strDiameter;
		strDiameter.Format(_T("%s"),diamater);
		if(diam == strDiameter)
		{
			//acutPrintf(_T("\n%s\t%s"), diamater, alpha);
			alphaRet.Format(_T("%s"),alpha);
			break;
		}
	}

	if (alphaRet.IsEmpty())
	{
		alphaRet = _T("���ݿ��޸�ֱ��");
	}
	inFile.close();
	return alphaRet;

}

CString ReadIntStringDatas(int intData,CString typeName)
{
	//CString dataDirName = _T( "Datas\\" );
	//CString fileName =BuildPath ( BuildPath( GetAppPathDir(), dataDirName ),_T( "����ϵͳ-�ַ���-�����б� .txt" ) );
	//
	//AcIfstream inFile( fileName );
	//if( !inFile ) 
	//{
	//	acutPrintf(_T("\n�ļ���ʧ��"));
	//	return _T("�ļ���ȡʧ��");
	//}

	CString strData;
	//while( !inFile.eof() )
	//{
	//	ACHAR cType[_MAX_PATH],cIntData[_MAX_PATH], cStrWay[_MAX_PATH];
	//	inFile >> cType >> cIntData >> cStrWay;

	//	CString strType;
	//	strType.Format(_T("%s"),cType);
	//	//acutPrintf(_T("\n%s\t%s"), strType, typeName);

	//	if(intData == _ttoi(cIntData) && strType == typeName)
	//	{
	//		//acutPrintf(_T("\n%s\t%s"), cIntData, cStrWay);
	//		strData.Format(_T("%s"),cStrWay);
	//		break;
	//	}
	//}
	//inFile.close();
	return strData;
}

int ReadStringIntDatas(CString strData,CString typeName)
{
	//CString dataDirName = _T( "Datas\\" );
	//CString fileName =BuildPath ( BuildPath( GetAppPathDir(), dataDirName ),_T( "����ϵͳ-�ַ���-�����б� .txt" ) );

	//AcIfstream inFile( fileName );
	//if( !inFile ) 
	//{
	//	acutPrintf(_T("\n�ļ���ʧ��"));
	//	return 0;
	//}

	int intData = 0;
	//while( !inFile.eof() )
	//{
	//	ACHAR cType[_MAX_PATH],cIntData[_MAX_PATH], cStrData[_MAX_PATH];
	//	inFile >> cType >> cIntData >> cStrData;

	//	CString strType;
	//	strType.Format(_T("%s"),cType);
	//	//acutPrintf(_T("\n%s\t%s"), strType, typeName);
	//	
	//	CString cStrToStr;
	//	cStrToStr.Format(_T("%s"),cStrData);
	//	if(strData == cStrToStr && strType == typeName)
	//	{
	//		//acutPrintf(_T("\n%s\t%s"), cIntData, cStrData);
	//		intData = _ttoi(cIntData);
	//		break;
	//	}
	//}
	//inFile.close();
	return intData;
}

