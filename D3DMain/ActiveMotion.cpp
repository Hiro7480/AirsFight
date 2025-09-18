//==========================================================
// Active.cpp
// Auther : ���� ���V
// Data   : 2002/04/16
//==========================================================

#include "ActiveMotion.h"

//**********************************************
//	CActiveFrame�N���X
//**********************************************

//----------------------------------------------
//	Name:	CActiveFrame
//	Func:	�R���X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CActiveFrame::CActiveFrame()
{
	m_pMeshFrame = NULL;
	m_pMotionFrame = NULL;

	D3DXQuaternionIdentity(&m_qtMotion);
	m_vecMotion *= 0;
}

//----------------------------------------------
//	Name:	~CActiveFrame
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CActiveFrame::~CActiveFrame()
{
	Destroy();
}

//------------------------------------------------------------------
//	Name:	Create
//	Func:	������
//	in:		CMeshFrame* pMeshFrame		= �Ή����郁�b�V���t���[��
//			CMotionFrame* pMotionFrame	= �Ή����郂�[�V�����t���[��
//	Out:	HRESULT
//------------------------------------------------------------------
HRESULT CActiveFrame::Create(CMeshFrame* pMeshFrame, CMotionFrame* pMotionFrame)
{
	m_pMeshFrame = pMeshFrame;
	m_pMotionFrame = pMotionFrame;

	return S_OK;
}

//----------------------------------------------
//	Name:	ComputQuat
//	Func:	���ݎ��Ԃ����]�␳�l�����߂�
//	in:		int nActiveTime = ���ݎ���
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveFrame::ComputQuat(int nActiveTime)
{
	int i;

	/* ��]�L�[���Ȃ������玸�s�Ƃ݂Ȃ� */
	if(m_pMotionFrame->m_nRotKeyNum == 0)
		return E_FAIL;

	/* ���ݎ��ԂƂ܂����������L�[�����邩�𔻒� */
	i=0;
	while(i<m_pMotionFrame->m_nRotKeyNum)
	{
		if(m_pMotionFrame->m_pRotKey[i].nTime == nActiveTime)	break;
		i++;
	}

	/* �܂����������L�[���������ꍇ�́A���̂܂܂̒l���i�[���ďI�� */
	if(i < m_pMotionFrame->m_nRotKeyNum)
	{
		m_qtMotion = m_pMotionFrame->m_pRotKey[i].quatRot;
		return S_OK;
	}

	/* �����L�[���Ȃ������ꍇ�� */
	/* �O��̈�ԋ߂��ɂ���L�[�l����⊮�l�����߂� */

	// �O��̃L�[����������
	int	nNextTime = -1;		// ���̃L�[
	int	nBackTime = -1;		// �O�̃L�[

	i=0;					// ��]�L�[�z��ւ̓Y�����Ƃ��Ă��g�p

	while(i < m_pMotionFrame->m_nRotKeyNum)
	{
		if(m_pMotionFrame->m_pRotKey[i].nTime > nActiveTime)
		{
			nNextTime = m_pMotionFrame->m_pRotKey[i].nTime;
			break;
		}
		else
			nBackTime = m_pMotionFrame->m_pRotKey[i].nTime;
		i++;
	}

	/* �O��̃L�[�ǂ��炩����������Ȃ������ꍇ�� */
	/* ���������L�[�̏������̂܂܎g�p���ďI�� */
	if(nNextTime == -1)
	{
		m_qtMotion = m_pMotionFrame->m_pRotKey[i-1].quatRot;
		return S_OK;
	}
	else if(nBackTime == -1)
	{
		m_qtMotion = m_pMotionFrame->m_pRotKey[i].quatRot;
		return S_OK;
	}

	/* �L�[����Ƃ����������ꍇ�͂��̕⊮�l����� */
	D3DXQUATERNION	qtTmp;
	float			fBlend;

	/* �u�����h�W�������߂� */
	fBlend = SuppleNum(nActiveTime, nNextTime, nBackTime);

	/* �N�I�[�^�j�I���̕⊮�l�����߂� */
	D3DXQuaternionSlerp(&qtTmp,
		&m_pMotionFrame->m_pRotKey[i-1].quatRot,
		&m_pMotionFrame->m_pRotKey[i].quatRot, fBlend);

	/* ���߂��l���i�[���ďI�� */
	m_qtMotion = qtTmp;
	return S_OK;
}

