#include <iostream>
#include <ctime>
#include "types.hpp"
#include "MapKey.hpp"
#include "Background.hpp"
#include "Simulation.hpp"

ushort Simulation::calc_lineStart(const ushort m_width) {
    return MAX_WIDTH + (MAX_SIZE - m_width)/2;
  }

ushort Simulation::calc_lineEnd(const ushort m_width) {
    return MAX_WIDTH + (MAX_SIZE + m_width)/2;
  }
void Simulation::clear(){
    const int realFirstCol = m_lineStart - m_width;
    const int realLastCol = m_lineEnd + m_width;
    for(int row=0; row<m_length; ++row) 
      for(int col=realFirstCol; col < realLastCol; ++col) 
        m_cell[row][col] = 0;
  }

void Simulation::evolve(){
  const int realFirstCol = m_lineStart - m_width + 1;
  const int realLastCol = m_lineEnd + m_width - 1;
  for(int row=1; row<m_length; ++row) {
    int prevRow = row-1;
    for(int col=realFirstCol; col<realLastCol; ++col){
      uchar val = m_cell[prevRow][col-1]*4+m_cell[prevRow][col]*2+m_cell[prevRow][col+1];
      m_cell[row][col] = (m_rule >> val) & 1;
    }
  }
}

void Simulation::evolve(const uchar row){
  const int realFirstCol = m_lineStart - m_width + 1;
  const int realLastCol = m_lineEnd + m_width - 1;
  int prevRow = row-1;
  for(int col=realFirstCol; col<realLastCol; ++col){
    uchar val = m_cell[prevRow][col-1]*4+m_cell[prevRow][col]*2+m_cell[prevRow][col+1];
    m_cell[row][col] = (m_rule >> val) & 1;
  }
}

void Simulation::set(const uchar pos){
  m_cell[0][m_lineStart+pos] = 1;
}

void Simulation::unset(const uchar pos){
  m_cell[0][m_lineStart+pos] = 0;
}

void Simulation::complement(const uchar pos){
  m_cell[0][m_lineStart+pos] = !m_cell[0][m_lineStart+pos];
}

void Simulation::randomize(){
  for(int col=m_lineStart; col<m_lineEnd; ++col){
    m_cell[0][col] = rand()%2;
  }
}

Background Simulation::findBackground(const ushort row){
  bool temp[MAX_SIZE];
  for(int len=4; len<m_width/4; ++len) {
    ushort endPos = m_lineEnd-2*len;
    for(int pos = m_lineStart; pos<endPos; ++pos) {
      bool backgroundPresent = true;
      for(int i=0; i<len; ++i){
        temp[i] = m_cell[row][pos+i];
      }
      for(int iter=0; iter<len; ++iter){
        if(m_cell[row][pos+iter]!=m_cell[row][pos+len+iter] ||
        m_cell[row][pos+iter]!=m_cell[row][pos+2*len+iter]){
          backgroundPresent = false;
          break;
        }
      }
      if(backgroundPresent) {
        //std::cout<<"Background found!\n";
        return Background(len, temp);
      }
    }
  }
  return Background();
}

bool Simulation::confirmBackground(Background& bg){
  bool bgConfirmed;
  bool absConfirmed;
  int rowLimit = m_length;
  int colLimit = m_lineEnd - bg.m_length;
  for(int row = 1; row<rowLimit; ++row){
    for(int col = m_lineStart; col < colLimit; ++col){
      bgConfirmed = true;
      for(int i=0; i<bg.m_length; ++i) if(m_cell[row][col+i] != bg.m_cell[i]){
        bgConfirmed = false;
        break;
      } if(bgConfirmed){
        bg.m_phaseVelocityDisplacement = col - m_lineStart;
        bg.m_phaseVelocityTime = row;
        //to find out whether background is actually travelling the opposite direction
        //if(bg.m_groupSpeedDisplacement > bg.m_groupSpeedTime) bg.m_groupSpeedDisplacement =  - bg.m_length - bg.m_groupSpeedDisplacement;
        break;
      }
    } if(bgConfirmed){
      break;
    }
  } if(bgConfirmed) {
    for(int row = 1; row<rowLimit; ++row){
      absConfirmed = true;
      for(int i=0; i<bg.m_length; ++i) if(m_cell[row][m_lineStart+i] != bg.m_cell[i]){
        absConfirmed = false;
        break;
      } if(absConfirmed){
        bg.m_absoluteTime = row;
        break;
      }
    } //std::cout << "Group speed: " << bg.m_phaseVelocityDisplacement << "/" << bg.m_phaseVelocityTime << "\nAbsolute time: " << bg.m_absoluteTime << "\n";
    return true;
  } return false;
}

