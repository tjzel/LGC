#include <iostream>
#include <ctime>
#include "types.hpp"
#include "Background.hpp"
#include "Simulation.hpp"

ushort Simulation::calc_lineStart(const ushort width) {
    return MAX_WIDTH + (MAX_SIZE - width)/2;
  }

ushort Simulation::calc_lineEnd(const ushort width) {
    return MAX_WIDTH + (MAX_SIZE + width)/2;
  }
void Simulation::clear(){
    const int realFirstCol = lineStart - width;
    const int realLastCol = lineEnd + width;
    for(int row=0; row<length; ++row) for(int col=realFirstCol; col < realLastCol; ++col) cell[row][col] = 0;
  }

void Simulation::evolve(){
  const int realFirstCol = lineStart - width + 1;
  const int realLastCol = lineEnd + width - 1;
  for(int row=1; row<length; ++row) {
    int prevRow = row-1;
    for(int col=realFirstCol; col<realLastCol; ++col){
      uchar val = cell[prevRow][col-1]*4+cell[prevRow][col]*2+cell[prevRow][col+1];
      cell[row][col] = (rule >> val) & 1;
    }
  }
}

void Simulation::evolve(const uchar row){
  const int realFirstCol = lineStart - width + 1;
  const int realLastCol = lineEnd + width - 1;
  int prevRow = row-1;
  for(int col=realFirstCol; col<realLastCol; ++col){
    uchar val = cell[prevRow][col-1]*4+cell[prevRow][col]*2+cell[prevRow][col+1];
    cell[row][col] = (rule >> val) & 1;
  }
}

void Simulation::set(const uchar pos){
  cell[0][lineStart+pos] = 1;
}

void Simulation::unset(const uchar pos){
  cell[0][lineStart+pos] = 0;
}

void Simulation::complement(const uchar pos){
  cell[0][lineStart+pos] = !cell[0][lineStart+pos];
}

void Simulation::randomize(){
  for(int col=lineStart; col<lineEnd; ++col){
    cell[0][col] = rand()%2;
  }
}

Background Simulation::findBackground(const ushort row){
  bool temp[MAX_SIZE];
  for(int len=4; len<width/4; ++len) {
    ushort endPos = lineEnd-2*len;
    for(int pos = lineStart; pos<endPos; ++pos) {
      bool backgroundPresent = true;
      for(int i=0; i<len; ++i){
        temp[i] = cell[row][pos+i];
      }
      for(int iter=0; iter<len; ++iter){
        if(cell[row][pos+iter]!=cell[row][pos+len+iter] ||
        cell[row][pos+iter]!=cell[row][pos+2*len+iter]){
          backgroundPresent = false;
          break;
        }
      }
      if(backgroundPresent) {
        std::cout<<"Background found!\n";
        return Background(len, temp);
      }
    }
  }
  return Background();
}

bool Simulation::confirmBackground(Background bg){
  bool bgConfirmed;
  bool absConfirmed;
  int rowLimit = length;
  int colLimit = lineEnd - bg.length;
  for(int row = 1; row<rowLimit; ++row){
    for(int col = lineStart; col < colLimit; ++col){
      bgConfirmed = true;
      for(int i=0; i<bg.length; ++i) if(cell[row][col+i] != bg.cell[i]){
        bgConfirmed = false;
        break;
      } if(bgConfirmed){
        bg.groupSpeedDisplacement = col - lineStart;
        bg.groupSpeedTime = row;
        break;
      }
    } if(bgConfirmed){
      break;
    }
  } if(bgConfirmed) {
    for(int row = 1; row<rowLimit; ++row){
      absConfirmed = true;
      for(int i=0; i<bg.length; ++i) if(cell[row][lineStart+i] != bg.cell[i]){
        absConfirmed = false;
        break;
      } if(absConfirmed){
        bg.absoluteTime = row;
        break;
      }
    } std::cout << "Group speed: " << bg.groupSpeedDisplacement << "/" << bg.groupSpeedTime << "\nAbsolute time: " << bg.absoluteTime << "\n";
    return true;
  } return false;
}

void Simulation::parseBackground(const Background bg){
  std::cout<<"bg length: "<<bg.length << "\n";
  std::cout<<"bg: ";
  for(int i=0; i<bg.length; ++i){
    if(bg.cell[i]) std::cout<<"x";
    else std::cout<<"o";
  } std::cout<<"\n";
  int pos = lineStart;
  int realLineEnd = lineEnd+width;
  int bg_iter=0;
  while(pos < realLineEnd){
    cell[0][pos++] = bg.cell[bg_iter++];
    if(bg_iter==bg.length) bg_iter = 0;
  }
  pos = lineStart - 1;
  int realLineStart = lineStart - width;
  bg_iter = bg.length-1;
  while(pos >= realLineStart){
    cell[0][pos--] = bg.cell[bg_iter--];
    if(bg_iter<0) bg_iter = bg.length-1;
  }
}

void Simulation::findParseEvolve(void){
  srand(time(NULL));
  Background bg;
  int ctr = 0;
  do{
    clear();
    randomize();
    evolve();
    bg = findBackground(length-1);
    std::cout << ctr++ << "\n";
  } while(bg.length == 0);
  parseBackground(bg);
  evolve();
  if(confirmBackground(bg)){
    std::cout << "Background confirmed!\n";
  } else std::cout << "False background\n";
  print();
}

void Simulation::print(void){
  for(int i=0; i<width; ++i) std::cout<<"=";
  std::cout<<"\n";
  for(int row=0; row<length; ++row){
    for(int col=lineStart; col<lineEnd; ++col){
      if(cell[row][col]) std::cout<<"X";
      else std::cout<<"-";
    } std::cout<<"\n";
  } for(int i=0; i<width; ++i) std::cout<<"="; 
  std::cout<<std::endl;
}

Simulation::Simulation(const uchar rule):rule(rule){}

Simulation::Simulation(const uchar rule, const ushort width, const ushort length):rule(rule), width(width), length(length), lineStart(calc_lineStart(width)), lineEnd(calc_lineEnd(width)){}
