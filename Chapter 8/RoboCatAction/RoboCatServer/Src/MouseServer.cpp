#include "MouseServer.h"

MouseServer::MouseServer() {}

void MouseServer::HandleDying() {
  NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool MouseServer::HandleCollisionWithCat(GameObject* inObj) {
  RoboCat* inCat = dynamic_cast<RoboCat*>(inObj);
  // kill yourself!
  SetDoesWantToDie(true);

  ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);

  return false;
}
