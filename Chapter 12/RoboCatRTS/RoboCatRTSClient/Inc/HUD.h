#pragma once
// I take care of rendering things!

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <string>

#include "RoboMath.h"

class HUD {
 public:
  static void StaticInit();
  static std::unique_ptr<HUD> sInstance;

  void Render();

  void SetPlayerHealth(int inHealth) { mHealth = inHealth; }

 private:
  HUD();

  void RenderTurnNumber();
  void RenderBandWidth();
  void RenderScoreBoard();
  void RenderHealth();
  void RenderCountdown();
  void RenderText(const std::string& inStr, const Vector3& origin,
                  const Vector3& inColor);

  Vector3 mBandwidthOrigin;
  Vector3 mRoundTripTimeOrigin;
  Vector3 mScoreBoardOrigin;
  Vector3 mScoreOffset;
  Vector3 mHealthOffset;
  Vector3 mTimeOrigin;
  SDL_Rect mViewTransform;

  TTF_Font* mFont;
  int mHealth;
};
