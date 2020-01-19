///////////////////////////////////////////////////
//
// fireworks
//
///////////////////////////////////////////////////

//--------�C���N���[�h--------
#include "fireworks.h"
#include "collision.h"
#include "light.h"
#include "burn.h"

//--------�萔�}�N��---------
#define FIREWORKS_BOX_WIDTH (50)
#define FIREWORKS_BOX_HEIGHT (50)

#define FIREWORKS_SEED_WIDTH (50)
#define FIREWORKS_SEED_HEIGHT (50)

#define FIREWORKS_PARTICLE_WIDTH (20)
#define FIREWORKS_PARTICLE_HEIGHT (20)

#define FIREWORKS_PARTICLE_SPEED (10)

#define FIREWORKS_SEED_TIME			(0.3f)	// �b
#define FIREWORKS_PARTICLE_MOVETIME (0.4f)	// �b
#define FIREWORKS_PARTICLE_TIME		(1.0f)	// �b

enum {
	NUM_FIREWORKS_BOX,
	NUM_FIREWORKS_SEED,
	NUM_FIREWORKS_PARTICLE,
	NUM_FIREWORKS_MAX,
};
//-------�O���[�o���ϐ�---------
// �e�N�X�`��
static LPDIRECT3DTEXTURE9	g_pTextureBox;
static LPDIRECT3DTEXTURE9	g_pTextureSeed;
static LPDIRECT3DTEXTURE9	g_pTextureParticle;
// �N���X
static CFireworks			g_Fireworks[MAX_FIREWORKS];	// �ԉ�
// ����
static bool					g_bExist[MAX_FIREWORKS];
//--------�N���X---------
// �ԉ�
void CFireworks::InitFireworks(D3DXVECTOR2 pos, int num) {
	pos.x += FIREWORKS_BOX_WIDTH / 2;
	pos.y -= FIREWORKS_BOX_HEIGHT / 2;
	m_FireworksBoxSprite.InitSprite(pos, FIREWORKS_BOX_WIDTH, FIREWORKS_BOX_HEIGHT, 1, 1);
	int H = rand() % 360;							// �J���[
	m_FireworksSeedSprite.InitSprite(pos, FIREWORKS_SEED_WIDTH, FIREWORKS_SEED_HEIGHT, 1, 1);
	m_FireworksSeedSprite.SetColor(HSVConvert(H, 100, 50, 255));
	for (int i = 0; i < MAX_FIRE_PARTICLE; i++) {
		m_FireworksParticleSprite[i].InitSprite(pos, FIREWORKS_PARTICLE_WIDTH, FIREWORKS_PARTICLE_HEIGHT, 1, 1);
		m_FireworksParticleSprite[i].SetColor(HSVConvert(H + rand() % 100 - 50, 100, 50, 255));
	}
	m_pat = NUM_FIREWORKS_BOX;
	m_num = num;
	m_time = 0.0f;
	m_bFire = false;
	// �R���Z�b�g
	m_SeedBurnNum = CreateBurn(m_FireworksSeedSprite.m_pos, FIREWORKS_SEED_WIDTH, FIREWORKS_SEED_HEIGHT, false);
}

