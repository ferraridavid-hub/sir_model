#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <cassert>
#include <cmath>
#include <vector>

#define EPSILON 0.005

// Population: class representing a Population of SIR Model
class Population {
  double _S{0};
  double _I{0};
  double _R{0};
  double _N{0};

public:
  Population() {}
  Population(double S, double I, double R)
      : _S{S}, _I{I}, _R{R}, _N{S + I + R} {}

  double getN() const { return _N; }
  double getS() const { return _S; }
  double getI() const { return _I; }
  double getR() const { return _R; }
  std ::vector<double> get_params() const {
    return std ::vector<double>{_S, _I, _R};
  }
  // set_params: setting params of population
  // pre: S + I + R must be equal to N
  void set_params(double S, double I, double R) {
    assert(std :: fabs(_N - _S - _I - _R) < EPSILON);
    _S = S;
    _I = I;
    _R = R;
  }
};

#endif