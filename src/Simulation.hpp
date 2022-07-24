#ifndef SIMULATION_CLASS
#define SIMULATION_CLASS
#include "types.hpp"
#include "Background.hpp"

class Simulation{
  const uchar rule;
  const ushort width = MAX_WIDTH;
  const ushort length = MAX_LENGTH;
  const ushort lineStart=MAX_WIDTH;
  const ushort lineEnd=MAX_WIDTH*2;
  bool cell[MAX_LENGTH][MAX_WIDTH*3];

  static ushort calc_lineStart(const ushort);
  static ushort calc_lineEnd(const ushort);

public:
  void clear(void);
  void evolve(void);
  void evolve(const uchar);
  void set(const uchar);
  void unset(const uchar);
  void complement(const uchar);
  void randomize(void);

  Background findBackground(const ushort);
  void parseBackground(const Background);
  bool confirmBackground(Background);
  Background findParseEvolve(void);
  void findGlider(const Background);

  void print(void);

  Simulation(const uchar);
  Simulation(const uchar, const ushort, const ushort);

};
#endif
