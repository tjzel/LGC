#ifndef PARAMETERS_CLASS
#define PARAMTETERS_CLASS
#include "types.hpp"
class Parameters{
protected:
  ushort length = 0;
  int groupSpeedDisplacement = -1;
  int groupSpeedTime = -1;
  int absoluteTime = -1;

  friend class Simulation;
};
#endif
