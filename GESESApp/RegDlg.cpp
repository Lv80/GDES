#include "RegDlg.h"

#include "Reg.h"
#include "HardWare.h"

RegDlg::RegDlg(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
	resize(300,120);
	QVBoxLayout *mainLayout = new QVBoxLayout;

	QGridLayout *upLayout = new QGridLayout;
	machineIdLabel = new QLabel(tr("machine"));
	upLayout->addWidget(machineIdLabel,0,0,1,1);

	m_regHelper = new RegHelper;
	machineIdEdit = new QLineEdit;

	CHardWare  hw;
	CReg       reg;
	DISKINFO   di;

	// ��ȡӲ����Ϣ
	if ( !hw.GetHDNum( &di ) )
	{
		hw.GetBiosNum( &di );
	}

	// ��Ӳ����ת��������ID
	machineID = reg.DisPoseID( di.szSystemInfo );

	machineIdEdit->setText(machineID);
	if (!machineIdEdit->text().isEmpty())
	{
		machineIdEdit->setReadOnly(true);
	}
	else
	{
		machineIdEdit->setReadOnly(false);
	}

	upLayout->addWidget(machineIdEdit,0,1,1,3);

	regIdLabel = new QLabel(tr("regId"));
	upLayout->addWidget(regIdLabel,1,0,1,1);

	regIdEdit = new QLineEdit;
	upLayout->addWidget(regIdEdit,1,1,1,3);

	QGridLayout *downLayout = new QGridLayout;
	getRegIdBtn = new QPushButton(tr("regist"));
	copyBtn = new QPushButton(tr("copyMachineCode"));
	copyBtn->setDisabled(false);

	downLayout->addWidget(getRegIdBtn,0,0,1,1);
	downLayout->addWidget(copyBtn,0,1,1,1);

	QVBoxLayout *msgLayout = new QVBoxLayout;
	QLabel *msgLabel = new QLabel(tr("please connect writer")+"\n"+tr("hunanhd@163.com"));
	msgLayout->addWidget(msgLabel);
	mainLayout->addLayout(msgLayout);

	mainLayout->addLayout(upLayout);
	mainLayout->addLayout(downLayout);

	connect(getRegIdBtn,SIGNAL(clicked()),this,SLOT(Regist()));
	connect(copyBtn,SIGNAL(clicked()),this,SLOT(copyMachineCode()));

	setLayout(mainLayout);
	setWindowTitle(tr("register"));
	regSucs = false;
}

RegDlg::~RegDlg()
{

}

void RegDlg::Regist()
{
	machineID.clear();
	regID.clear();
	regSucs = false;

	CReg          reg;
	CString       tmp;                           // �����ʱ����


	machineID = machineIdEdit->text(); 


	regID = regIdEdit->text();
	// �ж�ע�����Ƿ��Ѿ���������
	if ( regID.length() < 16 )
	{
		regID.clear();     // ��ձ���
		close();               // ����, ������
	}

	regID.toUpper();     // תΪ��д��ĸ

	// �Ƚ�ע�����Ƿ���ȷ
	m_nIndex = reg.CmpReg((CString) machineID.toStdString().c_str(), (CString)regID.toStdString().c_str() );

	// ���ע���벻��ȷ
	if ( !m_nIndex )
	{
		//Sleep( 3000 );         // ��ͣ�߳�3��
		MessageBox( NULL, "ע�������", "������ʾ",
			MB_OK | MB_ICONINFORMATION );

		//AfxMessageBox("xxxx");
		regSucs = false;
		
	}
	else
	{
		MessageBox( NULL, "ע��ɹ�", "��ʾ",
			MB_OK | MB_ICONINFORMATION );
		regSucs = true;
	}
	close();
}


void RegDlg::copyMachineCode()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(machineIdEdit->text());
	QMessageBox msg;
	msg.setWindowTitle(tr("tip"));
	msg.setText(tr("copy success")+ "\n"  + tr("hunanhd@163.com"));
	msg.exec();
	//copyBtn->setDisabled(true);
}