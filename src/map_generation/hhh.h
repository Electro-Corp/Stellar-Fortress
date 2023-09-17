#ifndef HHH_H
#define HHH_H

typedef struct HHH {
public:
  int heat = 0;
  int height = 0;
  int humidity = 0;

  constexpr HHH() = default;
  explicit constexpr HHH(int h, int hh, int hhh) : height(h), heat(hh), humidity(hhh) { }
  HHH(int h) : height(h), heat(h), humidity(h) { }
};
#endif