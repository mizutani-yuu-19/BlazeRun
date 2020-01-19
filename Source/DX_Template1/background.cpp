// �w�i����
#include "background.h"
#include "sprite.h"

//----- �}�N����`
// �e�N�X�`�� �p�X��
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

//----- �\���̐錾

//----- �O���[�o���ϐ�
// �e�N�X�`��
static LPDIRECT3DTEXTURE9		g_pTextureBG;
static LPDIRECT3DTEXTURE9		g_pTextureBGObject;
static LPDIRECT3DTEXTURE9		g_pTextureBGObject2;
// �X�v���C�g
static CSprite					g_BGSprite;
static CSprite					g_BGObjectSprite;
static CSprite					g_BGObjectSprite2;


// ����������
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

// �I������
void UninitBG()
{
	g_pTextureBG->Release();
	g_pTextureBG = NULL;
	g_pTextureBGObject->Release();
	g_pTextureBGObject = NULL;
}

// �X�V����
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

// �`�揈��
void DrawBG()
{
	SetRenderMode(BLEND_TRANSLUCENT);
	g_BGSprite.DrawSprite(g_pTextureBG);
	g_BGObjectSprite.DrawSprite(g_pTextureBGObject);
	g_BGObjectSprite2.DrawSprite(g_pTextureBGObject2);
}