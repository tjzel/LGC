#ifndef SIMULATION_CLASS
#define SIMULATION_CLASS
#include "types.hpp"
#include "Background.hpp"
#include "MapKey.hpp"
#include <map>

class Simulation{
  const uchar m_rule;
  const ushort m_width = MAX_WIDTH;
  const ushort m_length = MAX_LENGTH;
  const ushort m_lineStart=MAX_WIDTH;
  const ushort m_lineEnd=MAX_WIDTH*2;
  bool m_cell[MAX_LENGTH][MAX_WIDTH*3];  
  std::map<MapKey, Background> m_bgMap;

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
  bool confirmBackground(Background&);
  Background findParseEvolve(void);
  void findGlider(const Background);

  void print(void);
  void printBackgroundMap(void);

  int amountOfBackgrounds(void) const;

  Simulation(const uchar);
  Simulation(const uchar, const ushort, const ushort);

};
#endif
