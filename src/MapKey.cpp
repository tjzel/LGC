#include "types.hpp"
#include "MapKey.hpp"

MapKey::MapKey(const Background& bg){
    this->m_length = bg.m_length;
    this->m_min = bg.m_min;
}

bool MapKey::operator<(const MapKey& bg) const{
  if(this->m_length < bg.m_length || (this->m_length == bg.m_length && this->m_min < bg.m_min)) return true;
  return false;
}

bool MapKey::operator>(const MapKey& bg) const{
    if(this->m_length > bg.m_length || (this->m_length == bg.m_length && this->m_min > bg.m_min)) return true;
  return false;
}

bool MapKey::operator==(const MapKey& bg) const{
  if(this->m_length == bg.m_length && this->m_min == bg.m_min) return true;
  return false;
}