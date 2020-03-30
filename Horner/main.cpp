#include <iostream>
#include <math.h>

using namespace std;

void evaluate()
{
	int n;
	cout << "Enter the polynomial degree: ";
	cin >> n;

	double * a = new double[n + 1];
	for (int i = n; i >= 0; i--)
	{
		cout << "Enter the coefficient of x^" << i << ": ";
		cin >> a[i];
	}

	double x;
	cout << "Enter argument of the polynomial: ";
	cin >> x;

	double value;
	value = a[n];
	for (int i = n - 1; i >= 0; i--)
		value = a[i] + value * x;

	cout << endl << "The polynomial value at " << x << " is " << value << " (Horner)";

	double iAmSlow = 0;
	for (int i = 0; i <= n; i++)
		iAmSlow += a[i] * pow(x, i);

	cout << endl << "The polynomial value at " << x << " is " << iAmSlow << " (Traditional)" << endl;
}

void estimateInterval()
{
	int n;
	cout << "Enter the polynomial degree: ";
	cin >> n;

	double * a = new double[n + 1];
	for (int i = n; i >= 0; i--)
	{
		cout << "Enter the coefficient of x^" << i << ": ";
		cin >> a[i];
	}

	if (a[n] < 0)
		for (int i = 0; i <= n; i++)
			a[i] *= -1;

	double * b = new double[n + 1];
	b[n] = a[n];
	double beta = 0;
	bool areNegatives;

	do
	{
		beta += 1;
		areNegatives = false;
		for (int i = n - 1; i >= 0; i--)
			b[i] = a[i] + b[i + 1] * beta;
		for (int i = 0; i <= n; i++)
			if (b[i] < 0)
				areNegatives = true;
	} while (areNegatives);

	for (int i = n - 1; i >= 0; i-=2)
		a[i] *= -1;

	double alpha = 0;

	do
	{
		alpha += 1;
		areNegatives = false;
		for (int i = n - 1; i >= 0; i--)
			b[i] = a[i] + b[i + 1] * alpha;
		for (int i = 0; i <= n; i++)
			if (b[i] < 0)
				areNegatives = true;
	} while (areNegatives);

	alpha *= -1;

	cout << endl << "The estimated interval of real solutions is (" << alpha << ", " << beta << ")" << endl;
}

double cosPart(int N, double x_0)
{
	if (!N)
		return 1;
	return cosPart(N - 1, x_0) * -pow(x_0, 2) / ((2 * N) * (2 * N - 1));
}

void taylorSeriesCosine()
{
	double x_0;
	cout << "Enter x_0: ";
	cin >> x_0;

	double acc;
	cout << "Enter wanted accuracy: ";
	cin >> acc;

	int N = 0;
	for (int i = 0; i < 1000; i++)
	{
		cout << i + 1 << ": " << cosPart(i, x_0) << endl;
		if (abs(cosPart(i, x_0)) < acc)
		{
			N = i - 1;
			break;
		}
	}

	double cosValue = 0;
	for (int i = 0; i <= N; i++)
		cosValue += cosPart(i, x_0);

	cout << endl << "Estimated value of cosine at " << x_0 << " is " << cosValue << endl;
}

int main() {

	taylorSeriesCosine();

	system("pause");
	return 0;
}