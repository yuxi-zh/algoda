#include <iostream>
#include <exception>
#include <random>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct List
{
    int *Val;
    int *Ptr;
    int Head;
    int Size;
    int Capacity;

    List(int N)
    {
        Val = new int[N];
        Ptr = new int[N];
        Head = -1;
        Size = 0;
        Capacity = N;
    }

    ~List()
    {
        delete[] Val;
        delete[] Ptr;
    }

    void Fullfill()
    {
        default_random_engine Generator;
        uniform_int_distribution<int> Uniform(1, Capacity);

        for (int I = 0; I < Capacity; I++)
        {
            Insert(Uniform(Generator));
        }
    }

    void Insert(int Value)
    {
        if (Size == Capacity)
        {
            throw new runtime_error("No Space");
        }

        Val[Size] = Value;

        int I = Head, J = -1;
        while (Value > Val[I])
        {
            J = I;
            I = Ptr[I];
        }

        if (J != -1)
        {
            Ptr[Size] = Ptr[J];
            Ptr[J] = Size;
        }
        else
        {
            Ptr[Size] = Head;
            Head = Size;
        }

        Size += 1;
    }

    int Search(int Value, int PtrIdx)
    {
        while (Value > Val[PtrIdx])
        {
            PtrIdx = Ptr[PtrIdx];
        }
        return PtrIdx;
    }

    int A(int X)
    {
        return Search(X, Head);
    }

    int B(int X)
    {
        int I = Head;
        int Max = Val[I];
        int Cnt = (int)ceil(sqrt(Size));

        for (int J = 0; J < Cnt; J++)
        {
            int Y = Val[J];
            if (Y > Max && Y <= X)
            {
                I = J;
                Max = Y;
            }
        }

        return Search(X, I);
    }

    int C(int X)
    {
        default_random_engine Generator;
        uniform_int_distribution<int> Uniform(0, Size - 1);

        int I = Head;
        int Max = numeric_limits<int>::min();
        int Cnt = (int)ceil(sqrt(Size));

        for (int J = 0; J < Cnt; J++)
        {
            int K = Uniform(Generator);
            int Y = Val[K];
            if (Y > Max && Y <= X)
            {
                I = K;
                Max = Y;
            }
        }

        return Search(X, I);
    }

    int D(int X)
    {
        default_random_engine Generator;
        uniform_int_distribution<int> Uniform(0, Size - 1);

        int I = Uniform(Generator);
        int Y = Val[I];

        if (X < Y)
        {
            I = Search(X, Head);
        }
        else if (X > Y)
        {
            I = Search(X, Ptr[I]);
        }

        return X;
    }
};

double Timing(function<void(void)> target)
{
    const int Repeat = 100;
    auto Begin = high_resolution_clock::now();
    for (int I = 0; I < Repeat; I++)
    {
        target();
    }
    auto End = high_resolution_clock::now();
    return duration_cast<duration<double>>(End - Begin).count() / Repeat;
}

int main(int argc, char const *argv[])
{
    for (int N = 10; N < 1e10; N *= 10)
    {
        List TestList(N);
        TestList.Fullfill();

        default_random_engine Generator;
        uniform_int_distribution<int> Uniform(1, N);

        int X = Uniform(Generator);

        cout << Timing([&]() { TestList.A(X); }) << ",";
        cout << Timing([&]() { TestList.B(X); }) << ",";
        cout << Timing([&]() { TestList.C(X); }) << ",";
        cout << Timing([&]() { TestList.D(X); }) << endl;
    }
    return 0;
}