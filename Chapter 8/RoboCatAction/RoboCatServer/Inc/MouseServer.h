#pragma once

#include "NetworkManagerServer.h"
#include "RoboCatShared.h"

class MouseServer : public Mouse {
 public:
  static GameObjectPtr StaticCreate() {
    return NetworkManagerServer::sInstance->RegisterAndReturn(
        new MouseServer());
  }
  void HandleDying() override;
  virtual bool HandleCollisionWithCat(GameObject* inObj) override;

 protected:
  MouseServer();
};