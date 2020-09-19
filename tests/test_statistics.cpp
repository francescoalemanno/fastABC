#include "../statistics.cpp"
using namespace statistics;
using namespace std;
int main() {
    default_rng rng;
    auto a=Uniform(0,2);
    auto b=Normal(0,1);
    DistVec M = {&a,&b};
    cout << "Base methods, logpdf, rand, DistVec-rand" << endl;
    for(int i=0; i<5; i++) {
        double r1=a.rand(rng);
        double r2=b.rand(rng);
        Particle<2> x;
        x[0]=r1; x[1]=r2;
        cout <<"r(" << r1 << " "<< r2 << ") lp=" << (a.logpdf(r1) +b.logpdf(r2)) << ", lp=" << logpdf(M,x) << endl;
    }
    cout << "Particle sampling funcs" << endl;
    for(int i=0; i<5; i++) {
        Particle<2> x;
        rand(x,rng,M);
        cout <<"r(" << x << ") lp=" << logpdf(M,x) << endl;
    }
    cout << "Particle sampling helper funcs" << endl;
    for(int i=0; i<5; i++) {
        auto x=rand<2>(rng,M);
        cout <<"r(" << x << ") lp=" << logpdf(M,x) << endl;
    }
    cout << "Ensemble mean and variance" << endl;
    vector<Particle<2>> vecp;
    for(int i=0; i<50; i++) {
        vecp.push_back(rand<2>(rng,M));
        cout << vecp << endl;
    }
}