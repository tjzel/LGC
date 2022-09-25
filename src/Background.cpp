#include "types.hpp"
#include <iostream>
#include "Background.hpp"

void Background::simplify(){
  m_min = 0;
  int base = 1;
  bool temp[MAX_SIZE];
  bool min_cell[MAX_SIZE];
  for(int i= m_length-1; i>-1; --i){
    m_min += base*m_cell[i];
    min_cell[i] = m_cell[i];
    base*=2;
  } for(int i=1; i<m_length; ++i) {
    int current = 0;
    base = 1;
    for(int j=m_length-1; j>-1; --j) {
      temp[j] = m_cell[(j+i)%m_length];
      current += base*temp[j];
      base*=2;
    } if(current < m_min) {
      m_min = current;
      for(int j=0; j<m_length; ++j) min_cell[j] = temp[j];
    }
  } for(int i=0; i<m_length; ++i){
    m_cell[i] = min_cell[i];
  }
}

Background::Background(void){
  m_length = 0;
}

Background::Background(const ushort m_length, bool* m_cell){
  this->m_length = m_length;
  for(int i=0; i<m_length; ++i) this->m_cell[i] = m_cell[i];
  simplify();
}

Background::Background(const Background& bg) : Parameters(bg){
  for(int i=0; i<m_length; ++i) m_cell[i] = bg.m_cell[i];
}

Background& Background::operator=(const Background& bg){
  Parameters::operator=(bg);
  for(int i=0; i<m_length; ++i) m_cell[i] = bg.m_cell[i];
  return *this;
}

bool Background::operator<(const Background& bg) const{
  if(this->m_length < bg.m_length || (this->m_length == bg.m_length && this->m_min < bg.m_min)) return true;
  return false;
}

bool Background::operator>(const Background& bg) const{
    if(this->m_length > bg.m_length || (this->m_length == bg.m_length && this->m_min > bg.m_min)) return true;
  return false;
}

bool Background::operator==(const Background& bg) const{
  if(this->m_length == bg.m_length && this->m_min == bg.m_min) return true;
  return false;
}

void Background::print(void) const{
  for(int i=0; i<m_length; ++i){
    if(m_cell[i]) std::cout<<"x";
    else std::cout<<"o";
  } std::cout << "\nMinimal value: " << m_min << "\nLength: " << m_length << "\n";
  std::cout << "Phase velocity: " << m_phaseVelocityDisplacement << "/" << m_phaseVelocityTime << "\nAbsolute time: " << m_absoluteTime << "\n";
}
