// スコア表示処理
#include "number.h"
#include "sprite.h"
#include "player.h"

//----- マクロ定義
// テクスチャ パス名
#define PATH_TEXTURE_BALZECNT	"data/texture/blazecnt.png"
#define PATH_TEXTURE_NUMBER	"data/texture/number.png"
// ポリゴン サイズ
#define NUMBER_WIDTH		50
#define NUMBER_HEIGHT		100
#define BLAZECNT_WIDTH		150
#define BLAZECNT_HEIGHT		100
// テクスチャ分割数
#define NUMBER_DIV_U		10	// 横分割数
#define NUMBER_DIV_V		1	// 縦分割数
// BLAZECNT描画位置
#define BLAZECNT_POS_X		(30)
#define BLAZECNT_POS_Y		(30)
//----- 構造体宣言

//----- グローバル変数
static CSprite					g_Number[2];
static CSprite					g_BlazeCnt;
static LPDIRECT3DTEXTURE9		g_pTextureNumber;
static LPDIRECT3DTEXTURE9		g_pTextureBlazeCnt;
// 初期化処理
void InitNumber()
{
	g_pTextureBlazeCnt = SetTexture(PATH_TEXTURE_BALZECNT);
	g_pTextureNumber = SetTexture(PATH_TEXTURE_NUMBER);
	for (int i = 0; i < 2; i++) {
		g_Number[i].InitSprite(D3DXVECTOR2(BLAZECNT_POS_X + BLAZECNT_WIDTH + (NUMBER_WIDTH*i) + NUMBER_WIDTH / 2, BLAZECNT_POS_Y + BLAZECNT_HEIGHT / 2), NUMBER_WIDTH, NUMBER_HEIGHT, 10, 1);
	}
	g_BlazeCnt.InitSprite(D3DXVECTOR2(BLAZECNT_POS_X + BLAZECNT_WIDTH / 2, BLAZECNT_POS_Y + BLAZECNT_HEIGHT / 2), BLAZECNT_WIDTH, BLAZECNT_HEIGHT, 1, 1);
}

// 終了処理
void UninitNumber()
{
	// テクスチャの解放
	g_pTextureNumber->Release();
	g_pTextureNumber = NULL;
	g_pTextureBlazeCnt->Release();
	g_pTextureBlazeCnt = NULL;
}

// 更新処理
void UpdateNumber()
{
	int num = GetBlazeNum();
	g_Number[0].m_patNum = num / 10;
	g_Number[1].m_patNum = num % 10;
}

// 描画処理
void DrawNumber(void){
	SetRenderMode(BLEND_TRANSLUCENT);
	g_BlazeCnt.DrawSprite(g_pTextureBlazeCnt);
	for (int i = 0; i < 2; i++) {
		g_Number[i].DrawSprite(g_pTextureNumber);
	}
}
