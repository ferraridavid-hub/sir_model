#include <iostream>
#include <cstdio>

#define EPSILON 0.001

class Population {
  float _N; // once set, it is constant
  float _S;
  float _I;
  float _R;

public:
  Population() { _N = _S = _I = _R = 0; }
  Population(float S, float I, float R) {
    _S = S;
    _I = I;
    _R = R;
    _N = S + I + R;
  }

  float get_N() const { return _N; }

  float get_S() const { return _S; }

  float get_I() const { return _I; }

  float get_R() const { return _R; }

  void set_params(float S, float I, float R) {
    if (fabs(S + I + R - _N) < EPSILON) {
      _S = S;
      _I = I;
      _R = R;
    } else {
      std :: cerr << "error\n";
    }
  }
};

class Sir_system {
  float _beta;
  float _gamma;
  Population _p;
  int _t; // simulation duration in days

public:
  Sir_system(float beta, float gamma, Population const &p, int t) {
    _beta = beta;
    _gamma = gamma;
    _p = p;
    _t = t;
  }

  Population get_pop() const { return _p; }

  // tstep: simulate one step of the evolving system
  void tstep() {
    float beta_term = _beta * _p.get_S() * _p.get_I() / _p.get_N();
    float gamma_term = _gamma * _p.get_I();

    float next_S = _p.get_S() - beta_term;
    float next_I = _p.get_I() + beta_term - gamma_term;
    float next_R = _p.get_R() + gamma_term;

    _p.set_params(next_S, next_I, next_R);
  }

  // evolution: simulate a complete system evolution of duration t
  void evolution() {
    printf("Day\tS\tI\tR\n");
    for (int i = 0; i < _t; i++){
      print(i);
      tstep();
    }
  }

  void print(int day) {
    printf("%3d\t%5.0f\t%5.0f\t%5.0f\n", day, _p.get_S(), _p.get_I(), _p.get_R());
  }
};