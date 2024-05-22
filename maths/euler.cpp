# include <iostream>

long double next (size_t n) {
    if (n == 0) {
        return 1;
    }

    long double factorial = 1;
    for (size_t i = 0; i < n; i++){
        factorial = factorial * (n - i);
    }

    return 1/factorial;
}

int main() {
    long double sum = 0;
    for (size_t n = 0; n < 99999; n++) {
        sum  += next(n);
    }

    std::cout << std::setprecision(50) << sum << "\n";
}
