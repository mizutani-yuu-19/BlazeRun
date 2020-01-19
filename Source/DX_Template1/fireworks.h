///////////////////////////////////////////////////
//
// fireworks
//
////////////////////////////////////////////////////

#ifndef _FIREWORKS_H_
#define _FIREWORKS_H_

//--------�C���N���[�h--------
#include "main.h"
#include "sprite.h"
#include "physics.h"
#include "common.h"

//--------�萔�}�N��---------
#define MAX_FIREWORKS (10)
#define MAX_FIRE_PARTICLE (1000)
#define FIRE_PARTICLE_SIZE (2.0f)

//--------�N���X----------

class CFireworks {
public:
	void CFireworks::InitFireworks(D3DXVECTOR2 pos,int num);
	void CFireworks::UninitFireworks();
	void CFireworks::UpdateFireworks();
	void CFireworks::DrawFireworks();
private:
	float m_time;
	int m_pat;
	int m_num;
	int m_SeedBurnNum;
	int m_ParticleBurnNum[MAX_FIRE_PARTICLE];
	bool m_bFire;
	// �X�v���C�g
	CSprite		m_FireworksBoxSprite;
	CSprite		m_FireworksSeedSprite;
	CSprite		m_FireworksParticleSprite[MAX_FIRE_PARTICLE];
	// ����
	CPhysics	m_SeedPhysics;
	CPhysics	m_ParticlePhysics[MAX_FIRE_PARTICLE];
protected:
};

//---------�v���g�^�C�v---------
void InitFireworks(); 
void UninitFireworks(); 
void CreateFireworks(D3DXVECTOR2 pos);
void UpdateFireworks();
void DrawFireworks();
#endif // !_FIREWORKS_H_