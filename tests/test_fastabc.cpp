#include "../fastabc.cpp"

using namespace fastABC;

default_rng rng;
double costf(double x[2]) {
    Normal d=Normal(0,1);
    double s=d.rand(rng)*0.005;
    return sqrt((x[0]-0.2+s)*(x[0]-0.2+s)+(x[1]-s-1)*(x[1]-s-1));
}

int main() {
    auto a=Normal(0,3);
    auto b=Normal(0,1);
    DistVec M = {&a,&b};
    std::cout << "Expect ~ [0.2, 1.0]" << std::endl;
    std::cout << fastabc<2>(M,costf,50) << std::endl;
}

