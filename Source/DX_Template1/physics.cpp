///////////////////////////////////////////////////
//
// physics
//
////////////////////////////////////////////////////


//--------インクルード--------
#include "physics.h"

//--------定数マクロ--------
#define GRAVITY				(0.05f)
#define AIRREGISTANCE		(0.005f)

void CPhysics::InitPhysics(D3DXVECTOR2 acc, D3DXVECTOR2 speed) {
	m_speed = speed;
	m_accel = acc;
}

void CPhysics::PosCalc(D3DXVECTOR2* pos) {
	// 速度の更新
	m_speed += m_accel;
	if (m_speed.y > 30.0f) {
		m_speed.y = 30.0f;
	}
	// 座標の更新
	*pos += m_speed;
}

void CPhysics::Gravity()
{
	m_accel.y += GRAVITY;
}

void CPhysics::airResistance() {
	//m_accel.y -= AIRREGISTANCE;
	//m_accel += D3DXVECTOR2((rand() % 100 - 50) / 10000.0f, (rand() % 100 - 50) / 10000.0f);
}

void CPhysics::SetAccel(D3DXVECTOR2 acc) {
	m_accel = acc;
}
void CPhysics::SetSpeed(D3DXVECTOR2 speed) {
	m_speed = speed;
}