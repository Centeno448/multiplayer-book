#include <SDL.h>

#include "Engine.h"

#if _WIN32
#include "Windows.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (Engine::StaticInit()) {
    return Engine::sInstance->Run();
  } else {
    SDL_Quit();

    // error
    return 1;
  }
}
#else
const char** __argv;
int __argc;
int main(int argc, const char** argv) {
  __argc = argc;
  __argv = argv;
  if (Engine::StaticInit()) {
    return Engine::sInstance->Run();
  } else {
    // error
    return 1;
  }
}
#endif
