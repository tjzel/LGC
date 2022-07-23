#include "Background.hpp"
#include "Simulation.hpp"
#include <cstdio>
#include <iostream>

int main(int argv, char* argc[]){
  int length = 64;
  int width = 64;
  if(argv < 2){
    std::cout << "Forgot to select a rule!\n";
    return 1;
  }
  int rule = atoi(argc[1]);
  Simulation sim(rule, width, length);
  sim.findParseEvolve();
  return 0;
}
