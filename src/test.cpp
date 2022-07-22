#include "Simulation.cpp"
//#include "Background.cpp"
#include <cstdio>
#include <iostream>

int main(int argv, char* argc[]){
  int length = 64;
  int width = 64;
  int rule = atoi(argc[1]);
  /*for(int i=0; i<128; ++i){
    Simulation simulation(i, width, length);
    simulation.clear();
    simulation.set(width/2);
    simulation.print();
    simulation.evolve();
    simulation.print();
    std::cout<<"rule:"<<i<<std::endl;
    while(std::getchar() != '\n');
  }*/
  Simulation sim(rule, width, length);
  //sim.clear();
  //sim.set(width/2);
  //sim.randomize();
  //sim.evolve();
  //sim.print();
  //sim.findBackground();
  sim.findParseEvolve();
  //bool cell[] = {1, 0, 0, 1, 0, 0};
  //Background background(6, cell);
  //background.print();
  //background.simplify();
  //background.print();
}
