//==========================================================
// CCamera.cpp
// Auther : ���� ���V
// Data   : 2002/02/25
//==========================================================

#include "Camera.h"

//----------------------------------------------
//	Name:	CCamera
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3D�f�o�C�Xz
//	Out:	�Ȃ�
//----------------------------------------------
CCamera::CCamera(LPDIRECT3DDEVICE8 d3dDevice)
		:C3DGraphicObj(d3dDevice)
{
	m_fLength = 30.0f;			// �ΏۂƂ̋����̐ݒ�
	m_fFrameSpeed = 2.0f;		// �J����1�t���[���ړ��ʂ̐ݒ�

	m_fNowYaw = 180.0f;
	m_fNextYaw = 180.0f;
	m_fNowPitch = 0.0f;
	m_fNextPitch = 0.0f;
}

//----------------------------------------------
//	Name:	~CCamera
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CCamera::~CCamera()
{

}

//------------------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		CChara* pChara = �v���C���[�N���X�ւ̃|�C���^
//	Out:	�Ȃ�
//------------------------------------------------------
void CCamera::FrameMove(CMyPlayer* pMyPlayer)
{
	D3DXVECTOR3 vec;
	D3DXMATRIX mat;

	/* ���b�N�I�����Ă��Ȃ��Ƃ� */
	if(!pMyPlayer->GetLockFlg())
	{
		/* �ڕW�ƂȂ�p�x�̊i�[ */
		mat = pMyPlayer->GetMatBase();
		vec = GetNormalVec3ToMat(NULL, &mat);
		SetNextYaw(&vec);
		SetNextPitch(pMyPlayer->GetPitch()-10.0f);

		// ���݊p�x��ڕW�p�x�ɋ߂Â���
		MoveYaw();
		MovePitch();

		// ���݊p�x����J�����ʒu�̐ݒ�
		SetPosition(pMyPlayer);
	}

	/* ���b�N�I�����Ă���Ƃ� */
	else
	{
		/* �L�������ڕW�ւ̒P�ʕ����x�N�g���̎Z�o */
		D3DXVECTOR3	vecTmp;
		vecTmp = pMyPlayer->GetLockVec() - pMyPlayer->GetPosBase();
		D3DXVec3Normalize(&vecTmp, &vecTmp);
		vecTmp.y -= 0.2f;

		/* �P�ʕ����x�N�g���l�ɂ��ڕW�ƂȂ�p�x���Z�o */
		SetNextYaw(&vecTmp);
		SetNextPitch(&vecTmp);

		/* ���݊p�x��ڕW�p�x�ɋ߂Â��� */
		MoveYaw();
		MovePitch();

		/* ���݊p�x����J�����ʒu�̐ݒ� */
		SetPosition(pMyPlayer);
	}
}
//----------------------------------------------
//	Name:	Render
//	Func:	�`�掞�p�̏���
//	in:		CChara* pChara = �L�����N�^�N���X
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::Render(CChara* pChara)
{
	D3DXVECTOR3 vec1 = pChara->GetPosStock();
	D3DXVECTOR3 vec2(0.0f, 1.0f, 0.0f);

	/* �Ώۈʒu�ƃJ�����ʒu����r���[�ϊ��}�g���N�X���Z�o���� */
	D3DXMatrixLookAtLH(&m_matStock, &m_vecStock, &vec1, &vec2);

	/* �J�����ʒu�ݒ� */
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matStock );
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�`�掞�p�ϐ��̍X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::UpDate()
{
	C3DGraphicObj::UpDate();
	m_vecStock = m_vecPos;
}

//----------------------------------------------
//	Name:	SetPosition
//	Func:	�J�����ʒu�����݊p�x�ɂ��Z�o
//	in:		CChara* pChara	= �L�����N�^�N���X
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::SetPosition(CChara* pChara)
{
	D3DXVECTOR3	vecTmp;
	D3DXMATRIX	matTmp1;
	D3DXMATRIX	matTmp2;

	// ���݊p�x���x����]�s������
	D3DXMatrixRotationY(&matTmp1, D3DXToRadian(m_fNowYaw));

	// ���݊p�x���w����]�s������
	D3DXMatrixRotationX(&matTmp2, D3DXToRadian(m_fNowPitch));

	// �����̉�]�s������߂�
	matTmp1 = matTmp2 * matTmp1;

	// �J�����̃��[�J�����W���쐬����
	D3DXVECTOR3 v = D3DXVECTOR3(0, 0, m_fLength);
	D3DXVec3TransformCoord(&vecTmp, &v, &matTmp1);

	// ���[�J�����W�����[���h���W�ɕϊ�����
	vecTmp.x += pChara->GetPosBase().x;
	vecTmp.y += pChara->GetPosBase().y;
	vecTmp.z += pChara->GetPosBase().z;

	// �J�������W�Ɋi�[
	m_vecPos = vecTmp;
}

//----------------------------------------------
//	Name:	SetNowYaw
//	Func:	����Yaw�p�x���J�����ʒu�ƑΏۈʒu����Z�o
//	in:		CChara* pChara = �L�����N�^�N���X
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::SetNowYaw(CChara* pChara)
{
	D3DXVECTOR3	vecTmp;
	vecTmp = pChara->GetPosBase() - m_vecPos;
	GetVec3Inverce(&vecTmp, &vecTmp);

	m_fNowYaw  = D3DXUntiRagian((float)atan2(vecTmp.x, vecTmp.z));
}

//----------------------------------------------
//	Name:	SetNowPitch
//	Func:	����Pitch�p�x���J�����ʒu�ƑΏۈʒu����Z�o
//	in:		CChara* pChara = �L�����N�^�N���X
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::SetNowPitch(CChara* pChara)
{
	D3DXVECTOR3	vecTmp;
	vecTmp =m_vecPos - pChara->GetPosBase();
	GetVec3Inverce(&vecTmp, &vecTmp);

	// X,Z���̒��������߂�
	float	fTmp;
	fTmp = GetLengthEX(&vecTmp, true, false, true);

	m_fNowPitch  = D3DXUntiRagian((float)atan2(vecTmp.y, fTmp));
}

//----------------------------------------------
//	Name:	SetNextYaw
//	Func:	�w�肵�������ɃJ�������������邽�߂ɁA
//			�ڕW�ƂȂ�Yaw�p�x���Z�o
//	in:		D3DXVECTOR3* vecIn
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::SetNextYaw(D3DXVECTOR3* vecIn)
{
	// �x�N�g�����t�ɂ���
	D3DXVECTOR3	vecTmp;
	vecTmp = GetVec3Inverce(NULL, vecIn);

	// �p�x�̌v�Z
	m_fNextYaw = D3DXUntiRagian((float)atan2(vecTmp.x, vecTmp.z));

	// 360�𒴂�����C��
	if(m_fNextYaw >= 360.0f)		m_fNextYaw -= 360.0f;
	else if(m_fNextYaw < 0.0f)		m_fNextYaw += 360.0f;
}

//----------------------------------------------
//	Name:	SetNextPitch
//	Func:	�w�肵�������ɃJ�������������邽�߂ɁA
//			�ڕW�ƂȂ�Pitch�p�x���Z�o
//	in:		D3DXVECTOR3* vecIn
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::SetNextPitch(D3DXVECTOR3* vecIn)
{
	// �x�N�g�����t�ɂ���
	D3DXVECTOR3	vecTmp;
	vecTmp = GetVec3Inverce(NULL, vecIn);

	// X,Z���̒��������߂�
	float	fTmp;
	fTmp = GetLengthEX(&vecTmp, true, false, true);

	// �p�x�̌v�Z
	m_fNextPitch = D3DXUntiRagian((float)atan2(-vecTmp.y, fTmp));

	// 360�𒴂�����C��
	if(m_fNextPitch >= 360.0f)		m_fNextPitch -= 360.0f;
	else if(m_fNextPitch < 0.0f)	m_fNextPitch += 360.0f;
}

//----------------------------------------------
//	Name:	SetNextPitch
//	Func:	�P���ɖڕW�ɂȂ�Pitch�p�x���Z�b�g
//	in:		float fPitch = Pitch�p�x�l
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::SetNextPitch(float fPitch)
{
	m_fNextPitch = fPitch;
}

//----------------------------------------------
//	Name:	MoveYaw
//	Func:	����Yaw�p�x�l��ڕWYaw�p�x�l�ɋ߂Â���
//	in:		D3DXVECTOR3* vecIn
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::MoveYaw()
{
	// �J��������]������ہA�E��肩����肩
	// �ǂ��炪�߂�������
	// �ڕW�p�x�ƌ��݊p�x�������Ȃ珈�������Ȃ�
	if(m_fNowYaw != m_fNextYaw)
	{
		float fTmp;
		fTmp = m_fNowYaw - m_fNextYaw;
		// 360�𒴂�����C��
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		// �����i�}�C�i�X�j�̕����߂���
		if(fTmp < 180.0f)
		{
			// �ړ��ʂ̎Z�o
			m_fFrameSpeed = fTmp / 10.0f;	
			// �J�����ʒu�̈ړ�
			m_fNowYaw -= m_fFrameSpeed;
		}
		// �E���i�v���X�j�̕����߂���
		else
		{
			// �ړ��ʂ̎Z�o
			fTmp = 360.0f - fTmp;
			m_fFrameSpeed = fTmp / 10.0f;
			// �J�����ʒu�̈ړ�
			m_fNowYaw += m_fFrameSpeed;
		}
	}
	// 360�𒴂�����C��
	if(m_fNowYaw >= 360.0f)		m_fNowYaw -= 360.0f;
	else if(m_fNowYaw < 0.0f)	m_fNowYaw += 360.0f;
}

//----------------------------------------------
//	Name:	MovePitch
//	Func:	����Yaw�p�x�l��ڕWYaw�p�x�l�ɋ߂Â���
//	in:		D3DXVECTOR3* vecIn
//	Out:	�Ȃ�
//----------------------------------------------
void CCamera::MovePitch()
{
	// �J��������]������ہA�E��肩����肩
	// �ǂ��炪�߂�������
	// �ڕW�p�x�ƌ��݊p�x�������Ȃ珈�������Ȃ�
	if(m_fNowPitch != m_fNextPitch)
	{
		float fTmp;
		fTmp = m_fNowPitch - m_fNextPitch;
		// 360�𒴂�����C��
		if(fTmp >= 360.0f)		fTmp -= 360.0f;
		else if(fTmp < 0.0f)	fTmp += 360.0f;

		// �����i�}�C�i�X�j�̕����߂���
		if(fTmp < 180.0f)
		{
			// �ړ��ʂ̎Z�o
			m_fFrameSpeed = fTmp / 10.0f;	
			// �J�����ʒu�̈ړ�
			m_fNowPitch -= m_fFrameSpeed;
		}
		// �E���i�v���X�j�̕����߂���
		else
		{
			// �ړ��ʂ̎Z�o
			fTmp = 360.0f - fTmp;
			m_fFrameSpeed = fTmp / 10.0f;
			// �J�����ʒu�̈ړ�
			m_fNowPitch += m_fFrameSpeed;
		}
	}

	// 360�𒴂�����C��
	if(m_fNowPitch >= 360.0f)	m_fNowPitch -= 360.0f;
	else if(m_fNowPitch < 0.0f)	m_fNowPitch += 360.0f;
}
