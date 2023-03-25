#ifndef SIR_HPP
#define SIR_HPP

#include "Population.hpp"
#include <vector>

class Sir_system {
  double _beta;
  double _gamma;
  Population _p;

public:
  Sir_system(double beta, double gamma, Population const &p) {
    _beta = beta;
    _gamma = gamma;
    _p = p;
  }

  double get_beta() const { return _beta; }
  double get_gamma() const { return _gamma; }
  Population get_pop() const { return _p; }
};

#endif