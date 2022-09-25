#ifndef PARAMETERS_CLASS
#define PARAMETERS_CLASS
#include "types.hpp"
class Parameters {
protected:
  int m_length = 0;
  int m_min = -1;
  int m_groupVelocityDisplacement = 0;
  int m_groupVelocityTime = -1;
  int m_phaseVelocityDisplacement = 0;
  int m_phaseVelocityTime = -1;
  int m_absoluteTime = -1;

  friend class Simulation;

  //Parameters& Parameters::operator=(const Parameters&)
};
#endif
