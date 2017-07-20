#include "Dwave.hpp"

int main(int argc, char** argv) {
  // dwave::Dwave dwave;
  std::cout << "Here is OK" << std::endl;
  dwave::Dwave* dwave = new dwave::Dwave();
  // dwave::Dwave* dwave = (dwave::Dwave*)malloc(sizeof(dwave::Dwave));
  // static dwave::Dwave dwave;
  // dwave.setAngles(90, 90);
  // dwave.startDwave(argc, argv);
  dwave->startDwave(0, NULL);
  delete dwave;
  return EXIT_SUCCESS;
}
