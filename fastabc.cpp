#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <random>
#include <tuple>
#include "particle.hpp"


namespace fastABC {
#include "statistics.cpp"
using namespace statistics;
bool fastabc_verbose=false;
void fastabc_verbosity(bool state) {
    fastabc_verbose = state;
}

template<unsigned d, class T> auto fastabc(DistVec &prior, T &cost, unsigned N, double epstol=-double_inf, double efftol = 0.001,  double schedule=0.9) {
    default_rng rng;
    std::uniform_int_distribution<unsigned> randidx(0,N-1);
    std::normal_distribution<double> randn(0.0,1.0);
    std::uniform_real_distribution<double> randu(0.0,1.0);
    double gamma=2.38/sqrt(2*d);
    std::vector<Particle<d>> particles;
    double C[N]={0};
    double lpi[N]={0};

    for(int i=0;i<N;i++) {
        particles.push_back(rand<d>(rng,prior));
        C[i] = cost(particles[i].x);
        lpi[i] = logpdf(prior,particles[i]);
    }
    unsigned reps=0;

    while (true) {
        reps += 1;
        double mineps=double_inf;
        double maxeps=-double_inf;
        for(int i=0;i<N;i++) {
            mineps=std::min(mineps,C[i]);
            maxeps=std::max(maxeps,C[i]);
        }
        double adaeps=std::max(epstol,mineps+schedule*(maxeps-mineps));
        unsigned trys=0;
        for(int i=0;i<N;i++) {
            while (C[i] > adaeps) {
                if (trys*efftol > N) {
                    break;
                }
                trys+=1;
                unsigned a=i,b=i;
                do a=randidx(rng); while (a==i);
                do b=randidx(rng); while (b==i || b==a);
                unsigned s=i;

                if(randu(rng) < 0.5) {
                    unsigned tmp=a;
                    a=s;
                    s=tmp;
                }
                Particle<d> proposal = particles[s] + gamma*(particles[b]-particles[a]);
                double lpiproposal = logpdf(prior,proposal);
                if (log(randu(rng)) > std::min(0.0,lpiproposal-lpi[i])) continue;
                double Cproposal = cost(proposal.x);
                if (Cproposal > std::max(C[i],adaeps)) continue;
                C[i] = Cproposal;
                particles[i] = proposal;
                lpi[i] = lpiproposal;
            }
        }
        auto [Cmu, Csigma] = meanstd<double>(C, N);
        if(fastabc_verbose) {
            std::cout << reps << " -> " << particles << "; eps = " << adaeps << "; eff = " << (N+1)/(1.0*trys+1) << ";\t C = "<< Cmu << " \u00b1 "<< Csigma << std::endl;
        }
        if (maxeps <= epstol || trys*efftol > N) {
            if(fastabc_verbose) {
                std::cout << "END" << " -> " << particles << ";\t C = "<< Cmu << " \u00b1 "<< Csigma << std::endl;
            }
            break;
        }
    }

    return particles;
}

};