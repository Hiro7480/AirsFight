//==========================================================
// EnergyGauge.cpp
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================
#include "EnergyGauge.h"

//----------------------------------------------------------
//	Name:	CEnergyGauge
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3D�f�o�C�X
//			TCHAR*			  srcFileName = �e�N�X�`���t�@�C����
//	Out:	�Ȃ�
//----------------------------------------------------------
CEnergyGauge::CEnergyGauge(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName)
			 :CSprite(d3dDevice, srcFileName)
{
	/* �ϐ��̏����� */
	m_nMaxEnergy = 0;
	m_nNowEnergy = 0;

	/* ��{�`��ʒu�̃Z�b�g */
	m_vecPos = D3DXVECTOR2(40, 120);
}

//----------------------------------------------------------
//	Name:	~CEnergyGauge
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
CEnergyGauge::~CEnergyGauge()
{

}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CEnergyGauge::FrameMove()
{
	int	nGaugeNum;	// �`�悷��Q�[�W�̐�

	/* �ő�G�l���M�[�l�ƌ��݃G�l���M�[�l����A */
	/* �`�悷��Q�[�W�̐������Ƃ߂� */
	nGaugeNum = (int) (30.0f * ((float)m_nNowEnergy / (float)m_nMaxEnergy));

	/* �Q�[�W�̐����烌�N�g�����߂� */
	int	nTop;
	nTop = 300 - (10 * nGaugeNum);
	C2DGraphicObj::SetRec(100, nTop, 149, 299);

	/* ��ʂɕ`�悷����W�l�����߂� */
	C2DGraphicObj::SetVec(D3DXVECTOR2(m_vecPos.x, m_vecPos.y+nTop+10.0f));

}

//----------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CEnergyGauge::Render()
{
	RECT rc;

	/* �`��J�n */
	m_pSprite->Begin();

	/* �Q�[�W�̔w�i�𔼓����ɕ`�悷�� */
	SetRect(&rc, 50, 0, 99, 319);
	m_pSprite->Draw(m_pTexture, &rc, NULL, NULL, 0.0f, &m_vecPos,
					D3DCOLOR_ARGB(128, 255, 255, 255));

	/* �Q�[�W�̊O�g��`�悷�� */
	SetRect(&rc, 0, 0, 49, 319);
	m_pSprite->Draw(m_pTexture, &rc, NULL, NULL, 0.0f, &m_vecPos,
					D3DCOLOR_ARGB(255, 255, 255, 255));

	/* �Q�[�W��`�悷�� */
	m_pSprite->Draw(m_pTexture, &m_rectStock, NULL, NULL, 0.0f, &m_vecStock,
					D3DCOLOR_ARGB(255, 255, 255, 255));

	/* �`��I�� */
	m_pSprite->End();	

}