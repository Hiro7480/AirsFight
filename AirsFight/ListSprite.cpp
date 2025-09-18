//==========================================================
// ListSprite.cpp
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#include "ListSprite.h"

//----------------------------------------------
//	Name:	CListSprite
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice = D3D�f�o�C�X
//			LPDIRECT3DTEXTURE8	pTexture  = �e�N�X�`��
//	Out:	�Ȃ�
//----------------------------------------------
CListSprite::CListSprite(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture)
		:C2DGraphicObj(d3dDevice) 
{
	/* ���̃f�[�^�ւ̃|�C���^������ */
	m_pNext = NULL;

	/* ���R���������܂� */
	m_bFlg = true;

	/* �e�N�X�`���̃Z�b�g */
	m_pTexture = pTexture;
}

//----------------------------------------------
//	Name:	~CListSprite
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CListSprite::~CListSprite()
{

}

//----------------------------------------------
//	Name:	IsDelete
//	Func:	��������
//	in:		�Ȃ�
//	Out:	bool
//----------------------------------------------
bool CListSprite::IsDelete()
{
	/* �����t���O�������Ă��Ȃ���΂n�j */
	if(m_bFlg == false)		return true;

	/* �����Ă�Ώ����Ȃ� */
	return false;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		LPD3DXSPRITE pSprite = �X�v���C�g
//	Out:	�Ȃ�
//----------------------------------------------
void CListSprite::Render(LPD3DXSPRITE pSprite)
{
	/* �X�v���C�g��`�� */
	pSprite->Draw(m_pTexture, &m_rectStock, NULL, NULL, 0.0f, &m_vecStock,
					D3DCOLOR_ARGB(255, 255, 255, 255));
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CListSprite::UpDate()
{
	C2DGraphicObj::UpDate();

	/* ��Ȃ񂩏������� */

}