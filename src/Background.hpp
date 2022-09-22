#ifndef BACKGROUND_CLASS
#define BACKGROUND_CLASS
#include "types.hpp"
#include "Parameters.hpp"

class Background:public Parameters{
  int m_min;
  int m_length;
  bool m_cell[MAX_SIZE];

  void simplify(void);

public:
  Background(void);
  Background(const ushort, bool*);
  Background(const Background&);
  Background& operator=(const Background&);
  const bool operator>(const Background&);
  const bool operator<(const Background&);
  const bool operator==(const Background&);

  void print(void);

  friend class Simulation;
  friend class MapKey;
};

#endif
