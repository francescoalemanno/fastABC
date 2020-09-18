#pragma once

#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>

template<unsigned d, typename T = double> class Particle {
    public: 
    bool measurement=false;
    T x[d]={0};
    T& operator[](unsigned i) { return x[i]; }
    const T& operator[](unsigned i) const { return x[i]; }
};

template<unsigned d, typename T> std::ostream& operator<<(std::ostream& os, const Particle<d, T> &P)
{   
    if(P.measurement) {
        auto [mu,sig] = meanstd(P);
        os << mu << " \u00b1 " << sig;
        return os;
    }
    for(int i=0; i<d-1; i++) {
        os << P[i] << " ";
    }
    os << P[d-1];
    return os;
}

#define declare_operator(op,concreteop) \
    template<unsigned d, class T> Particle<d, T> op(const Particle<d, T> &a,const Particle<d, T> &b) {   \
        bool meas=a.measurement || b.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = a[i] concreteop b[i];\
        }\
        return z;\
    }\
    template<unsigned d, class T, class Q> Particle<d, T> op(const Particle<d, T> &a,Q b)\
    {   \
        bool meas=a.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = a[i] concreteop b;\
        }\
        return z;\
    }\
    template<unsigned d, class T, class Q> Particle<d, T> op(Q a,const Particle<d, T> &b)\
    {   \
        bool meas=b.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = a concreteop b[i];\
        }\
        return z;\
    }



#define declare_broadcast2d(op,fun) \
    template<unsigned d, class T> Particle<d, T> op(const Particle<d, T> &a,const Particle<d, T> &b) {   \
        bool meas=a.measurement || b.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = fun(a[i],b[i]);\
        }\
        return z;\
    }\
    template<unsigned d, class T, class Q> Particle<d, T> op(const Particle<d, T> &a,Q b)\
    {   \
        bool meas=a.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = fun(a[i],b);\
        }\
        return z;\
    }\
    template<unsigned d, class T, class Q> Particle<d, T> op(Q a,const Particle<d, T> &b)\
    {   \
        bool meas=b.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = fun(a,b[i]);\
        }\
        return z;\
    }




#define declare_broadcast(op,fun) \
    template<unsigned d, class T> Particle<d, T> op(const Particle<d, T> &a) {\
        bool meas=a.measurement;\
        Particle<d, T> z;\
        z.measurement=meas;\
        for(int i=0; i<d; i++) {\
            z[i] = fun(a[i]);\
        }\
        return z;\
    }

declare_operator(operator+, +)
declare_operator(operator-, -)
declare_operator(operator*, *)
declare_operator(operator/, /)
declare_operator(operator>, >)
declare_operator(operator<, <)
declare_operator(operator>=, >=)
declare_operator(operator<=, <=)
declare_operator(operator==, ==)
declare_operator(operator!=, !=)
declare_broadcast(operator+,+)
declare_broadcast(operator-,-)

declare_broadcast(std::abs,std::abs)
declare_broadcast(std::sqrt,std::sqrt)
declare_broadcast(std::exp,std::exp)
declare_broadcast(std::log,std::log)
declare_broadcast(std::sin,std::sin)
declare_broadcast(std::cos,std::cos)
declare_broadcast(std::sinh,std::sinh)
declare_broadcast(std::cosh,std::cosh)
declare_broadcast(std::tan,std::tan)
declare_broadcast(std::tanh,std::tanh)
declare_broadcast(std::asin,std::asin)
declare_broadcast(std::acos,std::acos)
declare_broadcast(std::asinh,std::asinh)
declare_broadcast(std::acosh,std::acosh)
declare_broadcast(std::atan,std::atan)
declare_broadcast(std::atanh,std::atanh)
declare_broadcast(std::erf,std::erf)
declare_broadcast(std::erfc,std::erfc)
declare_broadcast(std::tgamma,std::tgamma)
declare_broadcast(std::lgamma,std::lgamma)
declare_broadcast2d(std::pow,std::pow)
declare_broadcast2d(std::atan2,std::atan2)

#undef declare_operator
#undef declare_broadcast
#undef declare_broadcast2d


template<typename T, typename collection, typename sized> std::tuple<T,T> meanstd(collection P,sized N) {
    T mu=P[0]/N;
    T mu2=(P[0]*P[0])/N;
    for(int i=1; i<N; i++) {
        mu = mu + (P[i]/N);
        mu2 = mu2 + ((P[i]*P[i])/N);
    }
    T sigma = std::sqrt(std::abs(mu2-mu*mu));
    return {mu, sigma};
}

template<unsigned N, typename T> std::tuple<T,T> meanstd(Particle<N, T> P) {
    return meanstd<T>(P, N);
}

template<class Q> std::tuple<Q,Q> meanstd(const std::vector<Q> &P)
{
    return meanstd<Q>(P, P.size()); 
}