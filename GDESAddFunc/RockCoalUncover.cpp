#include "StdAfx.h"

#include <math.h>

#define PI 3.1415926535897932384626433832795
//����ת����
#define DegToRad(x) x*0.01745329251994329576923690768489
//����ת����
#define RadToDeg(x) x*57.295779513082320876798154814105

class RockGate
{
public:
	//���캯��
	RockGate() : origin(AcGePoint3d::kOrigin), beta(90), Dz(0) {}

	//���û�������
	void setOrigin(const AcGePoint3d& origin)
	{
		this->origin = origin;
	}
	//��ȡ��������
	AcGePoint3d getOrigin() const
	{
		return this->origin;
	}
	//����ú�����
	void setCoalParams(double alpha, double beta, double h)
	{
		this->alpha = alpha;
		this->beta = beta;
		this->h = h;
	}
	//��ȡú�����
	void getCoalParams(double& alpha, double& beta, double& h) const
	{
		alpha = this->alpha;
		beta = this->beta;
		h = this->h;
	}
	//����ʯ������������
	void setTunnelParams(double H, double W1, double W2)
	{
		this->H = H;
		this->W1 = W1;
		this->W2 = W2;
	}
	//��ȡʯ������������
	void getTunnelParams(double& H, double& W1, double& W2) const
	{
		H = this->H;
		W1 = this->W1;
		W2 = this->W2;
	}
	//����ʯ�Ų���
	void setRockGateParams(double f1, double f2, double d1, double d2)
	{
		this->f1 = f1;
		this->f2 = f2;
		this->d1 = d1;
		this->d2 = d2;
	}
	//��ȡʯ�Ų���
	void getRockGateParams(double& f1, double& f2, double& d1, double& d2) const
	{
		f1 = this->f1;
		f2 = this->f2;
		d1 = this->d1;
		d2 = this->d2;
	}
	//��С���������
	AcGePoint3d minNormalDistPoint() const
	{
		return origin + AcGeVector3d(W1*0.5, H, 0);
	}


	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	//�����úƽ�淽��
	void beginCoalSurface(AcGePlane& plane)
	{
		coalSurface(plane, 0);
	}
	//����ֹúƽ�淽��
	void endCoalSurface(AcGePlane& plane)
	{
		//��ú�����ú�����ֹú��
		coalSurface(plane, h);
	}

private:
	//��С����
	double minNormalDist() const
	{
		using namespace std;
		//����F��(��С�������ú��������)
		return S1*sin(DegToRad(beta));
	}
	//���ֻ����ʯ��ˮƽ����delta����alpha(ú�����)
	double getDelta() const
	{
		return this->alpha;
	}

	void coalSurface(AcGePlane& plane, double h)
	{
		using namespace std;
		double Lf = minNormalDist() + h;
		double D = Lf*sqrt(1+1.0/tan(DegToRad(getDelta())));
		D += Dz*cos(DegToRad(beta));
		D += H/tan(DegToRad(beta));
		D += W1*-0.5*sin(DegToRad(beta));

		double A = sin(DegToRad(beta));
		double B = -1.0/tan(DegToRad(getDelta()));
		double C = -1.0*cos(DegToRad(beta));

		//����ƽ�����
		plane.set(A, B, C, D);
	}

private:
	AcGePoint3d origin; // ʯ����������²����ĵ����ʵ����
	double Dz;          // ʯ�Ŷ����z����(Ĭ��Ϊ0)

	double alpha; // ú�����
	double beta; // ʯ��������ú������ļн�
	double h;    // ú����
	double H;    // ʯ������߶�
	double W1, W2; // ʯ��������(W1��W2Ϊ��������ϡ��µף����������ʱW1 = W2��ʾ�����)
	double S1; // ʯ�����߾�ú�����
	double f1; // ʯ�Ž�ú�������Ͽؾ���
	double f2; // ʯ�Ž�ú�������¿ؾ���
	double d1; // ʯ�Ž�ú��������ؾ���
	double d2; // ʯ�Ž�ú�������ҿؾ���
};
