#include "Background.hpp"
#include "Simulation.hpp"
#include <cstdio>
#include <iostream>

#define MAX_RULE 256

int main(int argv, char* argc[]){
  int length = 32;
  int width = 32;
  for(int i=0; i<MAX_RULE; ++i){
    std::cout<<"Rule "<< i << "\n";
    Simulation sim(i, width, length);
    sim.clear();
    sim.set(width/2);
    sim.evolve();
    sim.print();
    std::cout<<"Press q to quit, c to continue displaying rule examples: ";
    char c;
    while((c = getchar())){
      if(c == 'q') return 0;
      else if (c == 'c') break;
    }
  }
  return 0;
}
