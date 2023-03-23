#ifndef RUNGE_KUTTA_SOLVER_HPP
#define RUNGE_KUTTA_SOLVER_HPP

#include <cmath>
#include <iostream>
#include <vector>

/*** helper function for evaluating function f on the phase vector in runge
 * kutta algorithm ***/
std ::vector<double> eval_field(std ::vector<double> const &v);

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

/*** Runge-Kutta class  ***/
class Runge_Kutta_Solver {
  std ::vector<double> eq_vector; // phase space vector of the system
  size_t problem_dimension; // dimension of the Cauchy problem (equal to state
                            // vector's size)
  double _h;                // step-size of simulation

public:
  Runge_Kutta_Solver(size_t dimension)
      : eq_vector(dimension, 3), problem_dimension{dimension}, _h{0} {}
  auto getEqVector() const { return eq_vector; }
  void setEqVector(std ::vector<double> const &v) { eq_vector = v; }

  // tstep: perform one calculation step of Runge-Kutta algorithm
  // calculation depends on extern definition of eval_field
  // TODO: think something smarter, if possible
  void tstep() {
    auto temp = eq_vector;
    auto res = eq_vector;
    std ::vector<double> k(problem_dimension, 0);

    // computing k1
    k = eval_field(temp);
    res = res + (_h / 6) * k;

    // computing k2
    temp = eq_vector + (_h / 2) * k;
    k = eval_field(temp);
    res = res + (_h / 3) * k;

    // computing k3
    temp = eq_vector + (_h / 2) * k;
    k = eval_field(temp);
    res = res + (_h / 3) * k;

    // computing k4
    temp = eq_vector + _h * k;
    k = eval_field(temp);
    res = res + (_h / 6) * k;

    eq_vector = res;
  }

  // simulation: perform a simulation of system's evolution of duration t, and
  // step-size h first version: print result on standard output
  // TODO: initial conditions and initial instant (maybe not here)
  void simulation(double t, double h) {
    _h = h;
    double time = 0;
    while (time <= t) {
      for (size_t i = 0; i < problem_dimension; i++)
        printf("y%d(%.2f)=%.3f\t\t", i, time, eq_vector[i]);
      // std ::cout << "y" << i << "(" << time << ")=" << eq_vector[i] <<
      // "\t\t\t";
      std ::cout << '\n';
      tstep();
      time += _h;
    }
  }
};

#endif