//----------------------------------------------
//	Name:	ComputVec
//	Func:	���ݎ��Ԃ���ʒu�␳�l�����߂�
//	in:		int nActiveTime = ���ݎ���
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveFrame::ComputVec(int nActiveTime)
{
	int i;

	/* �ʒu�L�[���Ȃ������玸�s�Ƃ݂Ȃ� */
	if(m_pMotionFrame->m_nPosKeyNum == 0)
		return E_FAIL;

	/* ���ݎ��ԂƂ܂����������L�[�����邩�𔻒� */
	i=0;
	while(i<m_pMotionFrame->m_nPosKeyNum)
	{
		if(m_pMotionFrame->m_pPosKey[i].nTime == nActiveTime)	break;
		i++;
	}

	/* �܂����������L�[���������ꍇ�́A���̂܂܂̒l���i�[���ďI�� */
	if(i < m_pMotionFrame->m_nPosKeyNum)
	{
		m_vecMotion = m_pMotionFrame->m_pPosKey[i].vecPos;
		return S_OK;
	}

	/* �����L�[���Ȃ������ꍇ�� */
	/* �O��̈�ԋ߂��ɂ���L�[�l����⊮�l�����߂� */

	// �O��̃L�[����������
	int	nNextTime = -1;	// ���̃L�[
	int	nBackTime = -1;	// �O�̃L�[

	i=0;				// �ʒu�L�[�z��̓Y�����Ƃ��Ă��g�p

	while(i < m_pMotionFrame->m_nPosKeyNum)
	{
		if(m_pMotionFrame->m_pPosKey[i].nTime > nActiveTime)
		{
			nNextTime = m_pMotionFrame->m_pPosKey[i].nTime;
			break;
		}
		else
			nBackTime = m_pMotionFrame->m_pPosKey[i].nTime;
		i++;
	}

	/* �O��̃L�[�ǂ��炩����������Ȃ������ꍇ�� */
	/* ���������L�[�̏������̂܂܎g�p���ďI�� */
	if(nNextTime == -1)
	{
		m_vecMotion = m_pMotionFrame->m_pPosKey[i-1].vecPos;
		return S_OK;
	}
	else if(nBackTime == -1)
	{
		m_vecMotion = m_pMotionFrame->m_pPosKey[i].vecPos;
		return S_OK;
	}

	/* �L�[����Ƃ����������ꍇ�͂��̕⊮�l����� */
	D3DXVECTOR3		vecTmp;
	float			fBlend;

	/* �u�����h�W�������߂� */
	fBlend = SuppleNum(nActiveTime, nNextTime, nBackTime);

	/* �x�N�g���̕⊮�l�����߂� */
	vecTmp=	m_pMotionFrame->m_pPosKey[i].vecPos - 
			m_pMotionFrame->m_pPosKey[i-1].vecPos;
	vecTmp *= fBlend;
	vecTmp += m_pMotionFrame->m_pPosKey[i-1].vecPos;

	/* ���߂��l���i�[���ďI�� */
	m_vecMotion = vecTmp;
	return S_OK;
}

