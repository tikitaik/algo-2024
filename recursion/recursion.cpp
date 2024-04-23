#include <iostream>

int factorial(unsigned long long int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial (n - 1);
    }
}

int fib (int n) {
    if (n <= 1) {
        return n;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }
}

int arithSeries (int start, int diff, int n) {
    if (n == 0) {
        return start;
    }
    else {
        return arithSeries(start + diff * (n - 1), diff, n - 1);
    }
}

int geoSeries (int a, float r, int n) {
    if (n <= 1) {
        return a;
    }
    else {
        return a + geoSeries(r * a, r, n - 1);
    }
}

// f(n) = a^n, a > 0 e R
// no maths library
float aToPowOfN(float a, int n) {
    if (n == 1) {
        return a;
    }
    else {
        return aToPowOfN(a, n - 1) * a;
    }
}

int main()
{
    std::cout << aToPowOfN(4, 10) << '\n';
}
