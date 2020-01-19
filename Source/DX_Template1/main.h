//=============================================================================
//
// メイン処理 [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1 // [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "imm32.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1200)				// ウインドウの幅
#define SCREEN_HEIGHT	(700)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
{if(x){x->Release();x=NULL;}}
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

//*****************************************************************************
// extern宣言
//*****************************************************************************
extern int	g_nScore;

#endif // _MAIN_H_
