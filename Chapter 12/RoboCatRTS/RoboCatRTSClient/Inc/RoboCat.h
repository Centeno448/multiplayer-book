#pragma once

#include <memory>

#include "GameObject.h"
#include "MemoryBitStream.h"
#include "NetworkManager.h"
#include "RoboMath.h"
#include "SpriteComponent.h"

class RoboCat : public GameObject {
 public:
  CLASS_IDENTIFICATION('RCAT', GameObject)

  enum RoboCatState {
    RC_IDLE,
    RC_MOVING,
    RC_ATTACK,
  };

  static GameObjectPtr StaticCreate() {
    return NetworkManager::sInstance->RegisterAndReturn(new RoboCat());
  }

  virtual RoboCat* GetAsCat() { return this; }

  virtual void Update(float inDeltaTime) override;
  void UpdateIdleState(float inDeltaTime);
  void UpdateMovingState(float inDeltaTime);
  void UpdateAttackState(float inDeltaTime);
  // returns true if the move is done
  bool MoveToLocation(float inDeltaTime, const Vector3& inLocation);
  void UpdateRotation(const Vector3& inTarget);
  void EnterMovingState(const Vector3& inTarget);
  void EnterAttackState(uint32_t inTargetNetId);
  void TakeDamage(GameObjectPtr inFromCat, int inDmgAmount);
  virtual void HandleDying() override;

  RoboCat();

  virtual void WriteForCRC(OutputMemoryBitStream& inStream) override;

 private:
  Vector3 mMoveLocation;
  SpriteComponentPtr mSpriteComponent;

  /// move down here for padding reasons...
  int mHealth;
  RoboCatState mState;
  uint32_t mTargetNetId;
  GameObjectPtr mTargetCat;
  float mTimeSinceLastAttack;
};

typedef std::shared_ptr<RoboCat> RoboCatPtr;
