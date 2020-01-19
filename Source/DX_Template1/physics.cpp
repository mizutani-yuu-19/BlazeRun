///////////////////////////////////////////////////
//
// physics
//
////////////////////////////////////////////////////


//--------�C���N���[�h--------
#include "physics.h"

//--------�萔�}�N��--------
#define GRAVITY				(0.05f)
#define AIRREGISTANCE		(0.005f)

void CPhysics::InitPhysics(D3DXVECTOR2 acc, D3DXVECTOR2 speed) {
	m_speed = speed;
	m_accel = acc;
}

void CPhysics::PosCalc(D3DXVECTOR2* pos) {
	// ���x�̍X�V
	m_speed += m_accel;
	if (m_speed.y > 30.0f) {
		m_speed.y = 30.0f;
	}
	// ���W�̍X�V
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