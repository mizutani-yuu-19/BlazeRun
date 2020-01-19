// Õ“Ë”»’è
#include "collision.h"

// ‹éŒ`“¯m‚ÌÕ“Ë”»’è
bool CollisionRect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) {
	return (Ax <= Bx + Bw && Bx <= Ax + Aw && Ay <= By + Bh && By <= Ay + Ah);
}
// ‰~“¯m‚ÌÕ“Ë”»’è
bool CollisionCircle(float Ax, float Ay, float Ar, float Bx, float By, float Br) {
	float dx = Ax - Bx;
	float dy = Ay - By;
	float r = Ar + Br;
	return (dx*dx + dy*dy <= r*r);
}
// ü‚Æü
bool CollisionLineLine(float A1x, float A1y, float A2x, float A2y, float B1x, float B1y, float B2x, float B2y) {
	{
		float baseX = B2x - B1x;
		float baseY = B2y - B1y;
		float sub1X = A1x - B1x;
		float sub1Y = A1y - B1y;
		float sub2X = A2x - B1x;
		float sub2Y = A2y - B1y;

		float bs1 = baseX * sub1Y - baseY * sub1X;
		float bs2 = baseX * sub2Y - baseY * sub2X;
		float re = bs1 * bs2;
		if (re > 0) {
			return false;
		}
	}
	{
		float baseX = A2x - A1x;
		float baseY = A2y - A1y;
		float sub1X = B1x - A1x;
		float sub1Y = B1y - A1y;
		float sub2X = B2x - A1x;
		float sub2Y = B2y - A1y;

		float bs1 = baseX * sub1Y - baseY * sub1X;
		float bs2 = baseX * sub2Y - baseY * sub2X;
		float re = bs1 * bs2;
		if (re > 0) {
			return false;
		}
	}
	return true;
}
// ‹éŒ`‚Æü
bool CollisionRectLine(float left, float top, float right, float bottom, float x1, float y1, float x2, float y2) {
	if (CollisionLineLine(left, top, right, top, x1, y1, x2, y2)) 
		return true; 
	if (CollisionLineLine(right, top, right, bottom, x1, y1, x2, y2)) 
		return true; 
	if (CollisionLineLine(right, bottom, left, bottom, x1, y1, x2, y2)) 
		return true; 
	if (CollisionLineLine(left, bottom, left, top, x1, y1, x2, y2)) 
		return true; 
	
	return false;
}