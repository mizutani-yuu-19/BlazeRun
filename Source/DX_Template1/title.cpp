// タイトル画面処理
#include "title.h"
#include "scene.h"
#include "input.h"
#include "fade.h"
#include "light.h"
#include "sprite.h"
#include "tutorial.h"
//----- マクロ定義
// テクスチャ パス名
#define PATH_TEXTURE_TITLE	"data/texture/titlefire.png"
#define PATH_TEXTURE_TITLE_LOGO	"data/texture/title.png"
#define PATH_TEXTURE_CLICKTOSTART	"data/texture/clicktostart.png"
// 頂点数
#define NUM_VERTEX		4
#define LOGO_WIDTH		(1025)
#define LOGO_HEIGHT		(630)
#define CLICK_WIDTH		(533)
#define CLICK_HEIGHT		(81)
//----- 構造体宣言

//----- グローバル変数
// テクスチャ
static LPDIRECT3DTEXTURE9		g_pTextureTitle;
static LPDIRECT3DTEXTURE9		g_pTextureTitleLogo;
static LPDIRECT3DTEXTURE9		g_pTextureClick;
static CSprite					g_titleSprite;
static CSprite					g_titleLogoSprite;
static CSprite					g_clickSprite;
// 初期化処理
void InitTitle()
{
	g_titleSprite.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y + 5), SCREEN_WIDTH, SCREEN_HEIGHT, 5, 5);
	g_titleSprite.m_color = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_titleLogoSprite.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), LOGO_WIDTH, LOGO_HEIGHT, 1, 1);
	g_pTextureTitle = SetTexture(PATH_TEXTURE_TITLE);
	g_pTextureTitleLogo = SetTexture(PATH_TEXTURE_TITLE_LOGO);
	g_clickSprite.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, 600), CLICK_WIDTH, CLICK_HEIGHT, 1, 1);
	g_pTextureClick = SetTexture(PATH_TEXTURE_CLICKTOSTART);
	// フェードイン開始
	StartFadeIn();
	PlaySound(SOUND_LABEL_TITLE);
}

// 終了処理
void UninitTitle()
{
	StopSound(SOUND_LABEL_TITLE);
	if (g_pTextureTitle) {
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
}

// 更新処理
void UpdateTitle()
{
	static int time = 0;
	static int clicktime = 60;
	clicktime--;
	if (clicktime == 0) {
		clicktime = 60;
	}
	g_clickSprite.m_color = D3DCOLOR_RGBA(255, 255, 255, 255 - clicktime*2);
	time++;
	g_titleSprite.m_patNum = time / 3 % 25;
	if (EndFadeIn()) {
		if (DIGetMouseTrigger(0)) {
			StartFadeOut();
		}
	}
	if (EndFadeOut()) {
		if (GetTutorial())
			SetScene(SCENE_STAGESELECT);
		else
			SetScene(SCENE_TUTORIAL);
	}
}

// 描画処理
void DrawTitle()
{
	SetRenderMode(BLEND_TRANSLUCENT);
	g_titleSprite.DrawSprite(g_pTextureTitle);
	g_titleLogoSprite.DrawSprite(g_pTextureTitleLogo);
	g_clickSprite.DrawSprite(g_pTextureClick);
}
