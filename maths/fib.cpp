# include <iostream>

int fib(int n) {
    int a = 0;
    int b = 1;
    int c = a + b;
    if (n == 1) { 
        return 0;
    }
    else if (n == 2) {
        return 1;
    }
    for (int i = 0; i < n - 2; i++) {
        a = b;
        b = c;
        c = a + b;
    }

    return c;
}

int main() {
    std::cout << fib(20) << '\n';
}
