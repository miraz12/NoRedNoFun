#pragma once

#include <iostream>
#include <vector>

enum EntityType { UNKNOWN, WEAPON };

struct VisualEntity {
  float distance{0.0f};
  float directionX{1.0f};
  float directionY{1.0f};
  int entityHit{-1};
  EntityType type{EntityType::UNKNOWN};
};

class BotInterface {
public:
  virtual void print() = 0;
  virtual void update(float dt, std::vector<VisualEntity> *eyes) = 0;
  virtual void actionMove(void (*f)(unsigned int key, BotInterface *bot)) = 0;
  virtual void actionFire(void (*f)(BotInterface *bot)) = 0;
  virtual void actionLookAt(void (*f)(int x, int y, BotInterface *bot)) = 0;
  virtual void actionLookInDirection(void (*f)(float x, float y,
                                               BotInterface *bot)) = 0;

  unsigned int m_id{0};
};