//--------------------------------------------------------------
//	Name:	SupplementNum
//	Func:	��̐��l�̑傫���ق���1.0�A�������ق���0.0�Ƃ����ꍇ�A
//			�����ЂƂ̐��l�͂������A�����߂�
//	In:		int		nMiddle	= ���Ԃ̐��l
//			int		nMax	= �ő�l
//			int		nMin	= �ŏ��l
//	Out:	float
//--------------------------------------------------------------
float CActiveFrame::SuppleNum(int nMiddle, int nMax, int nMin)
{
	float	fTmp1,fTmp2;

	fTmp1 = float(nMax-nMin);
	fTmp2 = float(nMiddle-nMin);

	return fTmp2/fTmp1;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	�S�I�u�W�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveFrame::Destroy()
{
	return S_OK;
}

//**********************************************
//	CActiveData�N���X
//**********************************************

//----------------------------------------------
//	Name:	CActiveData
//	Func:	�R���X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CActiveData::CActiveData()
{
	for(int i=0; i<32; i++)
		m_pActiveFrame[i] = NULL;
	m_pMeshData = NULL;
	m_pMotionData = NULL;

	m_nActiveFrameNum = 0;
	m_nMaxTime = 0;
	m_nActiveTime = 0;
}

//----------------------------------------------
//	Name:	~CActiveData
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CActiveData::~CActiveData()
{
	Destroy();
}

//----------------------------------------------------------
//	Name:	CreateFrame
//	Func:	�t���[���f�[�^�̍쐬
//	in:		CMeshData* pMeshData =		�Ή����b�V���f�[�^
//			CMotionData* pMotionData =	�Ή����[�V�����f�[�^
//	Out:	HRESULT
//----------------------------------------------------------
HRESULT	CActiveData::CreateFrame(CMeshData* pMeshData, CMotionData* pMotionData)
{
	int i;

	/* ���ꂼ��̃��b�V���f�[�^�A���[�V�����f�[�^�̃t���[�������������m�F */
	if(pMeshData->GetFrameNum() != pMotionData->GetFrameNum())
		return E_FAIL;

	/* ���b�V���f�[�^�A���[�V�����f�[�^�̊i�[ */
	m_pMeshData = pMeshData;
	m_pMotionData = pMotionData;
	m_nActiveFrameNum = pMeshData->GetFrameNum();

	/* �A�j���[�V�����ő�t���[�����Ԃ̎擾 */
	m_nMaxTime = pMotionData->GetMaxFrame();

	/* �t���[���z���K�v���������Ɋm�� */
	for(i=0; i<m_nActiveFrameNum; i++)
		m_pActiveFrame[i] = new CActiveFrame;

	/* �Ή����郁�b�V���f�[�^�ƃ��[�V�����t���[�������ꂼ������ */
	CMeshFrame*			pMeshFrame;
	CMotionFrame*		pMotionFrame = m_pMotionData->GetListTop();

	for(i=0; i<m_nActiveFrameNum; i++)
	{
		/* ���ԂɃt���[�������b�V���f�[�^�̒����猩���A�i�[���� */
		pMeshFrame = m_pMeshData->GetFrame(i);
		m_pActiveFrame[i]->Create(pMeshFrame, pMotionFrame);

		/* ���̃f�[�^�� */
		pMotionFrame = pMotionFrame->GetNext();
	}
	return S_OK;
}

//----------------------------------------------
//	Name:	ComputMotion
//	Func:	���ݎ��Ԃ��烂�[�V�����␳�l���Z�o
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveData::ComputMotion()
{
	/* �S�Ă�ActiveFrame�ɂ����� */
	for(int i=0; i<m_nActiveFrameNum; i++)
	{
		m_pActiveFrame[i]->ComputQuat(m_nActiveTime);	// ��]�␳�l�̎Z�o
		m_pActiveFrame[i]->ComputVec(m_nActiveTime);	// �ʒu�␳�l�̎Z�o
	}
	return S_OK;
}

//----------------------------------------------
//	Name:	Run
//	Func:	�A�j���[�V�����̍Đ�
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveData::Run()
{
	m_nActiveTime++;
	if(m_nActiveTime > m_nMaxTime)
		m_nActiveTime = 0;

	return S_OK;
}

//----------------------------------------------
//	Name:	Destroy
//	Func:	�S�I�u�W�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveData::Destroy()
{
	for(int i=0; i<32; i++)
		SAFE_DELETE(m_pActiveFrame[i])
	return S_OK;
}

//**********************************************
//	CActiveMotion�N���X
//**********************************************

//----------------------------------------------
//	Name:	CActiveMotion
//	Func:	�R���X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CActiveMotion::CActiveMotion()
{
	for(int i=0; i<32; i++)
	{
		m_pActiveData[i] = NULL;
		m_fBlendNum[i] = 0;
		D3DXMatrixIdentity(&m_matMotion[i]);
		D3DXMatrixIdentity(&m_matStock[i]);
	}
	m_fBlendNum[0] = 1.0f;
	m_nActiveDataNum = 0;
	m_nMeshFrameNum = 0;
	m_pMeshData = 0;
}

//----------------------------------------------
//	Name:	~CActiveMotion
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CActiveMotion::~CActiveMotion()
{
	Destroy();
}

//----------------------------------------------
//	Name:	LoadMesh
//	Func:	���b�V���f�[�^�̓ǂݍ���
//	in:		CMeshData* pMeshData
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::LoadMesh(CMeshData* pMeshData)
{
	m_pMeshData = pMeshData;

	/* �t���[���������b�V������擾 */
	m_nMeshFrameNum = pMeshData->GetFrameNum();

	return S_OK;
}

//----------------------------------------------
//	Name:	LoadMotion
//	Func:	���[�V�����f�[�^�̓ǂݍ���
//	in:		CMotionData* pMotionData
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::LoadMotion(CMotionData* pMotionData)
{
	/* �|�C���^�z��ɍ쐬�A������ */
	m_pActiveData[m_nActiveDataNum] = new CActiveData;
	m_pActiveData[m_nActiveDataNum]->CreateFrame(m_pMeshData, pMotionData);

	/* �f�[�^���𑝂₷ */
	m_nActiveDataNum++;

	return S_OK;
}

//----------------------------------------------
//	Name:	ComputMatrix
//	Func:	���ꂼ��̃��[�V�����ƃu�����h�W������
//			���݂̃��[�V�����}�g���N�X�����߂�
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::ComputMatrix()
{
	D3DXQUATERNION	qtTmp;		// �v�Z�p�N�I�[�^�j�I��
	D3DXVECTOR3		vecTmp;		// �v�Z�p�x�N�g��

	for(int i=0; i<m_nMeshFrameNum; i++)
	{
		qtTmp *= 0.0f;			// �v�Z�p�N�I�[�^�j�I���̏�����
		vecTmp *= 0.0f;			// �v�Z�p�x�N�g���̏�����

		for(int j=0; j<m_nActiveDataNum; j++)
		{
			/* ��]�␳�l�̌v�Z */
			qtTmp += m_pActiveData[j]->m_pActiveFrame[i]->GetQuat()*m_fBlendNum[j];
			/* �ʒu�␳�l�̌v�Z */
			vecTmp += m_pActiveData[j]->m_pActiveFrame[i]->GetVec()*m_fBlendNum[j];
		}

		/* �v�Z���ʂ��}�g���N�X�ɕϊ����� */
		D3DXMatrixRotationQuaternion(&m_matMotion[i], &qtTmp);
		m_matMotion[i]._41 += vecTmp.x;
		m_matMotion[i]._42 += vecTmp.y;
		m_matMotion[i]._43 += vecTmp.z;
	}

	return S_OK;
}

//----------------------------------------------
//	Name:	ComputAllMotion
//	Func:	�S�Ẵ��[�V�����t���[����
//			���[�V�����f�[�^�̌v�Z
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::ComputAllMotion()
{
	/* �S�Ẵ��[�V�����f�[�^����ComputMotion���Ăяo�� */
	for(int i=0; i<m_nActiveDataNum; i++)
		m_pActiveData[i]->ComputMotion();

	return S_OK;
}

//--------------------------------------------------
//	Name:	ChangeMotion
//	Func:	���݂̃��[�V�������w�肵�����[�V�����ɕύX
//			�u�����h�W���̑���
//	in:		int		nNum		= �w�胂�[�V����
//			float	fChangeSpeed= ���[�V�����ύX���x
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CActiveMotion::ChangeMotion(int nNum, float fChangeSpeed)
{
	int i;

	/* �w�胂�[�V�������Ȃ��ꍇ�͎��s�Ƃ݂Ȃ� */
	if(nNum >= m_nActiveDataNum)
		return E_FAIL;

	/* �v���X�����̂݁A�ޔ����Ă��� */
	float fTmp=m_fBlendNum[nNum] + fChangeSpeed;
	if(fTmp > 1.0f)	fTmp = 1.0f;

	/* �S�Ẵu�����h�W�����}�C�i�X����i�������낤����j*/
	for(i=0; i<m_nActiveDataNum; i++)
		if((m_fBlendNum[i]-=fChangeSpeed) < 0.0f)
			m_fBlendNum[i]=0.0f;

	/* �ޔ�����������߂� */
	m_fBlendNum[nNum] = fTmp;

	/* �u�����h�W���̐��ځi�u�����h�W���̍��v��1.0�ɂȂ�悤�ɒ����j*/
	float fTotal = 0;
	for(i=0; i<m_nActiveDataNum; i++)	fTotal += m_fBlendNum[i];

	/* ���v��1.0f�ȏ�̏ꍇ */
	if(fTotal > 1.0f)
		for(i=0; i<m_nActiveDataNum; i++)
			m_fBlendNum[i] = m_fBlendNum[i] / fTotal;

	/* ���v��1.0f�ȉ��̏ꍇ */
	else
		m_fBlendNum[0] += (1.0f - fTotal);


	return S_OK;
}

//--------------------------------------------------
//	Name:	ChangeMotion
//	Func:	���݂̃��[�V�������w�肵�����[�V�����ɕύX
//			��̎w��̊Ԃ����
//			�u�����h�W���̑���
//	in:		int		nNum1		= �w�胂�[�V�����P
//			int		nNum2		= �w�胂�[�V�����Q
//			float	fChangeSpeed= ���[�V�����ύX���x
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CActiveMotion::ChangeMotion(int nNum1, int nNum2, float fChangeSpeed)
{
	int i;

	/* �w�胂�[�V�������Ȃ��ꍇ�͎��s�Ƃ݂Ȃ� */
	if(nNum1 >= m_nActiveDataNum || nNum2 >= m_nActiveDataNum)
		return E_FAIL;

	/* �v���X�����̂݁A�ޔ����Ă��� */
	float fTmp1 = m_fBlendNum[nNum1]+=fChangeSpeed;	if(fTmp1>1.0f) fTmp1=1.0f;
	float fTmp2 = m_fBlendNum[nNum2]+=fChangeSpeed;	if(fTmp2>1.0f) fTmp2=1.0f;

	/* �S�Ẵu�����h�W�����}�C�i�X����i�������낤����j*/
	for(i=0; i<m_nActiveDataNum; i++)
		if((m_fBlendNum[i]-=fChangeSpeed) < 0.0f)
			m_fBlendNum[i]=0.0f;

	/* �ޔ�����������߂� */
	m_fBlendNum[nNum1] = fTmp1;
	m_fBlendNum[nNum2] = fTmp2;

	/* �u�����h�W���̐��ځi�u�����h�W���̍��v��1.0�ɂȂ�悤�ɒ����j*/
	float fTotal = 0;
	for(i=0; i<m_nActiveDataNum; i++)	fTotal += m_fBlendNum[i];

	/* ���v��1.0f�ȏ�̏ꍇ */
	if(fTotal > 1.0f)
		for(i=0; i<m_nActiveDataNum; i++)
			m_fBlendNum[i] = m_fBlendNum[i] / fTotal;

	/* ���v��1.0f�ȉ��̏ꍇ */
	else
		m_fBlendNum[0] += (1.0f - fTotal);

	return S_OK;
}

//------------------------------------------------------
//	Name:	Play
//	Func:	���܂��܂ȃf�[�^�X�V
//	in:		�Ȃ�
//	Out:	HRESULT
//------------------------------------------------------
HRESULT CActiveMotion::Play()
{
	/* �S�Ẵ��[�V�����̍Đ� */
	for(int i=0; i<m_nActiveDataNum; i++)
		m_pActiveData[i]->Run();

	/* �S�Ẵ��[�V�����t���[���̌��݃N�I�[�^�j�I�������߂� */
	ComputAllMotion();

	/* �u�����h�W���ɂ�蕡���̃��[�V�����̕⊮�l�����߂� */
	ComputMatrix();

	return S_OK;
}

//------------------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	HRESULT
//------------------------------------------------------
HRESULT CActiveMotion::Render()
{
	m_pMeshData->Render(m_matStock);
	return S_OK;
}

//--------------------------------------------------
//	Name:	UpDate
//	Func:	�`��p�}�g���N�X�X�V
//	in:		�Ȃ�
//	Out:	HRESULT
//--------------------------------------------------
HRESULT CActiveMotion::UpDate()
{
	for(int i=0; i<m_nMeshFrameNum; i++)
		m_matStock[i] = m_matMotion[i];

	return S_OK;
}


//----------------------------------------------
//	Name:	Destroy
//	Func:	�S�I�u�W�F�N�g�̍폜
//	in:		�Ȃ�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CActiveMotion::Destroy()
{
	for(int i=0; i<32; i++)
		SAFE_DELETE(m_pActiveData[i]);
	return S_OK;
}
