#ifndef BACKGROUND_CLASS
#define BACKGROUND_CLASS
#include "types.hpp"
#include "Parameters.hpp"

class Background:public Parameters{
  int min;
  bool cell[MAX_SIZE];

  void simplify(void);
  Background(void);
  Background(const ushort, bool*);
  Background& operator=(const Background&);
  void print(void);

  friend class Simulation;
};

#endif
