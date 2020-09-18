#pragma once
#include <vector>
#include <limits>
#include <random>
#include <tuple>
#include <cmath>
#include "particle.hpp"

namespace statistics {
typedef std::mt19937 default_rng;
const double double_inf = std::numeric_limits<double>::infinity();

struct AbstractDistribution {
    virtual double logpdf(double x) = 0;
    virtual double rand(default_rng &gen) = 0;
};

struct Uniform: AbstractDistribution  {
    double a;
    double b;
    std::uniform_real_distribution<double> distribution;
    Uniform(double da,double db): a(da), b(db), distribution(da,db) {};
    double logpdf(double x) {
        if(x > b || x < a) {
            return -double_inf;
        }
        return -log(b-a);
    }
    double rand(default_rng &gen) {return distribution(gen);}
};

struct Normal: AbstractDistribution  {
    double mu;
    double sigma;
    std::normal_distribution<double> distribution;
    Normal(double dmu,double dsigma): mu(dmu), sigma(dsigma), distribution(dmu,dsigma) {};
    double logpdf(double x) { //unnormalized logpdf
        double z=(x-mu)/sigma;
        return -z*z/2;
    }
    double rand(default_rng &gen) {return distribution(gen);}
};
typedef std::vector<AbstractDistribution*> DistVec;

template<unsigned d> Particle<d> rand(Particle<d> &p, default_rng &rng, AbstractDistribution* dist) {
    for(unsigned i=0; i<d; i++) p[i] = dist->rand(rng);
    return p;
}

template<unsigned d> Particle<d> rand(Particle<d> &p, default_rng &rng, DistVec &prior) {
    for(unsigned i=0; i<d; i++) p[i] = prior[i]->rand(rng);
    return p;
}

template<unsigned d> Particle<d> rand(default_rng &rng, AbstractDistribution* dist) {
    Particle<d> p;
    p.measurement=true;
    return rand(p,rng,dist);
}
template<unsigned d> Particle<d> rand(default_rng &rng, DistVec &prior) {
    Particle<d> p;
    return rand(p,rng,prior);
}
template<unsigned d> double logpdf(DistVec &prior,Particle<d> &p) {
    double ll=0.0;
    for(unsigned i=0; i<d; i++) ll+=prior[i]->logpdf(p[i]);
    return ll;
}

template<unsigned d> std::ostream& operator<<(std::ostream& os, const std::vector<Particle<d>> &P)
{
    auto [mu,sigma] = meanstd(P); 
    os << "[";
    for(int i=0; i<d-1; i++) {
        os << mu[i] << " \u00b1 " << sigma[i] << ", ";
    }
    os << mu[d-1] << " \u00b1 " << sigma[d-1] << "]";
    return os;
}

};