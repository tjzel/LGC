#ifndef BACKGROUND_CLASS
#define BACKGROUND_CLASS
#include "types.hpp"

class Background{
public:
  ushort length;
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
