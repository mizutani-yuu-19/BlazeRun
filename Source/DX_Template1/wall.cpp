//------------インクルード------------
#include "wall.h"
#include "collision.h"
#include "dynamite.h"

//------------定数マクロ------------
#define MAX_WALL	(20)
#define WALL_WIDTH	(100)
#define WALL_HEIGHT	(350)
#define WALL_ANIM_WIDTH	(300)

//------------グローバル変数-------------
static CWall g_wall[MAX_WALL];
static bool  g_bExist[MAX_WALL];
static LPDIRECT3DTEXTURE9	g_pTextureWall;
static LPDIRECT3DTEXTURE9	g_pTextureWallAnim;

//------------メソッド-----------
void CWall::InitWall(D3DXVECTOR2 pos, int num) {
	// 補正
	pos.y += WALL_HEIGHT / 2.0f + 1.0f;
	pos.x += WALL_WIDTH / 2.0f;
	m_num = num;
	m_WallSprite.InitSprite(pos, WALL_WIDTH, WALL_HEIGHT, 1, 1);
	m_WallAnimSprite.InitSprite(pos, WALL_ANIM_WIDTH, WALL_HEIGHT, 3, 1);
	m_animCnt = 0;
	m_bDest = false;
}

void CWall::UninitWall() {
	g_bExist[m_num] = false;
}

void CWall::UpdateWall() {
	m_WallSprite.m_pos.x -= g_scrollSpeed;
	m_WallAnimSprite.m_pos.x -= g_scrollSpeed;
	// 消す
	// ダイナマイト
	int dynamiteNum = 0;
	D3DXVECTOR2 workDynamite = GetDynamiteExplosionPos(dynamiteNum);
	while (workDynamite != D3DXVECTOR2(0, 0)) {
		dynamiteNum++;
		if (CollisionRect(m_WallSprite.m_pos.x - WALL_WIDTH / 2.0f, m_WallSprite.m_pos.y - WALL_HEIGHT / 2.0f, WALL_WIDTH, WALL_HEIGHT, workDynamite.x - DYNAMITE_EXPLOSION_SIZE / 2.0f, workDynamite.y - DYNAMITE_EXPLOSION_SIZE / 2.0f, DYNAMITE_EXPLOSION_SIZE, DYNAMITE_EXPLOSION_SIZE)) {
			m_bDest = true;
		}
		// 位置再取得
		workDynamite = GetDynamiteExplosionPos(dynamiteNum);
	}
	if (m_bDest) {
		m_animCnt++;
		m_WallAnimSprite.m_patNum = m_animCnt / 8 % 3;
		if (m_animCnt >= 8 * 3) {
			UninitWall();
		}
	}
	// 画面外
	if (m_WallSprite.m_pos.x < VANISHING_POINT) {
		UninitWall();
	}
}

void CWall::DrawWall() {
	SetRenderMode(BLEND_TRANSLUCENT);
	if (m_bDest) {
		m_WallAnimSprite.DrawSprite(g_pTextureWallAnim);
	}
	else {
		m_WallSprite.DrawSprite(g_pTextureWall);
	}
}

int CWall::CollisionWall(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight) {
	if (m_bDest)	return 0;
	D3DXVECTOR2 PlayerRight = *PlayerPos;
	PlayerRight.x += PlayerWidth / 2.0f;
	D3DXVECTOR2 PlayerBottom = *PlayerPos;
	PlayerBottom.y += PlayerHeight / 2.0f;
	// 上に当たったら
	if (CollisionRect(PlayerBottom.x - PlayerWidth / 2.0f, PlayerBottom.y - 5.0f, PlayerWidth, 5.0f, m_WallSprite.m_pos.x - WALL_WIDTH / 2.0f, m_WallSprite.m_pos.y - WALL_HEIGHT / 2.0f, WALL_WIDTH, 5.0f) ||
		CollisionRect(PlayerBottom.x - PlayerWidth / 2.0f, PlayerBottom.y - 5.0f, PlayerWidth, 5.0f, m_WallSprite.m_pos.x - WALL_WIDTH / 2.0f + 20.0f, m_WallSprite.m_pos.y - WALL_HEIGHT / 2.0f, WALL_WIDTH, WALL_HEIGHT)) {
		PlayerPos->y = m_WallSprite.m_pos.y - WALL_HEIGHT / 2.0f - PlayerHeight / 2.0f;
		return 1;
	}
	// 横に当たったら
	if (CollisionRect(PlayerRight.x - SCROLL_SPEED, PlayerRight.y - PlayerHeight / 2.0f, SCROLL_SPEED, PlayerHeight - 6.0f, m_WallSprite.m_pos.x - WALL_WIDTH / 2.0f, m_WallSprite.m_pos.y - WALL_HEIGHT / 2.0f - 5.0f, WALL_WIDTH, WALL_HEIGHT - 5.0f)) {
		PlayerPos->x = m_WallSprite.m_pos.x - WALL_WIDTH / 2.0f - PlayerWidth / 2.0f;
		return 2;
	}

	return 0;
}

//----------------関数-------------
void InitWall() {
	switch (GetScene())
	{
	case SCENE_TUTORIAL:
		g_pTextureWall = SetTexture("data/texture/wall1.png");
		g_pTextureWallAnim = SetTexture("data/texture/wallanim1.png");
		break;
	case SCENE_STAGE1:
		g_pTextureWall = SetTexture("data/texture/wall1.png");
		g_pTextureWallAnim = SetTexture("data/texture/wallanim1.png");
		break;
	case SCENE_STAGE2:
		g_pTextureWall = SetTexture("data/texture/wall2.png");
		g_pTextureWallAnim = SetTexture("data/texture/wallanim2.png");
		break;
	case SCENE_STAGE3:
		g_pTextureWall = SetTexture("data/texture/wall3.png");
		g_pTextureWallAnim = SetTexture("data/texture/wallanim3.png");
		break;
	default:
		break;
	}
}

void UninitWall() {
	for (int i = 0; i < MAX_WALL; i++)
		g_bExist[i] = false;
	g_pTextureWall->Release();
	g_pTextureWall = NULL;
	g_pTextureWallAnim->Release();
	g_pTextureWallAnim = NULL;
}

void UpdateWall() {
	for (int i = 0; i < MAX_WALL; i++) {
		// 使用していたら更新
		if (!g_bExist[i])	continue;
		g_wall[i].UpdateWall();
	}
}

void DrawWall() {
	for (int i = 0; i < MAX_WALL; i++) {
		if (!g_bExist[i])	continue;
		g_wall[i].DrawWall();
	}
}

void CreateWall(D3DXVECTOR2 pos) {
	for (int i = 0; i < MAX_WALL; i++) {
		if (g_bExist[i])		continue;

		g_wall[i].InitWall(pos, i);
		g_bExist[i] = true;
		return;
	}
}


int CollisionWall(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight) {
	int work = 0;
	for (int i = 0; i < MAX_WALL; i++) {
		if (!g_bExist[i])		continue;

		work = g_wall[i].CollisionWall(PlayerPos, PlayerWidth, PlayerHeight);
		if (work)
			return work;
	}
	return work;
}
