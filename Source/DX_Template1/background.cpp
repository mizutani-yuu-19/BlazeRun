// 背景処理
#include "background.h"
#include "sprite.h"

//----- マクロ定義
// テクスチャ パス名
#define PATH_TEXTURE_BG1	"data/texture/stage1BG.jpg"
#define PATH_TEXTURE_BG_OBJECT1_1	"data/texture/stage1BGobject.png"
#define PATH_TEXTURE_BG_OBJECT1_2	"data/texture/stage1BGobject2.png"
#define PATH_TEXTURE_BG2	"data/texture/stage2BG.jpg"
#define PATH_TEXTURE_BG_OBJECT2_1	"data/texture/stage2BGobject.png"
#define PATH_TEXTURE_BG_OBJECT2_2	"data/texture/stage2BGobject2.png"
#define PATH_TEXTURE_BG3	"data/texture/stage3BG2.jpg"
#define PATH_TEXTURE_BG_OBJECT3_1	"data/texture/stage3BGobject.png"
#define PATH_TEXTURE_BG_OBJECT3_2	"data/texture/stage3BGobject2.png"

#define BGOBJECT_WIDTH (700)
#define BGOBJECT_HEIGHT (700)

//----- 構造体宣言

//----- グローバル変数
// テクスチャ
static LPDIRECT3DTEXTURE9		g_pTextureBG;
static LPDIRECT3DTEXTURE9		g_pTextureBGObject;
static LPDIRECT3DTEXTURE9		g_pTextureBGObject2;
// スプライト
static CSprite					g_BGSprite;
static CSprite					g_BGObjectSprite;
static CSprite					g_BGObjectSprite2;


// 初期化処理
void InitBG()
{
	switch (GetScene())
	{
	case SCENE_STAGE1:
		g_pTextureBG = SetTexture(PATH_TEXTURE_BG1);
		g_pTextureBGObject = SetTexture(PATH_TEXTURE_BG_OBJECT1_1);
		g_pTextureBGObject2 = SetTexture(PATH_TEXTURE_BG_OBJECT1_2);
		break;
	case SCENE_TUTORIAL:
		g_pTextureBG = SetTexture(PATH_TEXTURE_BG1);
		g_pTextureBGObject = SetTexture(PATH_TEXTURE_BG_OBJECT1_1);
		g_pTextureBGObject2 = SetTexture(PATH_TEXTURE_BG_OBJECT1_2);
		break;
	case SCENE_STAGE2:
		g_pTextureBG = SetTexture(PATH_TEXTURE_BG2);
		g_pTextureBGObject = SetTexture(PATH_TEXTURE_BG_OBJECT2_1);
		g_pTextureBGObject2 = SetTexture(PATH_TEXTURE_BG_OBJECT2_2);
		break;
	case SCENE_STAGE3:
		g_pTextureBG = SetTexture(PATH_TEXTURE_BG3);
		g_pTextureBGObject = SetTexture(PATH_TEXTURE_BG_OBJECT3_1);
		g_pTextureBGObject2 = SetTexture(PATH_TEXTURE_BG_OBJECT3_2);
		break;
	default:
		break;
	}
	g_BGSprite.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
	g_BGObjectSprite.InitSprite(D3DXVECTOR2(SCREEN_WIDTH - BGOBJECT_WIDTH / 2, SCREEN_HEIGHT - BGOBJECT_HEIGHT / 2), BGOBJECT_WIDTH, BGOBJECT_HEIGHT, 1, 1);
	g_BGObjectSprite2.InitSprite(D3DXVECTOR2(SCREEN_WIDTH + BGOBJECT_WIDTH, SCREEN_HEIGHT - BGOBJECT_HEIGHT / 2), BGOBJECT_WIDTH, BGOBJECT_HEIGHT, 1, 1);
}

// 終了処理
void UninitBG()
{
	g_pTextureBG->Release();
	g_pTextureBG = NULL;
	g_pTextureBGObject->Release();
	g_pTextureBGObject = NULL;
}

// 更新処理
void UpdateBG()
{
	if (g_scrollSpeed) {
		g_BGObjectSprite.m_pos.x -= g_scrollSpeed - 2;
		g_BGObjectSprite2.m_pos.x -= g_scrollSpeed - 2;
	}
	if (g_BGObjectSprite.m_pos.x <= BGOBJECT_WIDTH*-1) {
		g_BGObjectSprite.m_pos.x = SCREEN_WIDTH + BGOBJECT_WIDTH;
	}
	if (g_BGObjectSprite2.m_pos.x <= BGOBJECT_WIDTH*-1) {
		g_BGObjectSprite2.m_pos.x = SCREEN_WIDTH + BGOBJECT_WIDTH;
	}
}

// 描画処理
void DrawBG()
{
	SetRenderMode(BLEND_TRANSLUCENT);
	g_BGSprite.DrawSprite(g_pTextureBG);
	g_BGObjectSprite.DrawSprite(g_pTextureBGObject);
	g_BGObjectSprite2.DrawSprite(g_pTextureBGObject2);
}