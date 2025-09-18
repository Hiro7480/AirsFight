//==========================================================
// TimeGraphic.cpp
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================
#include "TimeGraphic.h"

//----------------------------------------------------------
//	Name:	CTimeGraphic
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------------------
CTimeGraphic::CTimeGraphic(LPDIRECT3DDEVICE8 d3dDevice)
			 :CSprite(d3dDevice, "data\\game\\TimeGraphic.png")
{
	/* �ϐ��̏����� */
	m_lStartTime = 0;
	m_lNowTime   = 0;
	m_lLimitTime = 0;

	m_bPlay		 = false;

	/* ��{�`��ʒu�̃Z�b�g */
	m_vecPos = D3DXVECTOR2(400, 400);

	/* ���N�g�̏����� */
	for(int i=0; i<5; i++)
	{
		SetRect(&m_rcBase[i], 0,0,0,0);
	}
}

//----------------------------------------------------------
//	Name:	~CTimeGraphic
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
CTimeGraphic::~CTimeGraphic()
{

}

//----------------------------------------------------------
//	Name:	Start
//	Func:	���Ԍv���J�n
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CTimeGraphic::Start()
{
	/* �J�n���Ԃ̎擾 */
	time(&m_lStartTime);

	/* �J�n�t���O�𗧂Ă� */
	m_bPlay = true;
}

//----------------------------------------------------------
//	Name:	IsEnd
//	Func:	�c�萧�����Ԃ��Ȃ��Ȃ������H
//	in:		�Ȃ�
//	Out:	bool = �Ȃ��Ȃ��Ă�����TURE
//----------------------------------------------------------
bool CTimeGraphic::IsEnd()
{
	if(m_lLimitTime < 0)
	{
		/* ���Ԍv���t���O��߂� */
		m_bPlay = false;
		return true;
	}

	return false;
}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CTimeGraphic::FrameMove()
{
	/* ���Ԍv���łȂ���Ώ������s��Ȃ� */
	if(!m_bPlay) return;

	/* ���ݎ��Ԃ����߂� */
	time(&m_lNowTime);

	/* �J�n���Ԃ���̌o�ߎ��Ԃ����߂� */
	long lTmp;
	lTmp = m_lNowTime - m_lStartTime;

	/* �ő吧�����Ԃ���A�c�萧�����Ԃ����߂� */
	m_lLimitTime = m_lMaxTime - lTmp;

	/* �c�萧�����Ԃ�0�ȉ���������v�Z�����������Ȃ肻���Ȃ̂ŏI������ */
	if(m_lLimitTime < 0) return;

	/* �c�萧�����Ԃ𕪂ƕb�ɕ������� */
	long lMinute = m_lLimitTime / 60;
	long lSecond = m_lLimitTime % 60;

	/* �c�萧�����Ԃ���ARECT�l�����߂� */
	int nTmp;

	/* 10���̈ʂ�RECT�����߂� */
	nTmp = lMinute / 10;
	SetRect(&m_rcBase[0], 30*nTmp, 0, 30*(nTmp+1), 50);

	/* 1���̈ʂ�RECT�����߂� */
	nTmp = lMinute % 10;
	SetRect(&m_rcBase[1], 30*nTmp, 0, 30*(nTmp+1), 50);

	/* �u�F�v�̃}�[�N�͌Œ� */
	SetRect(&m_rcBase[2], 300, 0, 330, 50);

	/* 10�b�̈ʂ�RECT�����߂� */
	nTmp = lSecond / 10;
	SetRect(&m_rcBase[3], 30*nTmp, 0, 30*(nTmp+1), 50);

	/* 1�b�̈ʂ�RECT�����߂� */
	nTmp = lSecond % 10;
	SetRect(&m_rcBase[4], 30*nTmp, 0, 30*(nTmp+1), 50);
}

//----------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CTimeGraphic::Render()
{
	/* ���Ԍv�����łȂ�������`�悵�Ȃ� */
	if(!m_bPlay) return;

	/* �`��J�n */
	m_pSprite->Begin();

	/* ���Ԃ�`�悷�� */
	for(int i=0; i<5; i++)
	{
		m_pSprite->Draw(m_pTexture, &m_rcStock[i], NULL, NULL, 0.0f, 
			&D3DXVECTOR2(m_vecPos.x+(30*i), m_vecPos.y), D3DCOLOR_ARGB(255, 255, 255, 255));
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
void CTimeGraphic::UpDate()
{
	for(int i=0; i<5; i++)
	{
		m_rcStock[i] = m_rcBase[i];
	}
}