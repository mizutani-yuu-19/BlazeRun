///////////////////////////////////////////////////
//
// physics
//
////////////////////////////////////////////////////


#ifndef _PHYSICS_H_
#define _PHYSICS_H_

//--------インクルード--------
#include "main.h"

//--------
class CPhysics {
public:
	void CPhysics::InitPhysics(D3DXVECTOR2 acc,D3DXVECTOR2 speed);

	void CPhysics::PosCalc(D3DXVECTOR2* pos);
	void CPhysics::Gravity();
	void CPhysics::airResistance();

	void CPhysics::SetAccel(D3DXVECTOR2 acc);
	void CPhysics::SetSpeed(D3DXVECTOR2 speed);

	D3DXVECTOR2 m_speed;	// 速度
	D3DXVECTOR2 m_accel;	// 加速度
protected:
private:
};



#endif // _PHYSICS_H_
