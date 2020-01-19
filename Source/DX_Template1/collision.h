// Õ“Ë”»’è
#pragma once

#include "main.h"
// ‹éŒ`“¯m‚ÌÕ“Ë”»’è
bool CollisionRect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh);
// ‰~“¯m‚ÌÕ“Ë”»’è
bool CollisionCircle(float Ax, float Ay, float Ar, float Bx, float By, float Br);
// ü‚Æü‚ÌÕ“Ë”»’è
bool CollisionLineLine(float A1x, float A1y, float A2x, float A2y, float B1x, float B1y, float B2x, float B2y);
// ‹éŒ`‚Æü
bool CollisionRectLine(float left, float top, float right, float bottom, float x1, float y1, float x2, float y2);
