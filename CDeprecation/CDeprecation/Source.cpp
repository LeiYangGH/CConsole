#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main()
{
	double S = 3, C = 10, d = 0.3;//Ê¾ÀýÊý¾Ý
	int year;
	puts("Enter the original cost and deprecation rate:");
	scanf("%lf%lf", &C, &d);
	printf("%lf\t%lf\n", C, d);

	puts("Enter the book value at the end of the useful life of an asset:");
	scanf("%lf", &S);
	printf("%lf\n", S);

	year = log(S / C) / log(1 - d);
	printf("The useful life of the asset is: %d years\n", year);

	system("pause");
	return 0;
}