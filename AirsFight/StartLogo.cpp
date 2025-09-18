//==========================================================
// StartLogo.cpp
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#include "StartLogo.h"

//------------------------------------------------------
//	Name:	CStartLogo
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	 d3dDevice = D3D�f�o�C�X
//			, LPDIRECT3DTEXTURE8 pTexture  = �e�N�X�`��
//	Out:	�Ȃ�
//------------------------------------------------------
CStartLogo::CStartLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture)
		   :CListSprite(d3dDevice, pTexture)
{
	/* �A�j���J�E���^�[�̏����� */
	m_nAnimeCnt = 0;

	/* �����l�̏����� */
	m_nAlphaBase  = 0;
	m_nAlphaStock = 0;

	/* �X�P�[���l�̏����� */
	m_fScaleBase  = 0;
	m_fScaleStock = 0;

	/* �e�N�X�`���\���ʒu�̐ݒ� */
	C2DGraphicObj::SetRec( 0, 128, 511, 255);

}

//----------------------------------------------
//	Name:	~CStartLogo
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CStartLogo::~CStartLogo()
{

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStartLogo::FrameMove()
{
	/* �A�j���[�V������0�`59�Ȃ�A�Œ�ŕ\�������� */
	if(m_nAnimeCnt < 60)
	{
		m_nAlphaBase = 255;
		m_fScaleBase = 1.0f;
	}

	/* �A�j���[�V������60�`89�Ȃ�t�F�[�h�A�E�g */
	else
	{
		m_nAlphaBase = (255 / 30) * (30-(m_nAnimeCnt-30));
		m_fScaleBase = (5.0f-(5.0f/30.0f) * (30-(m_nAnimeCnt-60))) +1.0f;
	}

	/* �\���ʒu�̐ݒ� */
	C2DGraphicObj::SetVec(D3DXVECTOR2(320-(256*m_fScaleBase), 240-(64*m_fScaleBase)));

	/* �A�j���J�E���^�[�̃C���N�������g */
	m_nAnimeCnt++;

	/* �A�j���J�E���^�[��90�𒴂�����I������ */
	if(m_nAnimeCnt > 90)	m_bFlg = false;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		LPD3DXSPRITE pSprite
//	Out:	�Ȃ�
//----------------------------------------------
void CStartLogo::Render(LPD3DXSPRITE pSprite)
{
	D3DXVECTOR2 vec2(m_fScaleStock, m_fScaleStock);

	/* �����l����ꂽ�X�v���C�g�`�� */
	pSprite->Draw(m_pTexture,
		&m_rectStock,
		&vec2,
		NULL,
		0.0f,
		&m_vecStock,
		D3DCOLOR_ARGB(m_nAlphaStock, 255, 255, 255));
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CStartLogo::UpDate()
{
	C2DGraphicObj::UpDate();

	/* �����l�̍X�V */
	m_nAlphaStock = m_nAlphaBase;

	/* �X�P�[���l�̍X�V */
	m_fScaleStock = m_fScaleBase;

}