#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "Cauchy_Problem.hpp"
#include <vector>

/*** vector operators ***/
std ::vector<double> operator+(std ::vector<double> const &v1,
                               std::vector<double> const &v2) {
  size_t s1 = v1.size();
  size_t s2 = v2.size();
  size_t i = 0;
  std ::vector<double> res(std ::max(s1, s2), 0);
  while (i < s1 && i < s2) {
    res[i] = v1[i] + v2[i];
    i++;
  }
  while (i < s1) {
    res[i] = v1[i];
    i++;
  }
  while (i < s2) {
    res[i] = v2[i];
    i++;
  }

  return res;
}

std ::vector<double> operator*(double alpha, std::vector<double> const &v) {
  std ::vector<double> res(v);
  for (double &d : res)
    d *= alpha;

  return res;
}

/*** Solver class ***/

class Solver {
  Cauchy_Problem _cp;
  phase_vec _eq_vector;
  double _t;
  double _h;

  void tstep() {
    auto temp = _eq_vector;
    auto res = _eq_vector;
    std ::vector<double> k(_eq_vector.size(), 0);

    // computing k1
    k = (_cp.field())(_t, temp);
    res = res + (_h / 6) * k;

    // computing k2
    temp = _eq_vector + (_h / 2) * k;
    k = (_cp.field())(_t + _h / 2, temp);
    res = res + (_h / 3) * k;

    // computing k3
    temp = _eq_vector + (_h / 2) * k;
    k = (_cp.field())(_t + _h / 2, temp);
    res = res + (_h / 3) * k;

    // computing k4
    temp = _eq_vector + _h * k;
    k = (_cp.field())(_t + _h, temp);
    res = res + (_h / 6) * k;

    _eq_vector = res;
    _t = _t + _h;
  }

public:
  Solver(Cauchy_Problem const &cp)
      : _cp{cp}, _eq_vector{cp.initial()}, _t{cp.t0()}, _h{0} {}

  std ::vector<phase_vec> simulation(double duration, double h) {
    _h = h;
    double t0 = _cp.t0();
    std ::vector<phase_vec> data{0};
    while (t0 <= duration) {
      data.push_back(_eq_vector);
      tstep();
      t0 += _h;
    }
    return data;
  }
};

#endif