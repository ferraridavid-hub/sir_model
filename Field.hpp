#ifndef FIELD_HPP
#define FIELD_HPP

#include <functional>
#include <iostream>
#include <vector>

using phase_vec = std ::vector<double>;

class Field {
  phase_vec (*f)(double t, phase_vec const &phase_vector);

public:
  Field(phase_vec (*field)(double t, phase_vec const &phase_vector)) {
    f = field;
  }
  phase_vec operator()(double t, phase_vec const &phase_vector) {
    return (*f)(t, phase_vector);
  }
};

#endif