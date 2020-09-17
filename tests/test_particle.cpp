#include "../particle.hpp"
int main() {
    Particle<10> x;
    Particle<10> y;
    Particle<10, int> m;
    for(int i=0; i < 10; i++) {
        x[i]=i*i;
        y[i]=i+1;
    }

    std::cout << x-y*y+2.0*y-1.0 << std::endl;
    std::cout << y-5 << std::endl;
    std::cout << -y << std::endl;
    std::cout << m+7.5 << std::endl;
    std::cout << +y << std::endl;
    std::cout << std::abs(y-7.0)/6.0 << std::endl;
    std::cout << (std::abs(y-5.0) == (y-5.0)) << std::endl;
    std::cout << (std::abs(y-5.0) != (y-5.0)) << std::endl;
}