//----------インクルード-----------
#include "burn.h"
#include "collision.h"
//--------定数マクロ---------
#define	MAX_BURN	(5000)
#define NEXT_BURN_TIME	(0.01f)

//--------グローバル変数---------
// 
static CBurn		g_burn[MAX_BURN];
// 存在
static bool			g_bExist[MAX_BURN];
// デバイス
//static LPDIRECT3DDEVICE9	g_pD3DDevice;

//---------プロトタイプ-----------

//---------クラス---------
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
	// 自分が燃えていなかったら
	if (!m_bBurn) {
		// 周囲のburnが燃えていたら自分を燃やす
		for (int i = 0; i < MAX_BURN; i++) {
			if (!g_bExist[i])	continue;	// 存在していない
			if (!g_burn[i].m_bBurn)	continue;	// 燃えていない
			if (g_burn[i].m_burnTime < NEXT_BURN_TIME*60.0f)	continue;

			// 自分と相手が触れていたら
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

//---------関数------------

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

// 燃える性質を作る
// 戻り値はセットした番号
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

// 燃えている位置を更新
// 毎フレーム呼び出してください
void SetBurnPos(int num, D3DXVECTOR2 pos) {
	g_burn[num].m_pos = pos;
}

// 自分が燃えているかをゲット
bool GetBurn(int num) {
	return g_burn[num].m_bBurn;
}