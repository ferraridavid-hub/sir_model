#ifndef CAUCHY_PROBLEM_HPP
#define CAUCHY_PROBLEM_HPP

#include <iostream>
#include <vector>

#include "Field.hpp"

using phase_vector = std ::vector<double>;

class Cauchy_Problem {
  phase_vector _initial_conditions;
  double _t0;
  Field _eq;

public:
  Cauchy_Problem(phase_vector const &x0, double t0, Field const &eq)
      : _initial_conditions{x0}, _t0{t0}, _eq{eq} {}

  Field field() const { return _eq; }
  phase_vector initial() const { return _initial_conditions; }
  double t0() const { return _t0; }
};

#endif