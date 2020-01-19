// �t�F�[�h����
#include "fade.h"
#include "light.h"
#include "common.h"

//----- �}�N����`
// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define FADE_TIME				(30)

//----- �\���̐錾

//----- �O���[�o���ϐ�
static int g_nFade=FADE_TIME;			// �^�C�}
static int g_nDir = -1;					// �t�F�[�h�C��:-1�@�t�F�[�h�A�E�g:+1

// ����������
HRESULT InitFade()
{
	return 1;
}

// �I������
void UninitFade()
{
	// �Ȃɂ����Ȃ��B
}

// �X�V����
void UpdateFade()
{
	g_nFade += g_nDir;
	if (g_nFade < 0)
		g_nFade = 0;
	else if (g_nFade > FADE_TIME)
		g_nFade = FADE_TIME;
}

// �`�揈��
void DrawFade()
{
 	SetLight(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(FADE_TIME-g_nFade, FADE_TIME-g_nFade));
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// ���_�����ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���ݒ�
	//pDevice->SetTexture(0, NULL);

	//// �|���S���`��(���_�z��g�p)
	//pDevice->DrawPrimitiveUP(
	//	D3DPT_TRIANGLESTRIP, 2,
	//	g_vertex, sizeof(g_vertex[0]));
}
// �t�F�[�h�C���J�n
void StartFadeIn() {
	g_nFade = FADE_TIME;
	g_nDir = -1;
}
// �t�F�[�h�A�E�g�J�n
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