void CFireworks::UninitFireworks() {
	g_bExist[m_num] = false;
	m_bFire = false;
	if (m_SeedBurnNum != 99999)
		DeleteBurn(m_SeedBurnNum);
}
void CFireworks::UpdateFireworks() {
	// �X�N���[���ɍ��킹�Ĉړ�
	m_FireworksBoxSprite.m_pos.x -= g_scrollSpeed;
	// SEED�ʒu�ύX
	m_FireworksSeedSprite.m_pos.x -= g_scrollSpeed;
	// BURN�ʒu�X�V
	if (m_SeedBurnNum != 99999)
		SetBurnPos(m_SeedBurnNum, m_FireworksSeedSprite.m_pos);
	switch (m_pat)
	{
	case NUM_FIREWORKS_BOX:
		// �R������
		if (m_SeedBurnNum != 99999)
			if (GetBurn(m_SeedBurnNum) && !m_bFire) {
				PlaySound(SOUND_LABEL_SE_FIREWORKSSHOT);
				m_bFire = true;
				// �p�^�[���؂�ւ�
				m_pat = NUM_FIREWORKS_SEED;
				// ����������
				m_SeedPhysics.InitPhysics(D3DXVECTOR2(0, 0), D3DXVECTOR2(10.0f, -15.0f));
				// ���˂��甚���܂ł̎��Ԑݒ�
				m_time = FIREWORKS_SEED_TIME * 60.0f;
			}
		if (m_FireworksBoxSprite.m_pos.x < VANISHING_POINT) {
			UninitFireworks();
		}
		break;
	case NUM_FIREWORKS_SEED:
		// SEED�ʒu�ύX
		m_SeedPhysics.Gravity();
		m_SeedPhysics.airResistance();
		m_SeedPhysics.PosCalc(&m_FireworksSeedSprite.m_pos);
		// ���ԃ}�C�i�X
		m_time -= 1.0f;
		// ��]
		m_FireworksSeedSprite.m_angleDegree += 50;
		// ���Ԃ�������
		if (m_time <= 0.0f) {
			// �p�^�[���؂�ւ�
			m_pat = NUM_FIREWORKS_PARTICLE;
			for (int i = 0; i < MAX_FIRE_PARTICLE; i++) {
				// ���݈ʒu���甭��
				m_FireworksParticleSprite[i].m_pos = m_FireworksSeedSprite.m_pos;
				// �����x�ݒ�
				int angle = rand() % 360;
				float speed = (rand() % (FIREWORKS_PARTICLE_SPEED * 100) / 100.0f);
				m_ParticlePhysics[i].InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2((cos(angle*PI / 180)*speed), (sin(angle*PI / 180)*speed)));
				// �R���Z�b�g
				m_ParticleBurnNum[i] = CreateBurn(m_FireworksParticleSprite[i].m_pos, FIREWORKS_PARTICLE_WIDTH, FIREWORKS_PARTICLE_HEIGHT, true);
				//DeleteBurn(m_SeedBurnNum);
			}
			// �������������܂ł̎��Ԑݒ�
			m_time = FIREWORKS_PARTICLE_TIME * 60.0f;
			PlaySound(SOUND_LABEL_SE_FIREWORKSPAN);
		}
		break;
	case NUM_FIREWORKS_PARTICLE:
		for (int i = 0; i < MAX_FIRE_PARTICLE; i++) {
			m_FireworksParticleSprite[i].m_pos.x -= g_scrollSpeed;
			//m_ParticlePhysics[i].Gravity();
			m_ParticlePhysics[i].airResistance();
			m_ParticlePhysics[i].PosCalc(&m_FireworksParticleSprite[i].m_pos);
			// ��]
			m_FireworksParticleSprite[i].m_angleDegree += 50;
			if (m_time <= FIREWORKS_PARTICLE_MOVETIME * 60.0f) {
				m_ParticlePhysics[i].InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
				m_FireworksParticleSprite[i].m_color -= D3DCOLOR_RGBA(0, 0, 0, 10);
			}
			// BURN�ʒu�X�V
			SetBurnPos(m_ParticleBurnNum[i], m_FireworksParticleSprite[i].m_pos);
		}
		// ���ԃ}�C�i�X
		m_time -= 1.0f;
		// ���Ԃ�������
		if (m_time <= 0.0f) {
			for (int i = 0; i < MAX_FIRE_PARTICLE; i++) {
				DeleteBurn(m_ParticleBurnNum[i]);
			}
			DeleteBurn(m_SeedBurnNum);
			m_SeedBurnNum = 99999;
			m_pat = NUM_FIREWORKS_BOX;
		}
		break;
	default:
		break;
	}
}
void CFireworks::DrawFireworks() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_FireworksBoxSprite.DrawSprite(g_pTextureBox);							// ��
	switch (m_pat)
	{
	case NUM_FIREWORKS_BOX:
		break;
	case NUM_FIREWORKS_SEED:
		// ���Z�����������ɕύX
		SetRenderMode(BLEND_ADDITION_TRANSLUCENT);
		m_FireworksSeedSprite.DrawSprite(g_pTextureSeed);					// ��
		if (!g_bDeleteLight)
			SetLight(m_FireworksSeedSprite.m_pos, D3DXVECTOR2(5, 5));			// ��̈ʒu�Ƀ��C�g
		break;
	case NUM_FIREWORKS_PARTICLE:
		// ���Z�����������ɕύX
		SetRenderMode(BLEND_ADDITION_TRANSLUCENT);
		for (int i = 0; i < MAX_FIRE_PARTICLE; i++) {
			m_FireworksParticleSprite[i].DrawSprite(g_pTextureParticle);		// �΂̃p�[�e�B�N��
		}
		if (!g_bDeleteLight)
			SetLight(m_FireworksSeedSprite.m_pos, D3DXVECTOR2(19, 19));	// �΂̈ʒu�Ƀ��C�g
		break;
	default:
		break;
	}
}

//===============�֐�=================
void InitFireworks(void) {
	g_pTextureBox = SetTexture("data/texture/fireworks_box.png");
	g_pTextureSeed = SetTexture("data/texture/fireworks_particle.png");
	g_pTextureParticle = SetTexture("data/texture/fireworks_particle.png");
}

void UninitFireworks(void) {
	for (int i = 0; i < MAX_FIREWORKS; i++)
		g_bExist[i] = false;
	g_pTextureBox->Release();
	g_pTextureBox = NULL;
	g_pTextureSeed->Release();
	g_pTextureSeed = NULL;
	g_pTextureParticle->Release();
	g_pTextureParticle = NULL;
}

void UpdateFireworks() {
	for (int i = 0; i < MAX_FIREWORKS; i++) {
		// �g�p���Ă�����X�V
		if (!g_bExist[i])	continue;
		g_Fireworks[i].UpdateFireworks();
	}
}

void CreateFireworks(D3DXVECTOR2 pos) {
	for (int i = 0; i < MAX_FIREWORKS; i++) {
		if (g_bExist[i])		continue;

		g_Fireworks[i].InitFireworks(pos, i);
		g_bExist[i] = true;
		return;
	}
}

void DrawFireworks() {
	for (int i = 0; i < MAX_FIREWORKS; i++) {
		if (!g_bExist[i])	continue;
		g_Fireworks[i].DrawFireworks();
	}
}