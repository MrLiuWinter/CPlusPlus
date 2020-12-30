#include<iostream>
using namespace std;
double exp2(double a, int n) {
	if (a == 0) return 0;
	if (n == 0) return 1;
	else {
		if (n % 2)
			return a * exp2(a, n / 2) * exp2(a, n / 2);
		else
		{
			return exp2(a, n / 2) * exp2(a, n / 2);
		}
	}
}
double exp(double a, int n) {
	int i;
	double b, s = 1.0;
	i = n; b = a;
	while (i > 0) {
		if (i % 2) s *= b;
		i /= 2; b *= b;
	}
	return s;
}
int main() {
	double x=2, y=2;
	int n = 10;
	x = exp(x, n);
	y = exp2(y, n);
	printf("%f,%f\n", x, y);
	return 0;
}