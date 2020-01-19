//------------インクルード------------
#include "ground.h"
#include "collision.h"
#include "dynamite.h"

//------------定数マクロ------------
#define MAX_GROUND	(50)
#define GROUND_WIDTH	(100)
#define GROUND_HEIGHT	(100)

#define GROUND_PAT1	(0)
#define GROUND_PAT2	(1)
#define GROUND_PAT3	(2)

//------------グローバル変数-------------
static CGround g_wall[MAX_GROUND];
static bool  g_bExist[MAX_GROUND];
static LPDIRECT3DTEXTURE9	g_pTextureGround1;
static LPDIRECT3DTEXTURE9	g_pTextureGround2;
static LPDIRECT3DTEXTURE9	g_pTextureGround3;

//------------メソッド-----------
void CGround::InitGround(D3DXVECTOR2 pos, int pat, int num) {
	// 補正
	pos.y += GROUND_HEIGHT / 2.0f;
	pos.x += GROUND_WIDTH / 2.0f;
	m_num = num;
	m_pat = pat;
	m_GroundSprite.InitSprite(pos, GROUND_WIDTH, GROUND_HEIGHT, 1, 1);
}

void CGround::UninitGround() {
	g_bExist[m_num] = false;
}

void CGround::UpdateGround() {
	m_GroundSprite.m_pos.x -= g_scrollSpeed;
	// 画面外
	if (m_GroundSprite.m_pos.x < VANISHING_POINT) {
		UninitGround();
	}
}

void CGround::DrawGround() {
	SetRenderMode(BLEND_TRANSLUCENT);
	switch (m_pat)
	{
	case GROUND_PAT1:
		m_GroundSprite.DrawSprite(g_pTextureGround1);
		break;
	case GROUND_PAT2:
		m_GroundSprite.DrawSprite(g_pTextureGround2);
		break;
	case GROUND_PAT3:
		m_GroundSprite.DrawSprite(g_pTextureGround3);
		break;
	default:
		break;
	}
}

int CGround::CollisionGround(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight) {
	D3DXVECTOR2 PlayerRight = *PlayerPos;
	PlayerRight.x += PlayerWidth / 2.0f;
	D3DXVECTOR2 PlayerBottom = *PlayerPos;
	PlayerBottom.y += PlayerHeight / 2.0f;
	// 上に当たったら
	if (CollisionRect(PlayerBottom.x - PlayerWidth / 2.0f, PlayerBottom.y - 1.0f, PlayerWidth - 15.0f, 1.0f, m_GroundSprite.m_pos.x - GROUND_WIDTH / 2.0f, m_GroundSprite.m_pos.y - GROUND_HEIGHT / 2.0f, GROUND_WIDTH, GROUND_HEIGHT)) {
		PlayerPos->y = m_GroundSprite.m_pos.y - GROUND_HEIGHT / 2.0f - PlayerHeight / 2.0f;
		return 1;
	}
	// 一番左のブロックなら
	if (m_pat == GROUND_PAT1) {
		// 横に当たったら
		if (CollisionRect(PlayerRight.x - SCROLL_SPEED, PlayerRight.y - PlayerHeight / 2.0f, 5.0f, PlayerHeight - 6.0f, m_GroundSprite.m_pos.x - GROUND_WIDTH / 2.0f, m_GroundSprite.m_pos.y - GROUND_HEIGHT / 2.0f, GROUND_WIDTH, GROUND_HEIGHT)) {
			PlayerPos->x = m_GroundSprite.m_pos.x - GROUND_WIDTH / 2.0f - PlayerWidth / 2.0f;
			return 2;
		}
	}

	return 0;
}

//----------------関数-------------
void InitGround() {
	switch (GetScene())
	{
	case SCENE_TUTORIAL:
		g_pTextureGround1 = SetTexture("data/texture/ground1_1.png");
		g_pTextureGround2 = SetTexture("data/texture/ground1_2.png");
		g_pTextureGround3 = SetTexture("data/texture/ground1_3.png");
		break;
	case SCENE_STAGE1:
		g_pTextureGround1 = SetTexture("data/texture/ground1_1.png");
		g_pTextureGround2 = SetTexture("data/texture/ground1_2.png");
		g_pTextureGround3 = SetTexture("data/texture/ground1_3.png");
		break;
	case SCENE_STAGE2:
		g_pTextureGround1 = SetTexture("data/texture/ground2_1.png");
		g_pTextureGround2 = SetTexture("data/texture/ground2_2.png");
		g_pTextureGround3 = SetTexture("data/texture/ground2_3.png");
		break;
	case SCENE_STAGE3:
		g_pTextureGround1 = SetTexture("data/texture/ground3_1.png");
		g_pTextureGround2 = SetTexture("data/texture/ground3_2.png");
		g_pTextureGround3 = SetTexture("data/texture/ground3_3.png");
		break;
	default:
		break;
	}
}

void UninitGround() {
	for (int i = 0; i < MAX_GROUND; i++)
		g_bExist[i] = false;
	g_pTextureGround1->Release();
	g_pTextureGround1 = NULL;
	g_pTextureGround2->Release();
	g_pTextureGround2 = NULL;
	g_pTextureGround3->Release();
	g_pTextureGround3 = NULL;
}

void UpdateGround() {
	for (int i = 0; i < MAX_GROUND; i++) {
		// 使用していたら更新
		if (!g_bExist[i])	continue;
		g_wall[i].UpdateGround();
	}
}

void DrawGround() {
	for (int i = 0; i < MAX_GROUND; i++) {
		if (!g_bExist[i])	continue;
		g_wall[i].DrawGround();
	}
}

void CreateGround(D3DXVECTOR2 pos, float width) {
	int groundNum = width / GROUND_WIDTH;
	for (int j = 0; j < groundNum; j++) {
		int pat = GROUND_PAT2;
		if (j == 0) {
			pat = GROUND_PAT1;
		}
		else if (j == groundNum - 1) {
			pat = GROUND_PAT3;
		}
		for (int i = 0; i < MAX_GROUND; i++) {
			if (g_bExist[i])		continue;

			g_wall[i].InitGround(pos, pat, i);
			g_bExist[i] = true;
			pos.x += GROUND_WIDTH;
			break;
		}
	}
}


int CollisionGround(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight) {
	int work = 0;
	for (int i = 0; i < MAX_GROUND; i++) {
		if (!g_bExist[i])		continue;

		work = g_wall[i].CollisionGround(PlayerPos, PlayerWidth, PlayerHeight);
		if (work)
			return work;
	}
	return work;
}
