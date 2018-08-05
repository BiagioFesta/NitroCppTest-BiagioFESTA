#include <iostream>
#include "NitroCpp.hpp"

int main(int argc, char* argv[]) {
  using nitroCpp::NitroCpp;

  NitroCpp aNitroCpp;
  return aNitroCpp.run(argc, argv);
}
