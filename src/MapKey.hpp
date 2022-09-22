#ifndef MYMAP_CLASS
#define MYMAP_CLASS
#include "types.hpp"
#include "Background.hpp"

class MapKey{
public:
    ushort m_length;
    int m_min;
    MapKey(const Background&);
    bool operator>(const MapKey&) const;
    bool operator<(const MapKey&) const;
    bool operator==(const MapKey&) const;
};

#endif