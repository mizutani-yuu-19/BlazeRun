// フェード処理
#include "fade.h"
#include "light.h"
#include "common.h"

//----- マクロ定義
// 頂点フォーマット
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define FADE_TIME				(30)

//----- 構造体宣言

//----- グローバル変数
static int g_nFade=FADE_TIME;			// タイマ
static int g_nDir = -1;					// フェードイン:-1　フェードアウト:+1

// 初期化処理
HRESULT InitFade()
{
	return 1;
}

// 終了処理
void UninitFade()
{
	// なにもしない。
}

// 更新処理
void UpdateFade()
{
	g_nFade += g_nDir;
	if (g_nFade < 0)
		g_nFade = 0;
	else if (g_nFade > FADE_TIME)
		g_nFade = FADE_TIME;
}

// 描画処理
void DrawFade()
{
 	SetLight(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(FADE_TIME-g_nFade, FADE_TIME-g_nFade));
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// 頂点書式設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャ設定
	//pDevice->SetTexture(0, NULL);

	//// ポリゴン描画(頂点配列使用)
	//pDevice->DrawPrimitiveUP(
	//	D3DPT_TRIANGLESTRIP, 2,
	//	g_vertex, sizeof(g_vertex[0]));
}
// フェードイン開始
void StartFadeIn() {
	g_nFade = FADE_TIME;
	g_nDir = -1;
}
// フェードアウト開始
void StartFadeOut() {
	g_nFade = 0;
	g_nDir = 1;
	StopSound();
}
int EndFadeIn() {
	return (g_nDir < 0 && g_nFade <= 0);
}
int EndFadeOut() {
	return (g_nDir > 0 && g_nFade >= FADE_TIME);
}