// �v���C���[����
#include "player.h"
#include "input.h"
#include "light.h"
#include "burn.h"
#include "oil.h"
#include "wall.h"
#include "ground.h"
#include "board.h"
#include "scene.h"
#include "goal.h"
#include "gameover.h"
#include "clear.h"
#include "tutorial.h"
#include "collision.h"
//----------�}�N����`-----------
// �e�N�X�`�� �p�X��
#define PATH_TEXTURE_PLAYER	"data/texture/player.png"
#define PATH_TEXTURE_PLAYER_FIRE	"data/texture/playerfire.png"
// �v���C���[�̕W���w�l
#define PLAYER_DEFAULT_X	(150)
// �e�N�X�`��������
#define PLAYER_DIV_U		4	// ��������
#define PLAYER_DIV_V		4	// �c������
// �u���C�Y�̏�����
#define NUM_BLAZE			(7)
#define MAX_BLAZE_CNT		(99)
// ���C�g�̊�T�C�Y
#define STANDARD_PLAYER_LIGHT	(5)
// �W�����v��
#define PLAYER_JUMP				(-15)
#define PLAYER_SECOND_JUMP		(-8)
// �X�s�[�h�A�b�v
#define PLAYER_UPSPEED			(5)
#define BLAZE_CNT_UP			(3)
// �A�j���[�V�����t���[�����[�g
#define FRAME_RUN			(7)
#define FRAME_JUMP			(4)
#define FRAME_BLAZE			(8)

#define FIRE_SIZE			(200)
//----------�O���[�o���ϐ�----------
// �v���C���[
static CPlayer					g_player;

// �e�N�X�`��
static LPDIRECT3DTEXTURE9		g_pTexturePlayer;
static LPDIRECT3DTEXTURE9		g_pTexturePlayerFire;
static LPDIRECT3DTEXTURE9		g_pTextureMark;
static LPDIRECT3DTEXTURE9		g_pTextureMouseLeft;
static LPDIRECT3DTEXTURE9		g_pTextureMouseRight;
static LPDIRECT3DTEXTURE9		g_pTextureMouse;

static CSprite	g_MarkSprite;
static CSprite	g_LeftSprite;
static CSprite	g_RightSprite;
static CSprite	g_MouseSprite;
//-------�N���X----------
void CPlayer::InitPlayer(D3DXVECTOR2 pos) {
	m_PlayerSprite.InitSprite(pos, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DIV_U, PLAYER_DIV_V);
	m_PlayerFireSprite.InitSprite(pos, FIRE_SIZE, FIRE_SIZE, 8, 4);
	m_PlayerFireSprite.m_scale = D3DXVECTOR2(0.1f, 0.1f);
	m_prevPos = pos;
	m_PlayerPhysics.InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_blazeCnt = NUM_BLAZE;
	m_bStart = false;
	m_animRunCnt = 0;
	m_animbJumpCnt = 0;
	m_animbBlazeCnt = 0;
	m_groundPosY = 999;
	g_scrollSpeed = 0;
}

void CPlayer::StartPlayer() {
	m_PlayerFireSprite.m_scale.x += 0.05f;
	m_PlayerFireSprite.m_scale.y += 0.05f;
	if (m_PlayerFireSprite.m_scale.x > 3.0f) {
		m_bStart = true;
		m_PlayerPhysics.SetSpeed(D3DXVECTOR2(0, PLAYER_JUMP));
		g_scrollSpeed = SCROLL_SPEED;
	}
}

void CPlayer::UninitPlayer() {
	//DeleteBurn(m_BurnNum);
	for (int i = 0; i < MAX_BLAZE; i++)
		m_bBlazeExist[i] = false;
}

