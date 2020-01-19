//----------�C���N���[�h-----------
#include "burn.h"
#include "collision.h"
//--------�萔�}�N��---------
#define	MAX_BURN	(5000)
#define NEXT_BURN_TIME	(0.01f)

//--------�O���[�o���ϐ�---------
// 
static CBurn		g_burn[MAX_BURN];
// ����
static bool			g_bExist[MAX_BURN];
// �f�o�C�X
//static LPDIRECT3DDEVICE9	g_pD3DDevice;

//---------�v���g�^�C�v-----------

//---------�N���X---------
void CBurn::InitBurn(D3DXVECTOR2 pos, float width, float height, int num, bool bBurn) {
	m_pos = pos;
	m_width = width;
	m_height = height;
	m_num = num;
	m_bBurn = bBurn;
}

void CBurn::UninitBurn() {
	g_bExist[m_num] = false;
	m_bBurn = false;
	m_burnTime = 0;
	m_pos = D3DXVECTOR2(9999, 9999);
}

void CBurn::UpdateBurn() {
	if (m_bBurn)
		m_burnTime++;
	if (m_pos.x > SCREEN_WIDTH)	return;
	// �������R���Ă��Ȃ�������
	if (!m_bBurn) {
		// ���͂�burn���R���Ă����玩����R�₷
		for (int i = 0; i < MAX_BURN; i++) {
			if (!g_bExist[i])	continue;	// ���݂��Ă��Ȃ�
			if (!g_burn[i].m_bBurn)	continue;	// �R���Ă��Ȃ�
			if (g_burn[i].m_burnTime < NEXT_BURN_TIME*60.0f)	continue;

			// �����Ƒ��肪�G��Ă�����
			if (CollisionRect(m_pos.x - m_width / 2.0f, m_pos.y - m_height / 2.0f, m_width, m_height, g_burn[i].m_pos.x - g_burn[i].m_width / 2.0f, g_burn[i].m_pos.y - g_burn[i].m_height / 2.0f, g_burn[i].m_width, g_burn[i].m_height)) {
				m_bBurn = true;
				break;
			}
		}
	}
	//if (m_pos.x < VANISHING_POINT) {
	//	g_bExist[m_num] = false;
	//}
}

void CBurn::DrawBurn() {

}

//---------�֐�------------

void InitBurn() {

}
void UninitBurn() {
	for (int i = 0; i < MAX_BURN; i++)
		g_bExist[i] = false;
}

void UpdateBurn() {
	for (int i = 0; i < MAX_BURN; i++) {
		if (!g_bExist[i])	continue;

		g_burn[i].UpdateBurn();
	}
}

void DrawBurn() {

}

// �R���鐫�������
// �߂�l�̓Z�b�g�����ԍ�
int CreateBurn(D3DXVECTOR2 pos, float width, float height, bool bBurn) {
	for (int i = 0; i < MAX_BURN; i++) {
		if (g_bExist[i])	continue;

		g_burn[i].InitBurn(pos, width, height, i, bBurn);
		g_bExist[i] = true;
		return i;
	}
}

void DeleteBurn(int num) {
	g_burn[num].UninitBurn();
}

// �R���Ă���ʒu���X�V
// ���t���[���Ăяo���Ă�������
void SetBurnPos(int num, D3DXVECTOR2 pos) {
	g_burn[num].m_pos = pos;
}

// �������R���Ă��邩���Q�b�g
bool GetBurn(int num) {
	return g_burn[num].m_bBurn;
}