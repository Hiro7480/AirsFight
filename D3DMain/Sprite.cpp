//==========================================================
// Sprite.cpp
// Auther : ���� ���V
// Data   : 2002/05/01
//==========================================================

#include "Sprite.h"

//------------------------------------------------------
//	Name:	CSprite
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice   = D3D�f�o�C�X
//			TCHAR*			  strFileName = �e�N�X�`���t�@�C����
//	Out:	�Ȃ�
//------------------------------------------------------
CSprite::CSprite(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName)
		:C2DGraphicObj(d3dDevice)
{
	/* �X�v���C�g�쐬 */
	D3DXCreateSprite(m_pd3dDevice,&m_pSprite);

	/* �e�N�X�`���f�[�^�̓ǂݍ��� */
	D3DXCreateTextureFromFile(m_pd3dDevice,strFileName,&m_pTexture);
}

//------------------------------------------------------
//	Name:	~CSprite
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
CSprite::~CSprite()
{
	/* �g�p�����������̊J�� */
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CSprite::Render()
{
	m_pSprite->Begin();

	/* �X�v���C�g��`�� */
	m_pSprite->Draw(m_pTexture, &m_rectStock, NULL, NULL, 0.0f, &m_vecStock,
					D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}
