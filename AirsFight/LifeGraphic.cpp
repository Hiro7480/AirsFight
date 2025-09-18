//==========================================================
// LifeGraphic.cpp
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================
#include "LifeGraphic.h"

//----------------------------------------------------------
//	Name:	CLifeGraphic
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3D�f�o�C�X
//			TCHAR*			  srcFileName = �e�N�X�`���t�@�C����
//	Out:	�Ȃ�
//----------------------------------------------------------
CLifeGraphic::CLifeGraphic(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName)
			 :CSprite(d3dDevice, srcFileName)
{
	/* �ϐ��̏����� */
	m_nNextLife = 0;
	m_nNowLife  = 0;

	/* ��{�`��ʒu�̃Z�b�g */
	m_vecPos = D3DXVECTOR2(50, 20);

	/* ���N�g�̏����� */
	for(int i=0; i<4; i++)
	{
		SetRect(&m_rcBase[i], 0,0,0,0);
	}
}

//----------------------------------------------------------
//	Name:	~CLifeGraphic
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
CLifeGraphic::~CLifeGraphic()
{

}

//----------------------------------------------------------
//	Name:	InitLife
//	Func:	���C�t�l�̏�����
//	in:		int nLife	= ���C�t�̏����l
//	Out:	�Ȃ�
//----------------------------------------------------------
void CLifeGraphic::InitLife(int nLife)
{
	/* �ő僉�C�t�l���i�[ */
	m_nMaxLife = nLife;

	/* �ڕW���C�t�l�A���݃��C�t�l�Ƃ��Ɋi�[ */
	m_nNextLife = nLife;
	m_nNowLife  = nLife;
}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CLifeGraphic::FrameMove()
{
	float fTmp;

	/* ����LIFE�A�ڕWLIFE�Ƃ��ɂO�����̐��l�ɂ͍s���Ȃ��悤�ɂ��� */
	if(m_nNextLife < 0)	m_nNextLife = 0;
	if(m_nNowLife  < 0) m_nNowLife  = 0;

	/* ����LIFE��ڕWLIFE�ɋ߂Â��� */
	if		(m_nNextLife > m_nNowLife)
	{
		fTmp = ( (float)m_nNextLife-(float)m_nNowLife ) / 10.0f+0.5f;
		if(fTmp <= 1.0f)	fTmp = 1.0f;
		m_nNowLife += (int)fTmp;
	}

	else if	(m_nNextLife < m_nNowLife)
	{
		fTmp = ( (float)m_nNowLife-(float)m_nNextLife ) /10.0f+0.5f;
		if(fTmp <= 1.0f)	fTmp = 1.0f;
		m_nNowLife -= (int)fTmp;
	}

	/* �ő�LIFE�ƁA����LIFE����A�����̐F�����߂� */
	int		nRectTop;
	fTmp = (float)m_nNowLife / (float)m_nMaxLife;

	if		(fTmp > 0.66f)	nRectTop = 0;	// 2/3�ȏ゠��Η�
	else if	(fTmp > 0.33f)	nRectTop = 80;	// 1/3�ȏ゠��Ή��F
	else					nRectTop = 160;	// ����ȉ��Ȃ�ΐ�

	/* ����LIFE����ARECT�l�����߂� */
	int nTmp;
	int	nLife;
	/* 1000�̈ʂ�RECT�����߂� */
	nTmp = m_nNowLife / 1000;
	SetRect(&m_rcBase[0], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);

	/* 100�̈ʂ�RECT�����߂� */
	nLife = m_nNowLife % 1000;
	nTmp = nLife / 100;
	SetRect(&m_rcBase[1], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);

	/* 10�̈ʂ�RECT�����߂� */
	nLife = m_nNowLife % 100;
	nTmp = nLife / 10;
	SetRect(&m_rcBase[2], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);

	/* 1�̈ʂ�RECT�����߂� */
	nLife = m_nNowLife % 10;
	nTmp = nLife;
	SetRect(&m_rcBase[3], 50*nTmp, nRectTop, 50*(nTmp+1), nRectTop+80);
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CLifeGraphic::Render()
{
	RECT rcTmp;
	D3DXVECTOR2 vec2;

	/* �`��J�n */
	m_pSprite->Begin();

	/* �w�i�𔼓����ŕ`�悷�� */
	SetRect(&rcTmp, 0, 330, 210, 420);
	vec2 = D3DXVECTOR2(m_vecPos.x - 5.0f, m_vecPos.y - 5.0f);
	m_pSprite->Draw(m_pTexture, &rcTmp, NULL, NULL, 0.0f,
		&vec2, D3DCOLOR_ARGB(128, 255, 255, 255));

	/* �O�g��`�悷�� */
	SetRect(&rcTmp, 0, 240, 210, 330);
	vec2 = D3DXVECTOR2(m_vecPos.x - 5.0f, m_vecPos.y - 5.0f);
	m_pSprite->Draw(m_pTexture, &rcTmp, NULL, NULL, 0.0f,
		&vec2, D3DCOLOR_ARGB(255, 255, 255, 255));


	/* ���C�t��`�悷�� */
	for (int i = 0; i < 4; i++)
	{
		vec2 = D3DXVECTOR2(m_vecPos.x + (50 * i), m_vecPos.y);
		m_pSprite->Draw(m_pTexture, &m_rcStock[i], NULL, NULL, 0.0f,
			&vec2, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	/* �`��I�� */
	m_pSprite->End();
}

//----------------------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CLifeGraphic::UpDate()
{
	for(int i=0; i<4; i++)
	{
		m_rcStock[i] = m_rcBase[i];
	}
}