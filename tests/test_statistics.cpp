#include "../statistics.cpp"
using namespace statistics;
int main() {
    default_rng rng;
    auto a=Uniform(0,2);
    auto b=Normal(0,1);
    DistVec M = {&a,&b};
    std::cout << "Base methods, logpdf, rand, DistVec-rand" << std::endl;
    for(int i=0; i<5; i++) {
        double r1=a.rand(rng);
        double r2=b.rand(rng);
        Particle<2> x;
        x[0]=r1; x[1]=r2;
        std::cout <<"r(" << r1 << " "<< r2 << ") lp=" << (a.logpdf(r1) +b.logpdf(r2)) << ", lp=" << logpdf(M,x) << std::endl;
    }
    std::cout << "Particle sampling funcs" << std::endl;
    for(int i=0; i<5; i++) {
        Particle<2> x;
        rand(x,rng,M);
        std::cout <<"r(" << x << ") lp=" << logpdf(M,x) << std::endl;
    }
    std::cout << "Particle sampling helper funcs" << std::endl;
    for(int i=0; i<5; i++) {
        auto x=rand<2>(rng,M);
        std::cout <<"r(" << x << ") lp=" << logpdf(M,x) << std::endl;
    }
    std::cout << "Ensemble mean and variance" << std::endl;
    std::vector<Particle<2>> vecp;
    for(int i=0; i<5; i++) {
        vecp.push_back(rand<2>(rng,M));
        std::cout << vecp << std::endl;
    }
    

}