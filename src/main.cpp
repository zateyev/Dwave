#include "Dwave.hpp"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(int argc, char** argv) {
  // dwave::Dwave dwave;
  dwave::Dwave* dwave = new dwave::Dwave();
  dwave->setDatasetPath("../noisig_ntj.raw");
  dwave->startDwave(0, NULL);
  // std::thread first(&dwave::Dwave::startDwave, dwave, 0, argv);
  // for (int i = 3; i > 0; --i) {
  //   std::cout << i << std::endl;
  //   std::this_thread::sleep_for (std::chrono::seconds(1));
  // }
  // dwave->setCameraSettings(3.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // std::thread second(&dwave::Dwave::setCameraSettings, dwave, 3.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  delete dwave;
  return EXIT_SUCCESS;
}
