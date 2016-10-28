#include "simulation.h"

#include <vector>
#include <iostream>

using namespace simulation_helpers;

Simulation::Simulation(unsigned int rows_,
                       unsigned int cols_,
                       double nu_,
                       double dx_,
                       double dy_,
                       double dt_) : _rows(rows_),
                                     _cols(cols_),
                                     _nu(nu_),
                                     _dx(dx_),
                                     _dy(dy_),
                                     _dt(dt_),
                                     _state_now(rows_ * cols_),
                                     _state_next(rows_ * cols_) {
  for (unsigned int i = 2 * (_rows / 4); i < 3 * (_rows / 4);  i++) {
    for (unsigned int j = 2 * (_cols / 4); j < 3 * (_cols / 4);  j++) {
      _state_now[Index2d(i, j, _rows, _cols)] = 1.0;
    }
  }
}

unsigned int Simulation::rows() const { return _rows; }
unsigned int Simulation::cols() const { return _cols; }
double Simulation::nu() const { return _nu; }
double Simulation::dx() const { return _dx; }
double Simulation::dy() const { return _dy; }
double Simulation::dt() const { return _dt; }

void Simulation::Advance() {
  double coeff_x = _nu * _dt / (_dx * _dx);
  double coeff_y = _nu * _dt / (_dy * _dy);
  for (unsigned int i = 0; i < _rows; ++i) {
    for (unsigned int j = 0; j < _cols; ++j) {
      size_t north = Index2d(i-1, j, _rows, _cols);
      size_t south = Index2d(i+1, j, _rows, _cols);
      size_t east = Index2d(i, j-1, _rows, _cols);
      size_t west = Index2d(i, j+1, _rows, _cols);
      size_t center = Index2d(i, j, _rows, _cols);
      _state_next[center] = _state_now[center] 
                          + coeff_x * (_state_now[west] - 2*_state_now[center] + _state_now[east])
                          + coeff_y * (_state_now[north] - 2*_state_now[center] + _state_now[south]);
    }
  }
  std::swap(_state_now, _state_next);
}
double Simulation::Temperature() const { 
  double temperature = 0.0;
  for (unsigned int i = 0; i < _rows; ++i) {
    for (unsigned int j = 0; j < _cols; ++j) {
      temperature += _state_now[Index2d(i, j, _rows, _cols)];
    }
  }
  return temperature;
}
