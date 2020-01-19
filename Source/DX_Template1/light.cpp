/////////////////////////////////////////////
//
// light
//
/////////////////////////////////////////////

//---------�C���N���[�h��---------------
#include "light.h"
#include "player.h"
#include "sprite.h"

//---------�萔�}�N��-------------
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define PATH_TEXTURE_LIGHT	"data/texture/light.png"
#define MAX_LIGHT			(10000)

//---------�\����---------


//---------�O���[�o���ϐ�---------------

static VERTEX_2D	g_vertex2[] = {
	{ { 0.0f,   0.0f, 0.0f }, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 0.0f, 0.0f },
	{ { SCREEN_WIDTH,   0.0f, 0.0f }, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0.0f },
	{ { 0.0f, SCREEN_HEIGHT, 0.0f }, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 0.0f, 1.0f },
	{ { SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f }, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 1.0f },
};
//static LPDIRECT3DTEXTURE9	g_pLight;

static CSprite				g_light[MAX_LIGHT];
static CSprite				g_Firelight;
static bool					g_bExist[MAX_LIGHT];
static LPDIRECT3DDEVICE9	g_pD3DDevice;
static LPDIRECT3DTEXTURE9	g_pTextureLight;	// ��
static LPDIRECT3DTEXTURE9	g_pTextureFireLight;	// ��
static LPDIRECT3DTEXTURE9	g_pTexture;		// �쐬�e�N�X�`��
static LPDIRECT3DSURFACE9	g_pTexZBuffer;		// �쐬�e�N�X�`��Z�o�b�t�@
static LPDIRECT3DSURFACE9	g_pTexSurface;		// �쐬�e�N�X�`���T�[�t�F�C�X
static LPDIRECT3DSURFACE9	g_pBackBuffer;		// �o�b�N�o�b�t�@
static LPDIRECT3DSURFACE9	g_pBackZBuffer;	// �o�b�NZ�o�b�t�@

HRESULT InitLight(void) {
	HRESULT hr = true;
	g_pD3DDevice = GetDevice();
	// �e�N�X�`���쐬
	g_pD3DDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture, NULL);
	// �e�N�X�`���̐[�x
	g_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, true, &g_pTexZBuffer, NULL);
	// �e�N�X�`������T�[�t�F�C�X���쐬
	g_pTexture->GetSurfaceLevel(0, &g_pTexSurface);
	// �o�b�N�o�b�t�@�̃A�h���X�擾
	g_pD3DDevice->GetRenderTarget(0, &g_pBackBuffer);
	// �o�b�N�o�b�t�@�̐[�x�擾
	g_pD3DDevice->GetDepthStencilSurface(&g_pBackZBuffer);

	// �e�N�X�`���Z�b�g
	g_pTextureLight = SetTexture(PATH_TEXTURE_LIGHT);
	g_pTextureFireLight = SetTexture("data/texture/firelight.png");
	// �X�v���C�g����
	for (int i = 0; i < MAX_LIGHT; i++) {
		g_light[i].InitSprite(D3DXVECTOR2(0, 0), 200, 200, 1, 1);
	}
	g_Firelight.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT - 200 + 5), SCREEN_WIDTH, 400, 5, 5);
	return hr;
}

void UpdateLight() {

}

void DrawLight() {
	// �e�N�X�`���T�[�t�F�C�X�ɕ`��
	g_pD3DDevice->SetRenderTarget(0, g_pTexSurface);
	g_pD3DDevice->SetDepthStencilSurface(g_pTexZBuffer);

	// ���Z�����ɕύX
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �����_�����O��̃N���A
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	for (int i = 0; i < MAX_LIGHT - 1; i++)
	{
		if (!g_bExist[i])	continue;

		// �`��
		g_light[i].DrawSprite(g_pTextureLight);
		g_bExist[i] = false;
	}
	if (g_bExist[9999]) {
		g_Firelight.DrawSprite(g_pTextureFireLight);
		g_bExist[9999] = false;
	}
	// �쐬�����e�N�X�`���T�[�t�F�C�X���o�b�N�o�b�t�@�ɕ`��
	// ��Z�����ɕύX
	SetRenderMode(BLEND_MULTIPLICATION);
	// �`�����o�b�N�o�b�t�@�ɕύX
	g_pD3DDevice->SetRenderTarget(0, g_pBackBuffer);
	g_pD3DDevice->SetDepthStencilSurface(g_pBackZBuffer);

	// ���_�����ݒ�
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���ݒ�
	g_pD3DDevice->SetTexture(0, g_pTexture);

	// �|���S���`��(���_�z��g�p)
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_vertex2, sizeof(g_vertex2[0]));
}

void UninitLight() {
	// �e�N�X�`���̉��
	if (g_pTextureLight) {
		g_pTextureLight->Release();
		g_pTextureLight = NULL;
	}
	g_pTexture->Release();
	g_pTextureLight = NULL;
	g_pTexZBuffer->Release();
	g_pTexZBuffer = NULL;
	g_pTexSurface->Release();
	g_pTexSurface = NULL;
	g_pBackBuffer->Release();
	g_pBackBuffer = NULL;
	g_pBackZBuffer->Release();
	g_pBackZBuffer = NULL;
}

void SetLight(D3DXVECTOR2 pos, D3DXVECTOR2 scale) {
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (g_bExist[i])	continue;

		g_light[i].m_pos = pos;
		g_light[i].m_scale = scale;

		g_bExist[i] = true;
		return;
	}
}

void SetFireLight(int animnum) {
	g_Firelight.m_patNum = animnum;
	g_bExist[9999] = true;
}