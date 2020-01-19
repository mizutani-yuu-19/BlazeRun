//----------インクルード---------
#include "sprite.h"
#include <math.h>
//----------定数マクロ----------
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//----------グローバル宣言------------
static LPDIRECT3DDEVICE9	g_pD3DDevice;

//----------メソッド--------------
void CSprite::InitSprite(D3DXVECTOR2 pos, float width, float height, int divideX, int divideY) {
	m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_scale.x = 1.0f;			// 拡大率
	m_scale.y = 1.0f;			// 拡大率
	m_angleDegree = 0.0f;	// 回転角度（°）
	m_pos = pos;
	m_width = width;
	m_height = height;
	m_divideX = divideX;
	m_divideY = divideY;

	for (int i = 0; i < 4; ++i) {
		m_vertex[i].rhw = 1.0f;
		m_vertex[i].diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
		m_vertex[i].u = i % 2 * (1.0f / m_divideX);
		m_vertex[i].v = i / 2 * (1.0f / m_divideY);
	}
}

void CSprite::SetDivide(int X, int Y) {
	m_divideX = X;		// 分割数X
	m_divideY = Y;		// 分割数Y
}

void CSprite::DrawSprite(LPDIRECT3DTEXTURE9 pTexture) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float rad = D3DXToRadian(m_angleDegree);  //D3DXToRadian角度をradianに変換

	float s = sinf(rad);
	float c = cosf(rad);

	for (int i = 0; i < 4; ++i) {
		// アニメーション
		int u = m_patNum % m_divideX;
		int v = m_patNum / m_divideX;
		m_vertex[i].u = (u + i % 2) * (1.0f / m_divideX);
		m_vertex[i].v = (v + i / 2) * (1.0f / m_divideY);
		// 位置
		float x = ((i & 1)  * m_width - m_width / 2) * m_scale.x;
		float y = ((i >> 1) * m_height - m_height / 2) * m_scale.y;
		m_vertex[i].pos.x = m_pos.x + x * c - y * s;
		m_vertex[i].pos.y = m_pos.y + x * s + y * c;
		// カラー
		m_vertex[i].diffuse = m_color;
	}
	// 頂点書式設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ設定
	pDevice->SetTexture(0, pTexture);

	// ポリゴン描画(頂点配列使用)
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertex, sizeof(VERTEX_2D));
}

void CSprite::SetSize(float width, float height) {
	m_width = width;
	m_height = height;
}

void CSprite::SetPos(D3DXVECTOR2 pos) {
	m_pos = pos;
}

VERTEX_2D *CSprite::GetVertex() {
	return &m_vertex[0];
}

void CSprite::SetColor(D3DCOLOR color) {
	m_color = color;
}

//-------関数----------
void InitSprite() {
	g_pD3DDevice = GetDevice();
}

LPDIRECT3DTEXTURE9 SetTexture(LPCSTR pass) {
	LPDIRECT3DTEXTURE9 texture;
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(g_pD3DDevice, pass, &texture);
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャ読み込み失敗", pass, MB_OK);
		texture = NULL;
	}
	return texture;
}

// レンダーモード
void SetRenderMode(int mode) {
	switch (mode)
	{
	case		BLEND_NOBLEND:				// 通常（ブレンド無し）
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		break;
	case		BLEND_TRANSLUCENT:			// 半透明
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case		BLEND_ADDITION:				// 加算合成
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case		BLEND_ADDITION_TRANSLUCENT:	// 加算半透明合成
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case		BLEND_SUBTRACTION:			// 減算合成
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		break;
	case		BLEND_MULTIPLICATION:		// 乗算合成
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	case		BLEND_SCREEN:				// スクリーン合成
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case		BLEND_REVERSE:				// リバース
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		break;
	default:
		break;
	}
}