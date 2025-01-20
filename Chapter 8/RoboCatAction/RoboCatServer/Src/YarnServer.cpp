#include "YarnServer.h"

#include "RoboCatServer.h"

YarnServer::YarnServer() {
  // yarn lives a second...
  mTimeToDie = Timing::sInstance.GetFrameStartTime() + 1.f;
}

void YarnServer::HandleDying() {
  NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void YarnServer::Update() {
  Yarn::Update();

  if (Timing::sInstance.GetFrameStartTime() > mTimeToDie) {
    SetDoesWantToDie(true);
  }
}

bool YarnServer::HandleCollisionWithCat(GameObject* inObj) {
  RoboCat* inCat = dynamic_cast<RoboCat*>(inObj);
  if (inCat->GetPlayerId() != GetPlayerId()) {
    // kill yourself!
    SetDoesWantToDie(true);

    static_cast<RoboCatServer*>(inCat)->TakeDamage(GetPlayerId());
  }

  return false;
}
