#pragma once

#include<math.h>


double** RK4_main1(double** kor_pr, double h, int n)
{
	int p = 4;
	double k1, k2, k3, k4,s,Xn_h;

	//локальная погрешность в начальной точке = 0
	kor_pr[0][2] = 0;

	for (int i = 1; i < n; i++)	
	{
		Xn_h = kor_pr[i][0] + h / 2;

		kor_pr[i][0] = kor_pr[i][0] + h;
		k1 = (1/(1+pow(kor_pr[i][0],4)))*pow(kor_pr[i][1],2) +kor_pr[i][1] - pow(kor_pr[i][1], 3)*sin(10*kor_pr[i][0]);
		k2 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + (h / 2)*k1), 2) + (kor_pr[i][1] + (h / 2)*k1) - pow((kor_pr[i][1] + (h / 2)*k1), 3)*sin(10 * Xn_h);
		k3 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + (h / 2)*k2), 2) + (kor_pr[i][1] + (h / 2)*k2) - pow((kor_pr[i][1] + (h / 2)*k2), 3)*sin(10 * Xn_h);
		k4 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + h*k3), 2) + (kor_pr[i][1] + h*k3) - pow((kor_pr[i][1] + h*k3), 3)*sin(10 * Xn_h);
		kor_pr[i][1] = kor_pr[i][1] + (h / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

	}
	return kor_pr;
}

double** RK4_main2(double** kor_pr, double h, int n, double e)
{
	int p = 4, c1 = 0, c2 = 0;
	double k1, k2, k3, k4, s,Xn_h;
	for (int i = 1; i < n; i++)
	{
		//вычисляем Xn+1, Vn+1 с шагом h из Xn,Vn
		Xn_h = kor_pr[i][0] + h / 2;

		kor_pr[i][0] = kor_pr[i][0] + h;
		k1 = (1 / (1 + pow(kor_pr[i][0], 4)))*pow(kor_pr[i][1], 2) + kor_pr[i][1] - pow(kor_pr[i][1], 3)*sin(10 * kor_pr[i][0]);
		k2 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + (h / 2)*k1), 2) + (kor_pr[i][1] + (h / 2)*k1) - pow((kor_pr[i][1] + (h / 2)*k1), 3)*sin(10 * Xn_h);
		k3 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + (h / 2)*k2), 2) + (kor_pr[i][1] + (h / 2)*k2) - pow((kor_pr[i][1] + (h / 2)*k2), 3)*sin(10 * Xn_h);
		k4 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + h * k3), 2) + (kor_pr[i][1] + h * k3) - pow((kor_pr[i][1] + h * k3), 3)*sin(10 * Xn_h);
		kor_pr[i][1] = kor_pr[i][1] + (h / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

		//вычисляем Xn+1/2, Vn+1/2 с шагом h/2 из Xn,Vn
		double h_pr = h / 4;
		Xn_h = kor_pr[i][0] + h_pr;

		kor_pr[i][2] = kor_pr[i][0] + h_pr;
		
		//k1 такой же

		k2 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + h_pr*k1), 2) + (kor_pr[i][1] + h_pr*k1) - pow((kor_pr[i][1] + h_pr*k1), 3)*sin(10 * Xn_h);
		k3 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + h_pr*k2), 2) + (kor_pr[i][1] + h_pr*k2) - pow((kor_pr[i][1] + h_pr*k2), 3)*sin(10 * Xn_h);
		k4 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][1] + (h/2)* k3), 2) + (kor_pr[i][1] + (h/2) * k3) - pow((kor_pr[i][1] + (h/2) * k3), 3)*sin(10 * Xn_h);
		kor_pr[i][3] = kor_pr[i][1] + (h / 12)*(k1 + 2 * k2 + 2 * k3 + k4);  //тк идем с шагом h/2
	

		//вычисляем Xn+1, Vn+1 с шагом h/2 из Xn+1/2,Vn+1/2

		Xn_h = kor_pr[i][2] + h_pr;

		k1 = (1 / (1 + pow(kor_pr[i][2], 4)))*pow(kor_pr[i][3], 2) + kor_pr[i][1] - pow(kor_pr[i][3], 3)*sin(10 * kor_pr[i][2]);
		k2 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][3] + h_pr * k1), 2) + (kor_pr[i][3] + h_pr * k1) - pow((kor_pr[i][3] + h_pr * k1), 3)*sin(10 * Xn_h);
		k3 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][3] + h_pr * k2), 2) + (kor_pr[i][3] + h_pr * k2) - pow((kor_pr[i][3] + h_pr * k2), 3)*sin(10 * Xn_h);
		k4 = (1 / (1 + pow(Xn_h, 4)))*pow((kor_pr[i][3] + (h / 2)* k3), 2) + (kor_pr[i][3] + (h / 2) * k3) - pow((kor_pr[i][3] + (h / 2) * k3), 3)*sin(10 * Xn_h);
		kor_pr[i][4] = kor_pr[i][3] + (h / 12)*(k1 + 2 * k2 + 2 * k3 + k4);  //тк идем с шагом h/2

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
	return kor_pr;
}