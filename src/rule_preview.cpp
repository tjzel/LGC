#include "Background.hpp"
#include "Simulation.hpp"
#include <cstdio>
#include <iostream>

#define MAX_RULE 256

int main(int argv, char* argc[]){
  int length = 32;
  int width = 32;
  if(argv < 2){
    std::cout << "Forgot to select a rule!\n";
    return 1;
  }
  int rule = atoi(argc[1]);
  for(int i=0; i<MAX_RULE; ++i){
    std::cout<<"Rule "<< i << "\n";
    Simulation sim(rule, width, length);
    sim.clear();
    sim.set(width/2);
    sim.evolve();
    sim.print();
    getchar();
  }
  return 0;
}
