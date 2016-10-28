#include <iostream>
#include <vector>
#include <cstdlib>

#include "simulation.h"

int main() {
  unsigned int rows = 310;
  unsigned int cols = 310;
  unsigned int timesteps = 500;
  double nu = 0.05;
  double dx = 2.0 / (cols - 1.0);
  double dy = 2.0 / (rows - 1.0);
  double sigma = 0.25;
  double dt = sigma * dx * dy / nu;

  Simulation sim(rows, cols, nu, dx, dy, dt);
  std::cout << "Start Temperature: " << sim.Temperature() << std::endl;
  for (unsigned int ts = 0; ts < timesteps; ++ts) {
    sim.Advance();
  }
  std::cout << "Finish Temperature: " << sim.Temperature() << std::endl;
  return EXIT_SUCCESS;
}
