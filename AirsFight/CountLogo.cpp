//==========================================================
// CountLogo.cpp
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#include "CountLogo.h"

//------------------------------------------------------
//	Name:	CCountLogo
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	 d3dDevice = D3D�f�o�C�X
//			, LPDIRECT3DTEXTURE8 pTexture  = �e�N�X�`��
//	Out:	�Ȃ�
//------------------------------------------------------
CCountLogo::CCountLogo(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture)
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

}

//----------------------------------------------
//	Name:	~CCountLogo
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CCountLogo::~CCountLogo()
{

}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CCountLogo::FrameMove()
{
	/* �A�j���J�E���^�[�ɂ��A�e�N�X�`���̎g�����������߂� */
	switch(m_nAnimeCnt / 60)
	{
		/* �u�J�E���g�R�v��\������ */
		case 0:
			C2DGraphicObj::SetRec(256, 0, 383, 127);
			break;
		/* �u�J�E���g�Q�v��\������ */
		case 1:
			C2DGraphicObj::SetRec(128, 0, 255, 127);
			break;
		/* �u�J�E���g�P�v��\������ */
		case 2:
			C2DGraphicObj::SetRec( 0, 0, 127, 127);
			break;
	}

	/* �A�j���J�E���^�[�ɂ��A���t�@�l�ƃX�P�[���l�𑀍� */
	int	nCnt = m_nAnimeCnt % 60;

	/* �A�j���[�V������0�`29�Ȃ�A���񂾂�s�����ɂ��Ă����Ȃ���k�����Ă��� */
	if(nCnt < 30)
	{
		m_nAlphaBase = (255 / 30) * nCnt;
		m_fScaleBase = (2.0f-(2.0f/30.0f)*nCnt)+1.0f;
	}

	/* �A�j���[�V������30�`59�Ȃ�Œ� */
	else
	{
		m_nAlphaBase = 255;
		m_fScaleBase = 1.0f;
	}

	/* �\���ʒu�̐ݒ� */
	C2DGraphicObj::SetVec(D3DXVECTOR2(320-(64*m_fScaleBase), 240-(64*m_fScaleBase)));

	/* �A�j���J�E���^�[�̃C���N�������g */
	m_nAnimeCnt++;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		LPD3DXSPRITE pSprite
//	Out:	�Ȃ�
//----------------------------------------------
void CCountLogo::Render(LPD3DXSPRITE pSprite)
{
	D3DXVECTOR2 vec2(m_fScaleStock, m_fScaleStock);

	/* �����l����ꂽ�X�v���C�g�`�� */
	pSprite->Draw(	m_pTexture,
					&m_rectStock,
					&vec2,
					NULL,
					0.0f,
					&m_vecStock,
					D3DCOLOR_ARGB(m_nAlphaStock, 255, 255, 255) );

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CCountLogo::UpDate()
{
	C2DGraphicObj::UpDate();

	/* �����l�̍X�V */
	m_nAlphaStock = m_nAlphaBase;

	/* �X�P�[���l�̍X�V */
	m_fScaleStock = m_fScaleBase;

}