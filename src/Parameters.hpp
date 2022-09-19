#ifndef PARAMETERS_CLASS
#define PARAMETERS_CLASS
#include "types.hpp"
class Parameters{
protected:
  ushort m_length = 0;
  int m_groupSpeedDisplacement = -1;
  int m_groupSpeedTime = -1;
  int m_absoluteTime = -1;

  friend class Simulation;
};
#endif
