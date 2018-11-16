#define _USE_MATH_DEFINES
#include <cmath>
#include <unordered_set>
#include <random>
#include <iostream>
#include <chrono>
#include <set>

using namespace std;
using namespace std::chrono;

int SetCount(int N)
{
    int K = 0;
    unordered_set<int> S;

    unsigned Seed = system_clock::now().time_since_epoch().count();
    default_random_engine Generator(Seed);
    uniform_int_distribution<int> Uniform(1, N);

    int A = Uniform(Generator);

    do
    {
        K += 1;
        S.insert(A);
        A = Uniform(Generator);
    } while (S.find(A) == S.end());

    return K;
}

int main(int argc, char const *argv[])
{
    const int Repeat = 10000;

    for (int I = 10; I < 1000000; I *= 10)
    {
        int K = 0;
        for (int J = 0; J < Repeat; J++)
        {
            K += SetCount(I);
        }
        K /= Repeat;
        double N = 2.0 * pow(K, 2) / M_PI;
        cout << I << "," << N << "," << fabs(N - I) / I << endl;
    }

    return 0;
}
