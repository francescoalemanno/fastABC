#include "../particle.hpp"
using namespace std;
int main() {
    Particle<10> x;
    Particle<10> y;
    Particle<10, int> m;
    for(int i=0; i < 10; i++) {
        x[i]=i*i;
        y[i]=i+1;
    }
    auto P=pow(sin(x),2)+pow(cos(x),2);
    P.measurement=true;
    cout << x-y*y+2.0*y-1.0 << endl;
    cout << y-5 << endl;
    cout << -y << endl;
    cout << m+7.5 << endl;
    cout << P << endl;
    cout << +y << endl;
    cout << abs(y-7.0)/6.0 << endl;
    cout << (abs(y-5.0) == (y-5.0)) << endl;
    cout << (abs(y-5.0) != (y-5.0)) << endl;
}