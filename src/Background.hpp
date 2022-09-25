#ifndef BACKGROUND_CLASS
#define BACKGROUND_CLASS
#include "types.hpp"
#include "Parameters.hpp"

class Background:public Parameters{
  bool m_cell[MAX_SIZE];

  void simplify(void);

public:
  Background(void);
  Background(const ushort, bool*);
  Background(const Background&);
  Background& operator=(const Background&);
  bool operator>(const Background&) const;
  bool operator<(const Background&) const;
  bool operator==(const Background&) const;

  void print(void) const;

  friend class Simulation;
  friend class MapKey;
};

#endif
