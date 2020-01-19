//----------インクルード-------------
#include "blaze.h"
#include "burn.h"
#include "light.h"
#include "ground.h"
#include "lamp.h"
#include "input.h"
#include "wall.h"
#include "board.h"
//----------定数マクロ------------
#define BLAZE_WIDTH	(50)
#define BLAZE_HEIGHT (50)
#define BLAZE_TIME	(5)
#define BLAZE_SPEED	(25)

//----------グローバル変数-------------
static LPDIRECT3DTEXTURE9	g_pTextureBlaze;

// デバイス
static LPDIRECT3DDEVICE9		g_pD3DDevice;
//----------クラス-----------
void CBlaze::InitBlaze(D3DXVECTOR2 pos) {
	m_rad = atan2(pos.y-GetMousePos().y, GetMousePos().x-pos.x);
	m_BlazeSprite.InitSprite(pos, BLAZE_WIDTH, BLAZE_HEIGHT, 1, 1);
	m_BlazePhysics.InitPhysics(D3DXVECTOR2(0, 0), D3DXVECTOR2(cos(m_rad)*BLAZE_SPEED,sin(m_rad)*-BLAZE_SPEED ));
	m_BurnNum = CreateBurn(pos, BLAZE_WIDTH, BLAZE_HEIGHT, true);
	m_time = BLAZE_TIME * 60;
}

void CBlaze::UninitBlaze() {
	DeleteBurn(m_BurnNum);
}

void CBlaze::UpdateBlaze() {
	m_time--;
	m_BlazePhysics.Gravity();
	m_BlazePhysics.PosCalc(&m_BlazeSprite.m_pos);
	SetBurnPos(m_BurnNum, m_BlazeSprite.m_pos);
	//ぶつかったら消す
	if (999 != CollisionBoard(m_BlazeSprite.m_pos, BLAZE_WIDTH, BLAZE_HEIGHT)) {
		m_time = 0;
		UpdateBurn();
	}
	else if (CollisionGround(&m_BlazeSprite.m_pos, BLAZE_WIDTH, BLAZE_HEIGHT)) {
		m_time = 0;
		UpdateBurn();
	}
	else if (CollisionWall(&m_BlazeSprite.m_pos, BLAZE_WIDTH, BLAZE_HEIGHT)) {
		UpdateBurn();
		m_time = 0;
	}
	else if (CollisionLamp(m_BlazeSprite.m_pos, BLAZE_WIDTH) ){
		UpdateBurn();
		m_time = 0;
	}
	
	//画面外
	if (m_BlazeSprite.m_pos.x > SCREEN_WIDTH + BLAZE_WIDTH || m_BlazeSprite.m_pos.x < -BLAZE_WIDTH||m_BlazeSprite.m_pos.y>SCREEN_HEIGHT+BLAZE_HEIGHT) {
		m_time = 0;
	}
}

void CBlaze::DrawBlaze() {
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_BlazeSprite.DrawSprite(g_pTextureBlaze);
	if(!g_bDeleteLight)
	SetLight(m_BlazeSprite.m_pos,D3DXVECTOR2(1,1));
}

D3DXVECTOR2 CBlaze::GetBlazePos() {
	return m_BlazeSprite.m_pos;
}
//-----------関数------------
void InitBlaze() {
	g_pD3DDevice = GetDevice();
	g_pTextureBlaze = SetTexture("data/texture/blaze.png");
}

void UninitBlaze() {
	g_pTextureBlaze->Release();
	g_pTextureBlaze = NULL;
}
