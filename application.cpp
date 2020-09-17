#include "fastabc.cpp"
#include <fstream>
//using namespace st;

using namespace fastABC;
/*

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

    std::cout << fastabc<2>(M,costf,50) << std::endl;
}
*/

Particle<100> data_t = {0, 0.181774, 0.384135, 0.568554, 0.743793, 0.924416, 1.1246, 1.3395, 1.54856, 1.7435, 1.93961, 2.1233, 2.31413, 2.53275, 2.74593, 2.94546, 3.13097, 3.30854, 3.50644, 3.70581, 3.88095, 4.09149, 4.30519, 4.50887, 4.68476, 4.90082, 5.10487, 5.28777, 5.50326, 5.72769, 5.90336, 6.08923, 6.30087, 6.51063, 6.71371, 6.89911, 7.09175, 7.29639, 7.47911, 7.67386, 7.86828, 8.08966, 8.29568, 8.47665, 8.67815, 8.88895, 9.09187, 9.29202, 9.4894, 9.70713, 9.93112, 10.1078, 10.3168, 10.5091, 10.6908, 10.9149, 11.13, 11.3089, 11.5058, 11.6908, 11.9039, 12.0809, 12.2971, 12.5211, 12.6985, 12.8859, 13.0781, 13.2548, 13.4544, 13.6406, 13.8482, 14.0611, 14.2387, 14.4298, 14.6453, 14.8332, 15.0271, 15.2381, 15.4537, 15.6443, 15.8601, 16.0685, 16.2587, 16.4792, 16.6596, 16.8543, 17.0752, 17.2774, 17.4998, 17.7243, 17.9232, 18.1252, 18.3222, 18.5046, 18.7033, 18.8828, 19.087, 19.2983, 19.5087, 19.6918};
Particle<100> data_x  = {0, -0.343478, -0.916422, -1.22021, -0.521715, 0.140775, 0.476329, -0.232606, -0.505085, -0.505838, 0.737463, 1.46812, 1.16125, 1.17623, 1.40268, 0.969796, 1.31413, 1.36253, 1.16959, 1.69794, 2.37553, 2.06132, 3.64276, 3.9055, 4.17068, 3.18801, 2.0818, 1.69969, 2.3468, 1.60287, 1.0576, 1.44456, 2.48468, 1.95234, 3.15569, 1.68939, 2.26445, 2.60052, 2.64789, 3.74227, 3.37389, 4.27545, 4.26844, 3.04336, 2.91728, 3.0518, 3.76579, 5.40901, 4.30924, 4.4154, 6.32749, 6.40329, 6.64329, 7.55862, 8.16566, 8.10436, 7.87631, 8.21864, 9.64687, 9.54955, 8.98956, 9.11623, 8.07521, 7.81976, 8.49242, 9.24731, 9.43656, 9.11205, 8.64844, 9.15735, 9.27297, 10.5716, 9.36836, 10.0188, 10.0158, 10.1157, 9.50789, 10.2188, 9.33258, 8.41714, 7.74426, 7.34827, 6.01638, 7.30009, 7.36199, 7.25326, 8.02489, 7.92611, 7.78279, 8.8581, 8.62488, 8.87807, 8.89313, 9.46683, 9.16481, 10.1045, 11.191, 12.2597, 11.6287, 11.6424};

template<unsigned N> std::tuple<Particle<N>,Particle<N>> model(default_rng &simrn, double v, double sigma) {
    Particle<N> t;
    Particle<N> x;
    Normal Z(0,1);
    Uniform U(0,1);
    t[0]=x[0]=0.0;
    for(unsigned i=1; i<N; i++) {
        double dt=0.175+U.rand(simrn)*0.05;
        t[i] = t[i-1] + dt;
        x[i] = x[i-1] + v*dt + Z.rand(simrn)*sigma*sqrt(dt);
    }
    return {x,t};
}

default_rng simrng;


double fcost(double P[2]) {
    double v=P[0];
    double sigma=P[1];
    auto [x,t] = model<100>(simrng,v,sigma);

    double vmu=0.0, vmu2=0.0, total=0.0;
    for(int i=1;i<100;i++) {
        double stat=(data_x[i]-data_x[i-1])/(data_t[i]-data_t[i-1]);
        vmu+=stat;
        vmu2+=stat*stat;
        total+=1.0;
    }
    double vmu_s=0.0, vmu2_s=0.0, total_s=0.0;
    for(int i=1;i<100;i++) {
        double stat=(x[i]-x[i-1])/(t[i]-t[i-1]);
        vmu_s+=stat;
        vmu2_s+=stat*stat;
        total_s+=1.0;
    }
    vmu/=total;
    vmu2/=total;
    vmu_s/=total_s;
    vmu2_s/=total_s;
    vmu2=sqrt(vmu2-vmu*vmu);
    vmu2_s=sqrt(vmu2_s-vmu_s*vmu_s);
    return sqrt((pow((vmu-vmu_s)/vmu,2)+pow((vmu2-vmu2_s)/vmu2,2))/2);
}
void sim(double epstol,bool verbose=true) {
    default_rng simrn;
    double x[2]= {0.6,1.5};
    auto a=Uniform(-2.5,2.5);
    auto b=Uniform(0,5);
    DistVec M = {&a,&b};
    fastabc_verbosity(verbose);
    auto res = fastabc<2>(M,fcost,500,epstol);
    std::cout << res << std::endl;
    std::ofstream myfile;
    myfile.open ("plot_infer/inference_res"+std::to_string((int)(epstol*100.0))+".txt");
    for (unsigned i = 0; i<500; i++) {
        myfile << res[i] << std::endl;
    }
    myfile.close();
}

int main() {
    sim(10000);
    sim(1.0);
    sim(0.5);
    sim(0.1);
    sim(0.05);
    sim(0.01);
}
