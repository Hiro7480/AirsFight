//==========================================================
// LockOnMarker.cpp
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================
#include "LockOnMarker.h"

//----------------------------------------------------------
//	Name:	CLockOnMarker
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	  = D3D�f�o�C�X
//			TCHAR*			  srcFileName = �e�N�X�`���t�@�C����
//	Out:	�Ȃ�
//----------------------------------------------------------
CLockOnMarker::CLockOnMarker(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName)
			  :CSprite(d3dDevice, srcFileName)
{
	/* �����o�ϐ��̏����� */
	m_dwStatus = NOT_LOCK;
	m_fAlpha   = 255.0f;
	m_fScale   = 1.0f;
}

//----------------------------------------------------------
//	Name:	~CLockOnMarker
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
CLockOnMarker::~CLockOnMarker()
{

}

//----------------------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CLockOnMarker::FrameMove()
{	
	/* ���b�N�I���ł��Ȃ��ꍇ */
	if(m_dwStatus == NOT_LOCK)	return;

	/* ���b�N�I�����\�ȏꍇ */
	else if(m_dwStatus == CAN_LOCK)
	{
		C2DGraphicObj::SetRec(0, 0, 64, 64);
		m_fAlpha = 255.0f;
		m_fScale = 1.0f;
	}
	/* �^�[�Q�b�g�Ƃ��ă��b�N�I�����Ă��� */
	else if(m_dwStatus == TAG_LOCK)
		C2DGraphicObj::SetRec(0, 0, 64, 64);

	/* ���݃��b�N�I�����Ă��� */
	else if(m_dwStatus == NOW_LOCK)
		C2DGraphicObj::SetRec(64, 0, 128, 64);


	/* �^�[�Q�b�g�Ƃ��ă��b�N�I���ł���ꍇ�ƁA*/
	/* ���݃��b�N�I�����Ă���ꍇ�� */
	/* ������Ƃ����A�j���[�V���������� */
	if(m_dwStatus == TAG_LOCK || m_dwStatus == NOW_LOCK)
	{
		/* �X�P�[���l��1.0�ȉ��Ȃ珉���� */
		if(m_fScale <= 1.0f)
		{
			m_fAlpha = 128;
			m_fScale = 1.5f;
		}
		/* ���񂾂񏬂����Ȃ�Ȃ���s�����ɂȂ� */
		m_fScale -= 0.025f;
		m_fAlpha += 6.0f;
	}

	/* ��ʂ̕`��ʒu�ɃX�P�[���l���l���ɓ���ďC�� */
	m_vecBase.x -= 32.0f * m_fScale;
	m_vecBase.y -= 32.0f * m_fScale;

}

//----------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------------------
void CLockOnMarker::Render()
{
	D3DXVECTOR2 vec2;

	m_pSprite->Begin();

	/* �X�v���C�g��`�� */
	vec2 = D3DXVECTOR2(m_fScale, m_fScale);
	m_pSprite->Draw(m_pTexture, &m_rectStock, &vec2,
		NULL, 0.0f, &m_vecStock, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));

	m_pSprite->End();
}