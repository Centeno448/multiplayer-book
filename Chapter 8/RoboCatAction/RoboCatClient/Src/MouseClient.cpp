#include "MouseClient.h"

#include "TextureManager.h"

MouseClient::MouseClient() {
  mSpriteComponent.reset(new SpriteComponent(this));
  mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("mouse"));
}