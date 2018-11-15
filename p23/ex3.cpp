#include <functional>
#include <cmath>
#include <random>
#include <iostream>

using namespace std;

typedef double (*Function)(double);

double EvaluateIntFunction(
    Function Func, double A, double B, double C, double D, int NumSamples)
{
    int HitCount = 0;
    default_random_engine Generator;
    uniform_real_distribution<double> UniformX(A, B);

    double YMax = max(D, 0.0);
    double YMin = min(C, 0.0);

    uniform_real_distribution<double> UniformY(YMin, YMax);

    for (size_t I = 0; I < NumSamples; I++)
    {
        double X = UniformX(Generator);
        double Y = UniformY(Generator);

        if (Y > 0 && Y <= Func(X))
        {
            HitCount += 1;
        }
        else if (Y < 0 && Y >= Func(X))
        {
            HitCount -= 1;
        }
    }

    double Area = (B - A) * (YMax - YMin);

    return static_cast<double>(HitCount) /
           static_cast<double>(NumSamples) * Area;
}

double GroundTruthIntExp(double A, double B)
{
    return exp(B) - exp(A);
}

double GroundTruthIntSqrt(double A, double B)
{
    return 2.0 / 3.0 * (pow(B, 1.5) - pow(A, 1.5));
}

double GroundTruthIntSin(double A, double B)
{
    return -(cos(B) - cos(A));
}

int main(int argc, char const *argv[])
{
    for (double I = 1e6; I < 1e10; I *= 10)
    {
        cout << "I = " << I << endl;
        double IntExp =
            EvaluateIntFunction(exp, 1.0, 3.0, exp(1.0), exp(3.0), I);
        cout << "Exp," << IntExp << "," << GroundTruthIntExp(1.0, 3.0) << endl;
        double IntSqrt =
            EvaluateIntFunction(sqrt, 1.0, 3.0, sqrt(1.0), sqrt(3.0), I);
        cout << "Sqrt," << IntSqrt << "," << GroundTruthIntSqrt(1.0, 3.0) << endl;
        double IntSin =
            EvaluateIntFunction(sin, 1.0, 3.0, -1.0, 1.0, I);
        cout << "Sin," << IntSin << "," << GroundTruthIntSin(1.0, 3.0) << endl;
    }

    return 0;
}
