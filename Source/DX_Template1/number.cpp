// �X�R�A�\������
#include "number.h"
#include "sprite.h"
#include "player.h"

//----- �}�N����`
// �e�N�X�`�� �p�X��
#define PATH_TEXTURE_BALZECNT	"data/texture/blazecnt.png"
#define PATH_TEXTURE_NUMBER	"data/texture/number.png"
// �|���S�� �T�C�Y
#define NUMBER_WIDTH		50
#define NUMBER_HEIGHT		100
#define BLAZECNT_WIDTH		150
#define BLAZECNT_HEIGHT		100
// �e�N�X�`��������
#define NUMBER_DIV_U		10	// ��������
#define NUMBER_DIV_V		1	// �c������
// BLAZECNT�`��ʒu
#define BLAZECNT_POS_X		(30)
#define BLAZECNT_POS_Y		(30)
//----- �\���̐錾

//----- �O���[�o���ϐ�
static CSprite					g_Number[2];
static CSprite					g_BlazeCnt;
static LPDIRECT3DTEXTURE9		g_pTextureNumber;
static LPDIRECT3DTEXTURE9		g_pTextureBlazeCnt;
// ����������
void InitNumber()
{
	g_pTextureBlazeCnt = SetTexture(PATH_TEXTURE_BALZECNT);
	g_pTextureNumber = SetTexture(PATH_TEXTURE_NUMBER);
	for (int i = 0; i < 2; i++) {
		g_Number[i].InitSprite(D3DXVECTOR2(BLAZECNT_POS_X + BLAZECNT_WIDTH + (NUMBER_WIDTH*i) + NUMBER_WIDTH / 2, BLAZECNT_POS_Y + BLAZECNT_HEIGHT / 2), NUMBER_WIDTH, NUMBER_HEIGHT, 10, 1);
	}
	g_BlazeCnt.InitSprite(D3DXVECTOR2(BLAZECNT_POS_X + BLAZECNT_WIDTH / 2, BLAZECNT_POS_Y + BLAZECNT_HEIGHT / 2), BLAZECNT_WIDTH, BLAZECNT_HEIGHT, 1, 1);
}

// �I������
void UninitNumber()
{
	// �e�N�X�`���̉��
	g_pTextureNumber->Release();
	g_pTextureNumber = NULL;
	g_pTextureBlazeCnt->Release();
	g_pTextureBlazeCnt = NULL;
}

// �X�V����
void UpdateNumber()
{
	int num = GetBlazeNum();
	g_Number[0].m_patNum = num / 10;
	g_Number[1].m_patNum = num % 10;
}

// �`�揈��
void DrawNumber(void){
	SetRenderMode(BLEND_TRANSLUCENT);
	g_BlazeCnt.DrawSprite(g_pTextureBlazeCnt);
	for (int i = 0; i < 2; i++) {
		g_Number[i].DrawSprite(g_pTextureNumber);
	}
}
