# include <iostream>
using namespace std;

int main(){
    float x = 1;
    float targSq = 29384;
    float f, df;

    while(targSq - x * x > 0.1 || targSq - x * x < -0.1)
    {
        f = (x * x) - targSq;
        df = 2 * x;
        x = x - (f / df);
    }
    cout << x;
}
