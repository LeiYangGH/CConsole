#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void read_input(double *g1, double *g2, double  *g3,
	double *h1, double  *h2, double *h3,
	double *k1, double  *k2, double *k3)
{
	//sample input : 2 3 4 5 6 4 7 8 9
	printf("please input a1 a2 a3 b1 b2 b3 c1 c2 c3 : \n");
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", g1, g2, g3, h1, h2, h3, k1, k2, k3);
}


double vector_magnitude(double g1, double g2, double  g3)
{
	return  sqrt(g1 * g1 + g2 * g2 + g3 * g3);
}

void cross_product(double g1, double g2, double  g3,
	double h1, double  h2, double h3,
	double *k1, double  *k2, double *k3)
{
	*k1 = g2 * h3 - g3 * h2;
	*k2 = -(g1 * h3 - g3 * h1);
	*k3 = (g1 * h2 - g2 * h1);
}

double dot_product(double g1, double g2, double  g3,
	double h1, double  h2, double h3)
{
	return g1 * h1 + g2 * h2 + g3 * h3;
}

double area_parallelogram(double g1, double g2, double  g3,
	double h1, double  h2, double h3)
{
	double k1, k2, k3;
	cross_product(g1, g2, g3, h1, h2, h3, &k1, &k2, &k3);
	return vector_magnitude(k1, k2, k3);
}

double volumn_parallelepiped(double g1, double g2, double  g3,
	double h1, double  h2, double h3,
	double k1, double  k2, double k3)
{
	double x, y, z;
	cross_product(g1, g2, g3, h1, h2, h3, &x, &y, &z);
	double dot = dot_product(g1, g2, g3, x, y, z);
	return	dot >= 0 ? dot : -dot;
}

void print_output(double g1, double g2, double  g3,
	double h1, double  h2, double h3,
	double k1, double  k2, double k3,
	double area, double volumn)
{
	printf("vector a=(%lf,%lf,%lf)\n", g1, g2, g3);
	printf("vector b=(%lf,%lf,%lf)\n", h1, h2, h3);
	printf("vector c=(%lf,%lf,%lf)\n", k1, k2, k3);
	printf("area = %lf\n", area);
	printf("volumn = %lf\n", volumn);
}

int main()
{
	double g1, g2, g3,
		h1, h2, h3,
		k1, k2, k3,
		area, volumn;
	read_input(&g1, &g2, &g3, &h1, &h2, &h3, &k1, &k2, &k3);
	area = area_parallelogram(g1, g2, g3, h1, h2, h3);
	volumn = volumn_parallelepiped(g1, g2, g3, h1, h2, h3, k1, k2, k3);
	print_output(g1, g2, g3, h1, h2, h3, k1, k2, k3, area, volumn);
	system("pause");
	return 0;
}