#include "Dwave.hpp"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(int argc, char** argv) {
  // dwave::Dwave dwave;
  dwave::Dwave* dwave = new dwave::Dwave();
  // dwave::Dwave* dwave = (dwave::Dwave*)malloc(sizeof(dwave::Dwave));
  // static dwave::Dwave dwave;
  // dwave.startDwave(argc, argv);
  // dwave->setQuat(0.41003194468231546, 0.14182406485987478, -0.90097710235425, 0.00390625);
  dwave->startDwave(0, NULL);
  // for (int i = 3; i > 0; --i) {
  //   std::cout << i << std::endl;
  //   std::this_thread::sleep_for (std::chrono::seconds(1));
  // }
  // dwave->startDwave(0, NULL);
  // dwave->stopDwave();
  delete dwave;
  return EXIT_SUCCESS;
}
