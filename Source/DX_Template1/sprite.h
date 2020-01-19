#ifndef _SPRITE_H_
#define	_SPRITE_H_

#include "main.h"
#include "RGBConvert.h"

//-----------�萔�}�N��-------------
enum {
	BLEND_NOBLEND,					// �ʏ�i�u�����h�����j
	BLEND_TRANSLUCENT,				// ������
	BLEND_ADDITION,					// ���Z����
	BLEND_ADDITION_TRANSLUCENT,		// ���Z����������
	BLEND_SUBTRACTION,				// ���Z����
	BLEND_MULTIPLICATION,			// ��Z����
	BLEND_SCREEN,					// �X�N���[������
	BLEND_REVERSE,					// ���o�[�X
};

//-----------�N���X-------------
typedef struct _VERTEX_2D {
	D3DVECTOR	pos;		// ���_���W
	float		rhw;		// �ϊ��ϒ��_(���1.0f)
	D3DCOLOR	diffuse;	// ���_�J���[(�g�U���ˌ�)
	float		u, v;		// �e�N�X�`�����W
} VERTEX_2D;

class CSprite {
public:
	void InitSprite(D3DXVECTOR2 pos, float width, float height, int divideX, int divideY);
	void DrawSprite(LPDIRECT3DTEXTURE9 pTexture);

	void SetDivide(int X, int Y);
	void SetSize(float width, float height);
	void SetPos(D3DXVECTOR2 pos);
	void SetColor(D3DCOLOR color);

	VERTEX_2D *GetVertex();

	D3DXVECTOR2 m_pos;			// ���S�ʒu
	D3DXVECTOR2	m_scale;		// �g�嗦
	float		m_angleDegree;	// ��]�p�x�i���j
	D3DCOLOR	m_color;		// �F
	int			m_patNum;		// �p�^�[��No
private:
	VERTEX_2D	m_vertex[4];	// ���_���
	float		m_width;		// �X�v���C�g�̕��i�e�N�X�`���̐؂��蕝�j
	float		m_height;		// �X�v���C�g�̍����i�e�N�X�`���̐؂��荂���j
	int			m_divideX;		// ������X
	int			m_divideY;		// ������Y

protected:

};

//-------�v���g�^�C�v---------
void InitSprite();
LPDIRECT3DTEXTURE9 SetTexture(LPCSTR pass);
void SetRenderMode(int mode);
#endif // !_SPRITE_H_