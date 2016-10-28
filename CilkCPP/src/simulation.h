#pragma once

#include <vector>
#include <algorithm>

class Simulation final {
  private:
    unsigned int _rows;
    unsigned int _cols;
    double _nu;
    double _dx;
    double _dy;
    double _dt;
    std::vector<double> _state_now;
    std::vector<double> _state_next;
  public:
    Simulation(unsigned int rows_,
               unsigned int cols_,
               double nu_,
               double dx_,
               double dy_,
               double dt_);
    Simulation(const Simulation&) = delete;
    Simulation(Simulation&&) = delete;
    Simulation& operator=(const Simulation&) = delete;
    Simulation& operator=(Simulation&&) = delete;
    ~Simulation() = default;

    unsigned int rows() const;
    unsigned int cols() const;
    double nu() const;
    double dx() const;
    double dy() const;
    double dt() const;
    void Advance();
    double Temperature() const;
};


namespace simulation_helpers {
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
  inline unsigned int Index2d(int i,
                              int j,
                              int rows,
                              int cols) {
    i = MAX(0, MIN(rows-1, i));
    j = MAX(0, MIN(cols-1, j));
    return i * cols + j;
  }
} // namespace simulation_helpers
