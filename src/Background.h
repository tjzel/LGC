#include"types.h"

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
