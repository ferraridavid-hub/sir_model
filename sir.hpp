#ifndef SIR_HPP
#define SIR_HPP

#include "Population.hpp"
#include <vector>

class Sir_system {
  double _beta;
  double _gamma;
  Population _p;

  // eval_field: helper function to evaluate the field on the
  // population p used for Runge_Kutta algorithm
  std ::vector<double> eval_field(std ::vector<double> v) const {
    double N = v[0] + v[1] + v[2];
    double beta_term = _beta * v[0] * v[1] / N;
    double gamma_term = _gamma * v[1];

    double new_s = -beta_term;
    double new_i = beta_term - gamma_term;
    double new_r = gamma_term;

    return std::vector<double>{new_s, new_i, new_r};
  }

public:
  Sir_system(double beta, double gamma, Population const &p) {
    _beta = beta;
    _gamma = gamma;
    _p = p;
  }

  double get_beta() const { return _beta; }
  double get_gamma() const { return _gamma; }
  Population get_pop() const { return _p; }

  // tstep: simulate a step of one day of the evolving system with Runge_Kutta
  // algorithm
  void tstep() {
    Population temp{_p};
    std ::vector<double> res(3);
    std ::vector<double> k(3);

    // computing k1
    k = eval_field(_p.get_params());
    temp.set_params(_p.getS() + k[0] / 2, _p.getI() + k[1] / 2,
                    _p.getR() + k[2] / 2);
    for (int i = 0; i < 3; i++)
      res[i] = k[i] / 6;

    // computing k2
    k = eval_field(temp.get_params());
    temp.set_params(_p.getS() + k[0] / 2, _p.getI() + k[1] / 2,
                    _p.getR() + k[2] / 2);
    for (int i = 0; i < 3; i++)
      res[i] += k[i] / 3;

    // computing k3
    k = eval_field(temp.get_params());
    temp.set_params(_p.getS() + k[0], _p.getI() + k[1], _p.getR() + k[2]);
    for (int i = 0; i < 3; i++)
      res[i] += k[i] / 3;

    // computing k4
    k = eval_field(temp.get_params());
    for (int i = 0; i < 3; i++)
      res[i] += k[i] / 6;

    // set new params of population after one day
    _p.set_params(_p.getS() + res[0], _p.getI() + res[1], _p.getR() + res[2]);
  }

};

#endif