#pragma once

#include <math.h>

#define PI 3.1415926535897932384626433832795
//����ת����
#define DegToRad(x) x*0.01745329251994329576923690768489
//����ת����
#define RadToDeg(x) x*57.295779513082320876798154814105
//ƽ��
#define square(x)  x*x
//����
#define cot(x) 1.0/tan(x)

//��һ���򻯰��ʯ�Ž�ú������
//ע:�Ƕ�Ĭ��ʹ�û���
class Rcu2
{
public:
	//���캯��
	Rcu2() : beta(PI*0.5) {}

	//����ú�����
	void setCoalSurf(double alpha, double thick)
	{
		this->alpha = alpha;
		//this->beta = beta;
		this->thick = thick;
	}
	//����ʯ������������
	void setRockGate1(double height, double width)
	{
		this->height = height;
		this->width = width;
	}
	//����ʯ�ŵ��������Ұﱣ�����
	void setRockGate2(double f1, double f2, double d1, double d2)
	{
		this->f1 = f1;
		this->f2 = f2;
		this->d1 = d1;
		this->d2 = d2;
	}
	//����ʯ�ž�ú�������С����
	void setRockGate3(double minDist)
	{
		this->minDist = minDist;
	}
	//�������ֱ��
	void setDrillDiameter(double d0)
	{
		this->d0 = d0;
	}

	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	/**
	 * ����ú�����ͶӰ��Ⱥ͸߶�Ҳ���ǳ�ɷ�Χ��ˮƽͶӰ.
	 * �������Ǽ���ӭͷ��ú��������Ǵ�ֱ��
	 * ͶӰ�Ŀ�ȵ������ұ�������������Ŀ��
	 * ͶӰ�߶���Ҫ����ͶӰ����
	 */
	void drillExtent(double& Lw, double& Lh)
	{
		//ͶӰ���
		Lw = width + d1 + d2;
		//ͶӰ�߶�
		Lh = abs((height + f1 + f2)*cot(alpha));
	}

	//ú����ĳ�ɷ�Χ�е�
	bool drillExtentCenter(AcGePoint3d& cnt)
	{
		//����úƽ�淽��
		AcGePlane plane1, plane2;
		coalSurface(plane1, plane2);

		//ͶӰ��Χ�����ĵ�����
		//��������ϰ�����°�Խǵ�,��2����е㼴Ϊ���ε����ĵ�
		AcGePoint3d left_top(-0.5*width-d1, 0, height+f1);
		AcGePoint3d right_bottom(0.5*width+d2, 0, -1*f2);
		AcGeRay3d lt_ray(left_top, AcGeVector3d::kYAxis);
		AcGeRay3d rb_ray(right_bottom, AcGeVector3d::kYAxis);

		//����������ƽ��Ľ���
		AcGePoint3d p1, p2;
		if(Adesk::kTrue != plane1.intersectWith(lt_ray, p1)) return false;
		if(Adesk::kTrue != plane1.intersectWith(rb_ray, p2)) return false;

		//2��������е㼴Ϊ���ĵ�
		cnt = p1 + 0.5*(p2-p1);
		//��ˮƽ��ͶӰ
		cnt.z = 0;
		
		return true;
	}

	//��׸��������
	void drillNumber(double Lw, double Lh, int& N1, int& N2, double& e1, double& e2)
	{
		N1 = int(Lw/d0)+2;
		N2 = int(Lh/d0)+2;
		e1 = Lw/(N1-1);
		e2 = Lh/(N2-1);
	}

private:
	//����úƽ�淽��(��ú��ֹú)
	void coalSurface(AcGePlane& plane1, AcGePlane& plane2)
	{
		//ӭͷú������߾���
		double L = minDist/sin(alpha);
		//ӭͷ������ú��Ľ���
		AcGePoint3d pt(0, L, 0);

		//����ƽ��ķ�����
		AcGeVector3d v(-AcGeVector3d::kYAxis);
		v.rotateBy(PI*0.5 - alpha, AcGeVector3d::kXAxis);

		//��ƽ���ϵĵ�ͷ�����ȷ��һ��ƽ��
		plane1.set(pt, v);
		plane2.set(pt - v*thick, v);
	}

private:
	double alpha;    // ú�����
	double beta;     // ʯ��������ú������ļн�(ʼ����90��)
	double thick;    // ú����

	double height;    // ʯ������߶�
	double width;     // ʯ��������(����ʯ��Ϊ�������)
	
	double minDist;     // ʯ�ž���ú�����С����
	double f1; // ʯ�Ž�ú�������Ͽؾ���
	double f2; // ʯ�Ž�ú�������¿ؾ���
	double d1; // ʯ�Ž�ú��������ؾ���
	double d2; // ʯ�Ž�ú�������ҿؾ���

	double d0;     // ���жѹֱ��
};
