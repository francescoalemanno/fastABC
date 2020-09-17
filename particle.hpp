#pragma once

#include <iostream>

template<unsigned d, class T = double> class Particle {
    public: 
    T x[d]={0};
    T& operator[](unsigned i) { return x[i]; }
    const T& operator[](unsigned i) const { return x[i]; }
};

template<unsigned d, class T> std::ostream& operator<<(std::ostream& os, const Particle<d, T> &P)
{   
    for(int i=0; i<d-1; i++) {
        os << P[i] << " ";
    }
    os << P[d-1];
    return os;
}

#define declare_operator(op,concreteop) \
    template<unsigned d, class T> Particle<d, T> op(const Particle<d, T> &a,const Particle<d, T> &b) {   \
        Particle<d, T> z;\
        for(int i=0; i<d; i++) {\
            z[i] = a[i] concreteop b[i];\
        }\
        return z;\
    }\
    template<unsigned d, class T, class Q> Particle<d, T> op(const Particle<d, T> &a,Q b)\
    {   \
        Particle<d, T> z;\
        for(int i=0; i<d; i++) {\
            z[i] = a[i] concreteop b;\
        }\
        return z;\
    }\
    template<unsigned d, class T, class Q> Particle<d, T> op(Q a,const Particle<d, T> &b)\
    {   \
        Particle<d, T> z;\
        for(int i=0; i<d; i++) {\
            z[i] = a concreteop b[i];\
        }\
        return z;\
    }


#define declare_broadcast(op,fun) \
    template<unsigned d, class T> Particle<d, T> op(const Particle<d, T> &a) {\
        Particle<d, T> z;\
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
declare_broadcast(abs,std::abs)
declare_broadcast(sqrt,sqrt)
declare_broadcast(exp,exp)
declare_broadcast(log,log)

#undef declare_operator
#undef declare_broadcast
