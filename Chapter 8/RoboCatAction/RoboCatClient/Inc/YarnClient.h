#pragma once

#include "RoboCatShared.h"
#include "SpriteComponent.h"

class YarnClient : public Yarn {
 public:
  static GameObjectPtr StaticCreate() {
    return GameObjectPtr(new YarnClient());
  }

  virtual void Read(InputMemoryBitStream& inInputStream) override;
  virtual bool HandleCollisionWithCat(GameObject* inCat) override;

 protected:
  YarnClient();

 private:
  SpriteComponentPtr mSpriteComponent;
};