void CPlayer::UpdatePlayer() {
	static int time = 0;
	time++;
	m_PlayerFireSprite.m_patNum = time / 3 % 32;
	if (!m_bStart) {
		StartPlayer();
		return;
	}
	m_PlayerFireSprite.m_pos.x -= g_scrollSpeed;
	bool bPress = false;
	m_bGround = false;

	if (GetScene() != SCENE_TUTORIAL) {
		// �W�����v
		if (DIGetMouseTrigger(0) && !m_bJump) {
			m_bJump = true;
			bPress = true;
			m_bGround = false;
			m_PlayerPhysics.SetSpeed(D3DXVECTOR2(0, PLAYER_JUMP));
			m_animbJumpCnt = 0;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
		if (DIGetMouseTrigger(0) && m_bJump && !bPress && !m_bSecondJump) {
			m_bSecondJump = true;
			m_PlayerPhysics.m_accel.y = 0;
			m_PlayerPhysics.m_speed.y = PLAYER_SECOND_JUMP;
			m_animbJumpCnt = 0;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
		// �u���C�Y
		if (DIGetMouseTrigger(1) && m_blazeCnt > 0 && m_animbBlazeCnt == 0) {
			m_blazeCnt--;
			for (int i = 0; i < MAX_BLAZE; i++) {
				if (m_bBlazeExist[i])	continue;
				m_PlayerBlaze[i].InitBlaze(m_PlayerSprite.m_pos);
				m_animbBlazeCnt = 1;
				m_bBlazeExist[i] = true;
				PlaySound(SOUND_LABEL_SE_BLAZE);
				break;
			}
		}
	}
	// �`���[�g���A���̎�
	else {
		if (GetTutorialPush() == false) {
			// �u���C�Y
			switch (GetTutorialButton())
			{
			case 1:
				if (DIGetMouseTrigger(1) && CollisionCircle(GetMousePos().x, GetMousePos().y, 0.1f, g_MarkSprite.m_pos.x, g_MarkSprite.m_pos.y, 10)) {
					m_blazeCnt--;
					for (int i = 0; i < MAX_BLAZE; i++) {
						if (m_bBlazeExist[i])	continue;
						m_PlayerBlaze[i].InitBlaze(m_PlayerSprite.m_pos);
						m_animbBlazeCnt = 1;
						m_bBlazeExist[i] = true;
						PlaySound(SOUND_LABEL_SE_BLAZE);
						break;
					}
					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;
				// �W�����v
			case 2:
				if (DIGetMouseTrigger(0)) {
					if (DIGetMouseTrigger(0) && !m_bJump) {
						m_bJump = true;
						bPress = true;
						m_bGround = false;
						m_PlayerPhysics.SetSpeed(D3DXVECTOR2(0, PLAYER_JUMP));
						m_animbJumpCnt = 0;
						PlaySound(SOUND_LABEL_SE_JUMP);
					}

					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;
				// 2�i�W�����v�P�����
			case 3:
				if (DIGetMouseTrigger(0)) {
					if (DIGetMouseTrigger(0) && !m_bJump) {
						m_bJump = true;
						bPress = true;
						m_bGround = false;
						m_PlayerPhysics.SetSpeed(D3DXVECTOR2(0, PLAYER_JUMP));
						m_animbJumpCnt = 0;
						PlaySound(SOUND_LABEL_SE_JUMP);
					}
					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;

				// 2�i�W�����v�Q�����
			case 4:
				if (DIGetMouseTrigger(0)) {
					if (DIGetMouseTrigger(0) && m_bJump && !bPress && !m_bSecondJump) {
						m_bSecondJump = true;
						m_PlayerPhysics.m_accel.y = 0;
						m_PlayerPhysics.m_speed.y = PLAYER_SECOND_JUMP;
						m_animbJumpCnt = 0;
						PlaySound(SOUND_LABEL_SE_JUMP);
					}
					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;
				// �����v
			case 5:
				if (DIGetMouseTrigger(1) && CollisionCircle(GetMousePos().x, GetMousePos().y, 0.1f, g_MarkSprite.m_pos.x, g_MarkSprite.m_pos.y, 10)) {
					m_blazeCnt--;
					for (int i = 0; i < MAX_BLAZE; i++) {
						if (m_bBlazeExist[i])	continue;
						m_PlayerBlaze[i].InitBlaze(m_PlayerSprite.m_pos);
						m_animbBlazeCnt = 1;
						m_bBlazeExist[i] = true;
						PlaySound(SOUND_LABEL_SE_BLAZE);
						break;
					}
					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;
				// dainamaito
			case 6:
				if (DIGetMouseTrigger(1) && CollisionCircle(GetMousePos().x, GetMousePos().y, 0.1f, g_MarkSprite.m_pos.x, g_MarkSprite.m_pos.y, 10)) {
					m_blazeCnt--;
					for (int i = 0; i < MAX_BLAZE; i++) {
						if (m_bBlazeExist[i])	continue;
						m_PlayerBlaze[i].InitBlaze(m_PlayerSprite.m_pos);
						m_animbBlazeCnt = 1;
						m_bBlazeExist[i] = true;
						PlaySound(SOUND_LABEL_SE_BLAZE);
						break;
					}
					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;
				// �ԉ�
			case 7:
				if (DIGetMouseTrigger(1) && CollisionCircle(GetMousePos().x, GetMousePos().y, 0.1f, g_MarkSprite.m_pos.x, g_MarkSprite.m_pos.y, 10)) {
					m_blazeCnt--;
					for (int i = 0; i < MAX_BLAZE; i++) {
						if (m_bBlazeExist[i])	continue;
						m_PlayerBlaze[i].InitBlaze(m_PlayerSprite.m_pos);
						m_animbBlazeCnt = 1;
						m_bBlazeExist[i] = true;
						PlaySound(SOUND_LABEL_SE_BLAZE);
						break;
					}
					TutorialPlus();
					SetTutorialPush(true);
					g_scrollSpeed = SCROLL_SPEED;
				}
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < MAX_BLAZE; i++) {
		if (!m_bBlazeExist[i]) continue;
		m_PlayerBlaze[i].UpdateBlaze();
		if (m_PlayerBlaze[i].m_time <= 0) {
			m_PlayerBlaze[i].UninitBlaze();
			m_bBlazeExist[i] = false;
		}
	}

	// �ʒu���X�V
	if (!(GetTutorialButton() == 4 && GetTutorialPush() == false)) {
		m_PlayerPhysics.PosCalc(&m_PlayerSprite.m_pos);
	}
	// �I�C���Q�b�g
	if (CollisionOil(m_PlayerSprite.m_pos, PLAYER_COL_WIDTH, PLAYER_COL_HEIGHT)) {
		m_blazeCnt += BLAZE_CNT_UP;
		if (m_blazeCnt > MAX_BLAZE_CNT) {

		}
	}
	// �ʒu�␳
	// ��
	m_noColTime--;
	if (m_noColTime < 0)
		m_noColTime = 0;
	if (m_groundPosY == 999 && !m_noColTime) {
		m_groundPosY = CollisionBoard(D3DXVECTOR2(m_PlayerSprite.m_pos.x, m_PlayerSprite.m_pos.y + PLAYER_HEIGHT / 2.0f - 0.5f), PLAYER_WIDTH, 1.0f);
	}
	if (m_groundPosY != 999) {
		if (m_prevPos.y + PLAYER_HEIGHT / 2 > m_groundPosY) {
			m_PlayerPhysics.InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, -10.0f));
			m_noColTime = 30;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
		else {
			m_PlayerSprite.m_pos.y = m_groundPosY - PLAYER_HEIGHT / 2.0f;
			m_PlayerPhysics.InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
		}
		m_bGround = true;
		m_bJump = false;
		m_bSecondJump = false;
		m_groundPosY = 999;
	}
	// ��
	int workWall;
	if (workWall = CollisionWall(&g_player.m_PlayerSprite.m_pos, PLAYER_WIDTH, PLAYER_HEIGHT)) {
		// ��ɏ��
		if (workWall == 1) {
			m_bJump = false;
			m_bSecondJump = false;
			m_bGround = true;
			m_PlayerPhysics.InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
		}
		// �ǂɓ�����
		if (workWall == 2) {
		}
	}
	// �n��
	int workGround;
	if (workGround = CollisionGround(&g_player.m_PlayerSprite.m_pos, PLAYER_WIDTH, PLAYER_HEIGHT)) {
		// ��ɏ��
		if (workGround == 1) {
			m_bJump = false;
			m_bSecondJump = false;
			m_bGround = true;
			m_PlayerPhysics.InitPhysics(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
		}
		// �ǂɓ�����
		if (workGround == 2) {
		}
	}
	if (!m_bGround) {
		// �d��
		m_bJump = true;
		m_PlayerPhysics.Gravity();
	}

	// ����ʒu�łȂ����
	if (m_PlayerSprite.m_pos.x < PLAYER_DEFAULT_X) {
		m_PlayerSprite.m_pos.x += PLAYER_UPSPEED;
	}

	m_prevPos = m_PlayerSprite.m_pos;
	if (!(GetGameClear() || GetGameOver())) {
		// �ްѵ��ް
		if (m_PlayerSprite.m_pos.x < -PLAYER_WIDTH) {
			SetGameOver(true);
		}
		if (m_PlayerSprite.m_pos.y > SCREEN_HEIGHT + PLAYER_HEIGHT) {
			SetGameOver(true);
		}
		if (CollisionGoal(m_PlayerSprite.m_pos, PLAYER_WIDTH, PLAYER_HEIGHT)) {
			SetGameClear(true);
		}
	}

	// �u���C�Y���̃A�j���[�V����
	if (m_animbBlazeCnt) {
		m_animbBlazeCnt++;
		m_PlayerSprite.m_patNum = m_animbBlazeCnt / FRAME_BLAZE % 2 + PLAYER_DIV_U * 2;
		if (m_animbBlazeCnt > FRAME_BLAZE * 2) {
			m_animbBlazeCnt = 0;
		}
	}
	else {
		// ����A�j���[�V����
		if (!m_bJump) {
			m_animRunCnt++;
			m_PlayerSprite.m_patNum = m_animRunCnt / FRAME_RUN % 4;
		}
		else {
			// �W�����v�A�j���[�V����
			m_animRunCnt = 0;
			if (m_animbJumpCnt < 40) {
				m_animbJumpCnt++;
			}
			m_PlayerSprite.m_patNum = m_animbJumpCnt / 10 % 4 + PLAYER_DIV_U;
		}
	}
}

void CPlayer::DrawPlayer() {
	if (GetGameOver() || GetGameClear()) return;
	SetRenderMode(BLEND_TRANSLUCENT);
	if (m_bStart) {
		m_PlayerSprite.DrawSprite(g_pTexturePlayer);
		for (int i = 0; i < MAX_BLAZE; i++) {
			if (!m_bBlazeExist[i]) continue;
			m_PlayerBlaze[i].DrawBlaze();
		}
		if (!g_bDeleteLight)
			SetLight(m_PlayerSprite.m_pos, D3DXVECTOR2(STANDARD_PLAYER_LIGHT, STANDARD_PLAYER_LIGHT));
	}
	m_PlayerFireSprite.DrawSprite(g_pTexturePlayerFire);
	SetLight(m_PlayerFireSprite.m_pos, D3DXVECTOR2(m_PlayerFireSprite.m_scale.x * 2, m_PlayerFireSprite.m_scale.y * 2));
}

D3DXVECTOR2 CPlayer::GetPos() {
	return m_PlayerSprite.m_pos;
}

int CPlayer::GetBlazeNum() {
	return m_blazeCnt;
}
bool CPlayer::GetStart() {
	return m_bStart;
}


// ����������
void InitPlayer()
{
	g_MarkSprite.InitSprite(D3DXVECTOR2(700, 400), 100, 100, 1, 1);	
	g_MouseSprite.InitSprite(D3DXVECTOR2(750, 450), 100, 100, 1, 1);
	g_RightSprite.InitSprite(D3DXVECTOR2(750, 450), 100, 100, 1, 1);
	g_LeftSprite.InitSprite(D3DXVECTOR2(500, 300), 150, 150, 1, 1);
	if (GetScene() == SCENE_TUTORIAL) {
		g_pTextureMark = SetTexture("data/texture/mark.png");
		g_pTextureMouseLeft = SetTexture("data/texture/left.png");
		g_pTextureMouseRight = SetTexture("data/texture/right.png");
		g_pTextureMouse = SetTexture("data/texture/mouse.png");
	}
	// �e�N�X�`���̓ǂݍ���
	g_pTexturePlayer = SetTexture(PATH_TEXTURE_PLAYER);
	g_pTexturePlayerFire = SetTexture(PATH_TEXTURE_PLAYER_FIRE);
	g_player.InitPlayer(D3DXVECTOR2(PLAYER_DEFAULT_X, 300));
}

// �I������
void UninitPlayer()
{
	g_player.UninitPlayer();
	// �e�N�X�`���̉��
	g_pTexturePlayer->Release();
	g_pTexturePlayer = NULL;

	g_player.UninitPlayer();
}



// �X�V����
void UpdatePlayer()
{
	g_player.UpdatePlayer();
}

// �`�揈��
void DrawPlayer()
{
	g_player.DrawPlayer();
}

D3DXVECTOR2 *GetPlayerPos(void) {
	return &g_player.GetPos();
}
int GetBlazeNum() {
	return g_player.GetBlazeNum();
}
bool GetStart() {
	return g_player.GetStart();
}

void DrawTutrialMark() {
	if (GetTutorialPush() == false) {
		static int time = 70;
		time--;
		if (time == 0) {
			time = 70;
		}
		g_MarkSprite.m_scale = D3DXVECTOR2(0.3f + time * 0.007f, 0.3f + time * 0.007f);
		// �u���C�Y
		switch (GetTutorialButton())
		{
		case 1:
		{
			static int i = 100;
			i -= 2;
			if (i < -50) {
				i = 100;
			}
			g_MarkSprite.DrawSprite(g_pTextureMark);
			if (i < 0) {
				g_RightSprite.InitSprite(D3DXVECTOR2(750, 450), 100, 100, 1, 1);
				g_RightSprite.DrawSprite(g_pTextureMouseRight);
			}
			else {
				g_MouseSprite.InitSprite(D3DXVECTOR2(750 + i, 450 + i), 100, 100, 1, 1);
				g_MouseSprite.DrawSprite(g_pTextureMouse);
			}
			break;
		}
		// �W�����v
		case 2:
			g_LeftSprite.InitSprite(D3DXVECTOR2(500, 300), 150, 150, 1, 1);
			g_LeftSprite.DrawSprite(g_pTextureMouseLeft);
			break;
			// 2�i�W�����v�P�����
		case 3:
			g_LeftSprite.DrawSprite(g_pTextureMouseLeft);
			break;
			// 2�i�W�����v�Q�����
		case 4:
			g_LeftSprite.DrawSprite(g_pTextureMouseLeft);
			break;
			// �����v
		case 5:
		{
			static int i = 100;
			i -= 2;
			if (i < -50) {
				i = 100;
			}
			g_MarkSprite.m_pos = D3DXVECTOR2(700, 200);
			g_MarkSprite.DrawSprite(g_pTextureMark);
			if (i < 0) {
				g_RightSprite.m_pos = D3DXVECTOR2(750, 250);
				g_RightSprite.DrawSprite(g_pTextureMouseRight);
			}
			else {
				g_MouseSprite.m_pos = D3DXVECTOR2(750 + i, 250 + i);
				g_MouseSprite.DrawSprite(g_pTextureMouse);
			}
			break;
		}
		// dainamaito
		case 6:
		{
			static int i = 100;
			i -= 2;
			if (i < -50) {
				i = 100;
			}
			g_MarkSprite.m_pos = D3DXVECTOR2(600, 500);
			g_MarkSprite.DrawSprite(g_pTextureMark);
			if (i < 0) {
				g_RightSprite.m_pos = D3DXVECTOR2(650, 550);
				g_RightSprite.DrawSprite(g_pTextureMouseRight);
			}
			else {
				g_MouseSprite.m_pos = D3DXVECTOR2(650 + i, 550 + i);
				g_MouseSprite.DrawSprite(g_pTextureMouse);
			}
			break;
		}
		// �ԉ�
		case 7:
		{
			static int i = 100;
			i -= 2;
			if (i < -50) {
				i = 100;
			}
			g_MarkSprite.m_pos = D3DXVECTOR2(600, 500);
			g_MarkSprite.DrawSprite(g_pTextureMark);
			if (i < 0) {
				g_RightSprite.m_pos = D3DXVECTOR2(650, 550);
				g_RightSprite.DrawSprite(g_pTextureMouseRight);
			}
			else {
				g_MouseSprite.m_pos = D3DXVECTOR2(650 + i, 550 + i);
				g_MouseSprite.DrawSprite(g_pTextureMouse);
			}
			break;
		}
		default:
			break;
		}
	}
}