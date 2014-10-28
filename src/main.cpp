#include <iostream>
#include "SDL.h"
using namespace std;

int main() {
  std::cout << "Hello world!" << std::endl;

  SDL_Init(SDL_INIT_HAPTIC);
  SDL_Quit();

  return 0;
}
