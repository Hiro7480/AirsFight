//==========================================================
// ScrollBG.cpp
// Auther : ���� ���V
// Data   : 2002/05/01
//==========================================================

#include "ScrollBG.h"


//------------------------------------------------------------------
//	Name:	CScrollBG
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice   = D3D�f�o�C�X
//			TCHAR*			  strFileName = �e�N�X�`���t�@�C����
//			float			  fHeight	  = �e�N�X�`���̍����T�C�Y
//			float			  fWidth	  = �e�N�X�`���̕��T�C�Y
//	Out:	�Ȃ�
//------------------------------------------------------------------
CScrollBG::CScrollBG(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName, float fHeight, float fWidth)
		:C2DGraphicObj(d3dDevice)
{
	/* �e�N�X�`���f�[�^�̓ǂݍ��� */
	D3DXCreateTextureFromFile(m_pd3dDevice,strFileName,&m_pTexture);

	/* �e�N�X�`���T�C�Y�̃Z�b�g */
	m_fHeight = fHeight;
	m_fWidth  = fWidth;

	/* �X�v���C�g�쐬 */
	D3DXCreateSprite(m_pd3dDevice,&m_pSprite);

	/* �\���ʒu�̏����� */
	m_vecBase.x = 0;
	m_vecBase.y = 0;
}

//------------------------------------------------------
//	Name:	~CScrollBG
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
CScrollBG::~CScrollBG()
{
	/* �g�p�����������̊J�� */
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CScrollBG::FrameMove()
{
	/* �摜���ړ��x�N�g�������������� */
	m_vecBase.x -= m_vecDir.x;
	m_vecBase.y -= m_vecDir.y;

	/* �e�N�X�`���T�C�Y�ȏ�͌��炳�Ȃ� */
	if(m_vecBase.x < -m_fWidth)		m_vecBase.x = 0;
	if(m_vecBase.y < -m_fHeight)	m_vecBase.y = 0;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CScrollBG::Render()
{
	float	fXPos, fYPos;

	D3DXVECTOR2 pos;

	/* �`��J�n */
	m_pSprite->Begin();

	/* ��ʈ�t���܂�܂ŃX�v���C�g��`�悷�� */
	for(fXPos=m_vecStock.x; fXPos<640; fXPos+=m_fWidth)
	{
		for(fYPos=m_vecStock.y; fYPos<480; fYPos+=m_fHeight)
		{
			pos.x = fXPos;
			pos.y = fYPos;
			m_pSprite->Draw(m_pTexture, NULL, NULL, NULL, 0.0f, &pos,
							D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	/* �`��I�� */
	m_pSprite->End();

}

