#include <iostream>
#include <ctime>
#include "types.hpp"
#include "Background.hpp"

class Simulation{
  const uchar rule;
  const ushort width = 512, length = 512, lineStart=512, lineEnd=1024;
  bool cell[MAX_LENGTH][MAX_WIDTH*3];

  static ushort calc_lineStart(const ushort width) {
    return MAX_WIDTH + (MAX_SIZE - width)/2;
  }

  static ushort calc_lineEnd(const ushort width) {
    return MAX_WIDTH + (MAX_SIZE + width)/2;
  }
public:
  void clear(){
    //const int realFirstCol = (MAX_LENGTH-3*width)/2;
    const int realFirstCol = lineStart - width;
    //const int realLastCol = (realFirstCol + 3*width);
    const int realLastCol = lineEnd + width;
    for(int row=0; row<length; ++row) for(int col=realFirstCol; col < realLastCol; ++col) cell[row][col] = 0;
  }

  void evolve(){
    //const int realFirstCol = (MAX_LENGTH-3*width)/2;
    const int realFirstCol = lineStart - width + 1;
    //const int realLastCol = (realFirstCol + 3*width) - 1;
    const int realLastCol = lineEnd + width - 1;
    for(int row=1; row<length; ++row) {
      int prevRow = row-1;
      for(int col=realFirstCol; col<realLastCol; ++col){
      uchar val = cell[prevRow][col-1]*4+cell[prevRow][col]*2+cell[prevRow][col+1];
      cell[row][col] = (rule >> val) & 1;
      }
    }
  }

  void set(const uchar pos){
    cell[0][lineStart+pos] = 1;
  }

  void unset(const uchar pos){
    cell[0][lineStart+pos] = 0;
  }

  void complement(const uchar pos){
    cell[0][lineStart+pos] = !cell[0][lineStart+pos];
  }

  void randomize(){
    srand(time(NULL));
    for(int col=lineStart; col<lineEnd; ++col){
      cell[0][col] = rand()%2;
    }
  }

  Background findBackground(const ushort row){
    bool left[MAX_SIZE];
    bool middle[MAX_SIZE];
    bool right[MAX_SIZE];
    for(int len=4; len<width/4; ++len) {
      ushort endPos = lineEnd-2*len;
      for(int pos = lineStart; pos<endPos; ++pos) {
        bool backgroundPresent = true;
        for(int i=0; i<len; ++i){
          left[i] = cell[row][pos+i];
          middle[i] = cell[row][pos+len+i];
          right[i] = cell[row][pos+2*len+i];
        }
        for(int iter=0; iter<len; ++iter){
          if(cell[row][pos+iter]!=cell[row][pos+len+iter] ||
          cell[row][pos+iter]!=cell[row][pos+2*len+iter]){
            backgroundPresent = false;
            break;
          }
        }
        if(backgroundPresent) {
          std::cout<<"pos: " << pos - lineStart << "\n";
          for(int i=0; i<len; ++i){
            if(left[i]) std::cout<<"x";
            else std::cout<<"o";
          }
          std::cout<<"\n";
          for(int i=0; i<len; ++i){
            if(middle[i]) std::cout<<"x";
            else std::cout<<"o";
          }
          std::cout<<"\n";
          for(int i=0; i<len; ++i){
            if(right[i]) std::cout<<"x";
            else std::cout<<"o";
          }
          std::cout<<"\n";
          std::cout<<"Background found!\n";
          return Background(len, left);
        }
      }
    }
    return Background();
  }

  void parseBackground(const Background bg){
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

  void findParseEvolve(void){
    Background bg;
    int ctr = 0;
    do{
      clear();
      randomize();
      evolve();
      bg = findBackground(length-1);
      std::cout << ctr++ << "\n";
    } while(bg.length == 0);
    print();
    //std::cout<<"parsing\n";
    clear();
    parseBackground(bg);
    //std::cout<<"printing\n";
    print();
    evolve();
    print();
  }

  void print(void){
    for(int i=0; i<width; ++i) std::cout<<"-";
    std::cout<<"\n";
    for(int row=0; row<length; ++row){
      for(int col=lineStart; col<lineEnd; ++col){
        if(cell[row][col]) std::cout<<"X";
        else std::cout<<"-";
      } std::cout<<"\n";
    } std::cout<<std::endl;
  }

  Simulation(const uchar rule):rule(rule){}

  Simulation(const uchar rule, const ushort width, const ushort length):rule(rule), width(width), length(length), lineStart(calc_lineStart(width)), lineEnd(calc_lineEnd(width)){}

};
