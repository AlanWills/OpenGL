#pragma once

#include "GLHeaders.h"

class Component
{

public:
  Component();
  virtual ~Component();

  virtual void init() { }
  virtual void update() = 0;
  virtual void draw(GLfloat elapsedTime) const = 0;
};

