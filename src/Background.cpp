#include "types.hpp"
#include <iostream>
#include "Background.hpp"

void Background::simplify(){
  min = 0;
  int base = 1;
  bool temp[MAX_SIZE];
  bool min_cell[MAX_SIZE];
  for(int i= length-1; i>-1; --i){
    min += base*cell[i];
    min_cell[i] = cell[i];
    base*=2;
  } for(int i=1; i<length; ++i) {
    int current = 0;
    base = 1;
    for(int j=length-1; j>-1; --j) {
      temp[j] = cell[(j+i)%length];
      current += base*temp[j];
      base*=2;
    } if(current < min) {
      min = current;
      for(int j=0; j<length; ++j) min_cell[j] = temp[j];
    }
  } for(int i=0; i<length; ++i){
    cell[i] = min_cell[i];
  }
}

Background::Background(void){
  length = 0;
}

Background::Background(const ushort length, bool* cell){
  this->length = length;
  for(int i=0; i<length; ++i) this->cell[i] = cell[i];
  simplify();
}

Background& Background::operator=(const Background& bg){
  length = bg.length;
  for(int i=0; i<length; ++i) cell[i] = bg.cell[i];
  return *this;
}

void Background::print(){
  for(int i=0; i<length; ++i){
    if(cell[i]) std::cout<<"x";
    else std::cout<<"o";
  } std::cout << "\nmin: " << min << "\n";
}
