#pragma once

#include <SDL_events.h>

#include "RoboCatShared.h"

class Client : public Engine {
 public:
  static bool StaticInit();

 protected:
  Client();

  virtual void DoFrame() override;
  virtual void HandleEvent(SDL_Event* inEvent) override;

 private:
};