void Simulation::parseBackground(const Background bg){
  //std::cout<<"bg m_length: "<<bg.m_length << "\n";
  //std::cout<<"bg: ";
  //for(int i=0; i<bg.m_length; ++i){
  //  if(bg.m_cell[i]) std::cout<<"x";
  //  else std::cout<<"o";
  //} std::cout<<"\n";
  int pos = m_lineStart;
  int realLineEnd = m_lineEnd+m_width;
  int bg_iter=0;
  while(pos < realLineEnd){
    m_cell[0][pos++] = bg.m_cell[bg_iter++];
    if(bg_iter==bg.m_length) bg_iter = 0;
  }
  pos = m_lineStart - 1;
  int realLineStart = m_lineStart - m_width;
  bg_iter = bg.m_length-1;
  while(pos >= realLineStart){
    m_cell[0][pos--] = bg.m_cell[bg_iter--];
    if(bg_iter<0) bg_iter = bg.m_length-1;
  }
}

Background Simulation::findParseEvolve(void){
  Background bg;
  int ctr = 0;
  bool bgConfirmed = false;
  while(!bgConfirmed){
    do{
      clear();
      randomize();
      evolve();
      bg = findBackground(m_length-1);
      //std::cout << ctr++ << "\n";
      if(ctr > 100000){
        std::cout << "Too many attempts!\n";
        return bg;
      }
    } while(bg.m_length == 0);
    parseBackground(bg);
    evolve();
    bgConfirmed = confirmBackground(bg);
  } //std::cout << "Background confirmed!\n";
  int size = m_bgMap.size();
  m_bgMap.try_emplace(MapKey(bg), bg);
  if(m_bgMap.size() == size) std::cout << "Background already present!\n";
  print();
  return bg;
}

void Simulation::findGlider(const Background bg){
  if(bg.m_length == 0){
    std::cout<<"Background not valid!\n";
    return;
  } parseBackground(bg);
  for(int i=0; i<bg.m_length; ++i){
    complement((m_width-bg.m_length)/2+i);
    evolve();
    print();
    complement((m_width-bg.m_length)/2+i);
    //here
  }
}

void Simulation::print(void){
  for(int i=0; i<m_width; ++i) std::cout<<"=";
  std::cout<<"\n";
  for(int row=0; row<m_length; ++row){
    for(int col=m_lineStart; col<m_lineEnd; ++col){
      if(m_cell[row][col]) std::cout<<"X";
      else std::cout<<"-";
    } std::cout<<"\n";
  } for(int i=0; i<m_width; ++i) std::cout<<"=";
  std::cout<<std::endl;
}

void Simulation::printBackgroundMap(void){
  std::cout<<"Printing backgrounds, size: " << m_bgMap.size() << "\n";
  for(auto it = m_bgMap.begin(); it != m_bgMap.end(); ++it){
    it->second.print();
  } std::cout<<"\n";
}

Simulation::Simulation(const uchar m_rule):m_rule(m_rule){
    srand(time(NULL));
}

Simulation::Simulation(const uchar m_rule, const ushort m_width, const ushort m_length)
:m_rule(m_rule), m_width(m_width), m_length(m_length), m_lineStart(calc_lineStart(m_width)), m_lineEnd(calc_lineEnd(m_width)){
    srand(time(NULL));
}
