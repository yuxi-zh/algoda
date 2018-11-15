#include <iostream>
#include <cmath>

using namespace std;

double Factorial(int N)
{
    double Result = 1.0;
    for (int I = 1; I <= N; I++)
    {
        Result *= I;
    }
    return Result;
}

double SetRepeat(double N)
{
    double Sum = 0;
    double NoRepeatPrev = 1;

    for (double K = 2; K <= N + 1; K++)
    {
        Sum += K * (K - 1) * NoRepeatPrev / N;
        NoRepeatPrev *= (1.0 - (K - 1.0) / N);
    }

    return Sum;
}

int main(int argc, char const *argv[])
{
    const double beta = sqrt(M_PI_2);

    for (double I = 10; I < 1e9; I *= 10)
    {
        double Exception = SetRepeat(I);
        cout << Exception << "," << beta * sqrt(I) << endl;
    }
    return 0;
}
