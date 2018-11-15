#include <cmath>
#include <random>
#include <iostream>

using namespace std;

const double C_PI = 3.141592653589793238463;

double Function(double X)
{
    return sqrt(1 - pow(X, 2));
}

double EvaluatePI(int NumSamples)
{
    int HitCount = 0;

    default_random_engine Generator;
    uniform_real_distribution<double> Uniform(0.0, 1.0);

    for (size_t i = 0; i < NumSamples; i++)
    {
        double X = Uniform(Generator);
        double Y = Uniform(Generator);

        if (Y <= Function(X))
        {
            HitCount += 1;
        }
    }

    return 4.0 * HitCount / NumSamples;
}

int main(int argc, char const *argv[])
{

    for (double I = 1e6; I < 1e10; I *= 10)
    {
        double PI = EvaluatePI(I);
        cout << I << "," << PI << "," << fabs(C_PI - PI) << endl;
    }

    return 0;
}
