//--------インクルード---------
#include "board.h"
#include "collision.h"
#include "input.h"
#include "dynamite.h"

//--------定数マクロ---------
#define MAX_BOARD		(20)
#define BOARD_HEIGHT	(50)
#define BOARD_COL_HEIGHT	(30)
#define BOARD_WIDTH_PAT1	(100)
#define BOARD_WIDTH_PAT2	(300)
#define BOARD_WIDTH_PAT1_ANIM	(171)
#define BOARD_HEIGHT_PAT1_ANIM	(135)
#define BOARD_WIDTH_PAT2_ANIM	(513)
#define BOARD_HEIGHT_PAT2_ANIM	(405)

//--------グローバル変数---------
// 足場
static CBoard		g_board[MAX_BOARD];
// テクスチャ
static LPDIRECT3DTEXTURE9	g_pTextureBoard1;
static LPDIRECT3DTEXTURE9	g_pTextureBoard2;
static LPDIRECT3DTEXTURE9	g_pTextureBoard1_anim;
static LPDIRECT3DTEXTURE9	g_pTextureBoard2_anim;
// 存在
static bool			g_bExist[MAX_BOARD];

//---------プロトタイプ-----------

//---------クラス---------
void CBoard::InitBoard(D3DXVECTOR2 pos, int num, int pat) {
	int animWidth;
	int animHeight;
	if (pat == 1) {
		m_width = BOARD_WIDTH_PAT1;
		animWidth = BOARD_WIDTH_PAT1_ANIM;
		animHeight = BOARD_HEIGHT_PAT1_ANIM;
	}
	else if (pat == 2) {
		m_width = BOARD_WIDTH_PAT2;
		animWidth = BOARD_WIDTH_PAT2_ANIM;
		animHeight = BOARD_HEIGHT_PAT2_ANIM;
	}
	m_num = num;
	pos.y += BOARD_HEIGHT / 2;
	pos.x += m_width / 2.0f;
	m_BoardSprite.InitSprite(pos, m_width, BOARD_HEIGHT, 1, 1);
	m_BoardSpriteAnim.InitSprite(pos, animWidth, animHeight, 2, 1);
	m_pat = pat;
	m_animTime = 0;
}
void CBoard::UninitBoard() {
	g_bExist[m_num] = false;
	m_bExplosion = false;
}
void CBoard::UpdateBoard() {
	m_BoardSprite.m_pos.x -= g_scrollSpeed;
	m_BoardSpriteAnim.m_pos.x -= g_scrollSpeed;
	// 消す
	// ダイナマイト
	int dynamiteNum = 0;
	D3DXVECTOR2 workDynamite = GetDynamiteExplosionPos(dynamiteNum);
	while (workDynamite != D3DXVECTOR2(0, 0)) {
		dynamiteNum++;
		if (CollisionRect(m_BoardSprite.m_pos.x - m_width / 2.0f, m_BoardSprite.m_pos.y - BOARD_HEIGHT / 2.0f, m_width, BOARD_HEIGHT, workDynamite.x - DYNAMITE_EXPLOSION_SIZE / 2.0f, workDynamite.y - DYNAMITE_EXPLOSION_SIZE / 2.0f, DYNAMITE_EXPLOSION_SIZE, DYNAMITE_EXPLOSION_SIZE) && !m_bExplosion) {
			m_bExplosion = true;
		}

		if (m_bExplosion) {
			m_animTime++;
			m_BoardSpriteAnim.m_patNum = m_animTime / 8 % 2;
				if (m_animTime >= 16) {
					UninitBoard();
				}
		}
		// 位置再取得
		workDynamite = GetDynamiteExplosionPos(dynamiteNum);
	}

	// 画面外
	if (m_BoardSprite.m_pos.x < m_width / 2 * -1) {
		UninitBoard();
	}
}
void CBoard::DrawBoard() {
	if (m_pat == 1) {
		if (!m_bExplosion)
			m_BoardSprite.DrawSprite(g_pTextureBoard1);
		else
			m_BoardSpriteAnim.DrawSprite(g_pTextureBoard1_anim);
	}
	else if (m_pat == 2) {
		if (!m_bExplosion)
			m_BoardSprite.DrawSprite(g_pTextureBoard2);
		else
			m_BoardSpriteAnim.DrawSprite(g_pTextureBoard2_anim);
	}
}

float CBoard::CollisionBoard(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight) {
	if (CollisionRect(PlayerPos.x - PlayerWidth / 2.0f, PlayerPos.y - PlayerHeight / 2.0f, PlayerWidth, PlayerHeight, m_BoardSprite.m_pos.x - m_width / 2.0f, m_BoardSprite.m_pos.y - BOARD_HEIGHT / 2.0f, m_width, BOARD_COL_HEIGHT)) {
		return m_BoardSprite.m_pos.y - BOARD_HEIGHT / 2.0f;
	}
	return 999;
}

D3DXVECTOR2 CBoard::GetPos() {
	return m_BoardSprite.m_pos;
}
//---------関数----------
void InitBoard() {
	g_pTextureBoard1 = SetTexture("data/texture/board1.png");
	g_pTextureBoard1_anim = SetTexture("data/texture/board1_anim.png");
	g_pTextureBoard2 = SetTexture("data/texture/board1.png");
	g_pTextureBoard2_anim = SetTexture("data/texture/board2_anim.png");
}

void UninitBoard() {
	for (int i = 0; i < MAX_BOARD; i++)
		g_bExist[i] = false;
	g_pTextureBoard1->Release();
	g_pTextureBoard1 = NULL;
	g_pTextureBoard2->Release();
	g_pTextureBoard2 = NULL;
}


void CreateBoard(D3DXVECTOR2 pos, int pat) {
	for (int i = 0; i < MAX_BOARD; i++) {
		if (g_bExist[i])		continue;

		g_board[i].InitBoard(pos, i, pat);
		g_bExist[i] = true;
		return;
	}
}

void UpdateBoard() {
	for (int i = 0; i < MAX_BOARD; i++) {
		if (!g_bExist[i])		continue;

		g_board[i].UpdateBoard();
	}
}
void DrawBoard() {
	SetRenderMode(BLEND_TRANSLUCENT);
	for (int i = 0; i < MAX_BOARD; i++) {
		if (!g_bExist[i])		continue;

		g_board[i].DrawBoard();
	}
}
// 当たった地面の位置Ｙを返す
// 当たっていなければ999
float CollisionBoard(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight) {
	for (int i = 0; i < MAX_BOARD; i++) {
		if (!g_bExist[i])		continue;

		float worky = g_board[i].CollisionBoard(PlayerPos, PlayerWidth, PlayerHeight);
		if (worky != 999) {
			return worky;
		}
	}
	return 999;
}
