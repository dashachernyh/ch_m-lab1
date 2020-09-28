#pragma once
#include<math.h>


double** RK4_test1(double** kor_pr,double h, int n )
{
	int p = 4;
	double k1, k2, k3, k4,s;

	/*kor_pr = new double* [n];
	for (int i = 0; i < n; i++)
		kor_pr[i] = new double[3];*/

	//локальная погрешность в начальной точке = 0
	kor_pr[0][2]=0;
	
	for (int i = 1; i < n; i++)
	{
		kor_pr[i][0] = kor_pr[i][0] + h;
		k1 = -kor_pr[i][1] / 2;
		k2 = -(kor_pr[i][1] + (h / 2)*k1) / 2;
		k3= -(kor_pr[i][1] + (h / 2)*k2) / 2;
		k4= -(kor_pr[i][1] + h *k3) / 2;
		kor_pr[i][1] = kor_pr[i][1] + (h / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

	}
	return kor_pr;
}

double** RK4_test2(double** kor_pr, double h, int n, double e)
{
	int p = 4,c1=0,c2=0;
	double k1, k2, k3, k4,s;

	//локальная погрешность в начальной точке = 0
	kor_pr[0][5] = 0;

	for (int i = 1; i < n; i++)
	{
		//вычисляем Xn+1, Vn+1 с шагом h из Xn,Vn
		kor_pr[i][0] = kor_pr[i][0] + h;
		k1 = -kor_pr[i][1] / 2;
		k2 = -(kor_pr[i][1] + (h / 2)*k1) / 2;
		k3 = -(kor_pr[i][1] + (h / 2)*k2) / 2;
		k4 = -(kor_pr[i][1] + h * k3) / 2;
		kor_pr[i][1] = kor_pr[i][1] + (h / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

		//вычисляем Xn+1/2, Vn+1/2 с шагом h/2 из Xn,Vn
		double h_pr = h / 2;
		kor_pr[i][2] = kor_pr[i][0] + h_pr;
		k1 = -kor_pr[i][1] / 2;
		k2 = -(kor_pr[i][1] + (h_pr / 2)*k1) / 2;
		k3 = -(kor_pr[i][1] + (h_pr / 2)*k2) / 2;
		k4 = -(kor_pr[i][1] + h_pr * k3) / 2;
		kor_pr[i][3] = kor_pr[i][1] + (h_pr / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

		//вычисляем Xn+1, Vn+1 с шагом h/2 из Xn+1/2,Vn+1/2
		k1 = -kor_pr[i][3] / 2;
		k2 = -(kor_pr[i][3] + (h_pr / 2)*k1) / 2;
		k3 = -(kor_pr[i][3] + (h_pr / 2)*k2) / 2;
		k4 = -(kor_pr[i][3] + h_pr * k3) / 2;
		kor_pr[i][4] = kor_pr[i][3] + (h_pr / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

		s = (kor_pr[i][4] - kor_pr[i][1]) / (pow(2, p) - 1);

		if (e / (pow(2, p) - 1) > fabs(s))
		{
			h = 2 * h;
			c2++;
		}
		if (fabs(s) > e)
		{
			i = i - 1;
			h = h / 2;
			c1++;
		}

		//локальная погрешность En+1
		kor_pr[i][5] = s * pow(2, p);
		
	}
	kor_pr[0][2] = c1;
	kor_pr[0][3] = c2;
	return kor_pr;
}

