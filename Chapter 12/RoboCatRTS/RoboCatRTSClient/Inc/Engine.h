#pragma once

#include <SDL_events.h>

#include <memory>

class Engine {
 public:
  static bool StaticInit();
  virtual ~Engine();
  static std::unique_ptr<Engine> sInstance;

  virtual int Run();
  void SetShouldKeepRunning(bool inShouldKeepRunning) {
    mShouldKeepRunning = inShouldKeepRunning;
  }
  virtual void HandleEvent(SDL_Event* inEvent);

 protected:
  Engine();

  virtual void DoFrame();

 private:
  int DoRunLoop();

  bool mShouldKeepRunning;
};
