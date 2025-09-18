//==========================================================
// MyFunction.h
// Func   : ����ėp�֐�
// Auther : ���� ���V
// Data   : 2002/01/15
//==========================================================
#include	"MyFunction.h"
//------------------------------------------
//	Name:	GetAngle
//	Func:	��̒����̒l����A���̊p�x�����߂�
//	In:		double			*dwY
//			double			*dwX
//	Out:	double
//------------------------------------------
double GetAngle(CONST double dwY, CONST double dwX)
{
	double dwTmp;
	dwTmp = atan2(dwY,dwX);

	// ���W�A���l���p�x�ɕϊ�
	dwTmp = (float)D3DXUntiRagian((float)dwTmp);

	return dwTmp;
}


//------------------------------------------
//	Name:	SetVec3Length
//	Func:	�x�N�g����C�ӂ̒����ɕԂ�
//	In:		D3DXVECTOR3*		pOut
//			CONST D3DXVECTOR3*	pIn
//			float				fLength
//	Out:	D3DXVECTOR3
//------------------------------------------
D3DXVECTOR3	SetVec3Length(D3DXVECTOR3* pOut, CONST D3DXVECTOR3*	pIn, float fLength)
{
	D3DXVECTOR3	vecTmp;

	D3DXVec3Normalize(&vecTmp,pIn);
	vecTmp *= fLength;

	if(pOut)*pOut = vecTmp;
	return vecTmp;
}

//------------------------------------------
//	Name:	GetVec3Inverce
//	Func:	�x�N�g�����t�ɂ��ĕԂ�(��)
//	In:		D3DXVECTOR3*		pOut
//			CONST D3DXVECTOR3*	pIn
//	Out:	D3DXVECTOR3
//------------------------------------------
D3DXVECTOR3 GetVec3Inverce(D3DXVECTOR3* pOut, CONST D3DXVECTOR3* pIn)
{
	D3DXVECTOR3	vecTmp = *pIn;

	vecTmp.x *= -1;
	vecTmp.y *= -1;
	vecTmp.z *= -1;

	if(pOut)	*pOut = vecTmp;
	return vecTmp;
}

//------------------------------------------
//	Name:	GetNormalVec3ToMat
//	Func:	�}�g���b�N�X����
//			�P�ʕ����x�N�g�������߂�
//	In:		D3DXVECTOR3*		pVecOut
//			CONST D3DXMATRIX*	pMatIn
//	Out:	D3DXVECTOR3
//------------------------------------------
D3DXVECTOR3 GetNormalVec3ToMat(D3DXVECTOR3* pVecOut, CONST D3DXMATRIX* pMatIn)
{
	D3DXVECTOR3 vec3l(0, 0, 1);			// ���[�J�����W�i�s�����x�N�g��
	D3DXVECTOR3	vec3w;					// ���[���h���W�i�s�����x�N�g��
	D3DXMATRIX	matTmp;

	matTmp = *pMatIn;

	// �Ώۂ̍��W�l���J�b�g
	matTmp._41 = 0;
	matTmp._42 = 0;
	matTmp._43 = 0;

	// �}�g���N�X����P�ʕ����x�N�g���ɕϊ�
	D3DXVec3TransformCoord(&vec3w, &vec3l, &matTmp);
	D3DXVec3Normalize(&vec3w,&vec3w);

	// �l��Ԃ�
	if(pVecOut)	*pVecOut = vec3w;
	return vec3w;
}

//----------------------------------------------------------
//	Name:	GetMatrixToVec
//	Func:	�ʒu�x�N�g���A�����x�N�g������
//			�}�g���N�X�����߂� (���s�������ߖ��g�p)
//	In:		D3DXMATRIX*			pMatOut	= �o�͗p�}�g���N�X
//			CONST D3DXVECTOR3*	pVecPos	= �ʒu�x�N�g��
//			CONST D3DXVECTOR3*	pVecDir = �����x�N�g��
//	Out:	D3DXMATRIX
//----------------------------------------------------------
D3DXMATRIX	GetMatrixToVec(D3DXMATRIX* pMatOut,
						   CONST D3DXVECTOR3* pVecPos,
						   CONST D3DXVECTOR3* pVecDir)

{
	D3DXMATRIX matTmp;
	float fYaw, fPitch, fRoll;

	/* �����x�N�g���̒l����A�p�x���������߂� */
	fYaw	= (float)atan2(pVecDir->x, pVecDir->z);
//	fPitch	= (float)atan2(pVecDir->z, pVecDir->y);
//	fRoll	= (float)atan2(pVecDir->y, pVecDir->x);

	fPitch = 0;
	fRoll = 0;

	/* ���ꂼ��̊p�x��������}�g���N�X�����߂� */
	D3DXMatrixRotationYawPitchRoll(&matTmp, -fYaw/2, fPitch, fRoll);

	/* �w��ʒu�ɕ��s�ړ������� */
	matTmp._41 = pVecPos->x;
	matTmp._42 = pVecPos->y;
	matTmp._43 = pVecPos->z;

	/* �l���i�[���ĕԂ� */
	if(pMatOut)	*pMatOut = matTmp;
	return matTmp;
}

//------------------------------------------
//	Name:	MatUpdate
//	Func:	�}�g���N�X����]�l�̂ݍX�V
//	In:		D3DXMATRIX*	pMatBase
//			D3DXMATRIX*	pMatRot
//	Out:	D3DXMATRIX
//------------------------------------------
D3DXMATRIX MatUpdate(const D3DXMATRIX* pMatBase, const D3DXMATRIX* pMatRot)
{
	D3DXMATRIX matTmp;

	D3DXMatrixIdentity(&matTmp);
	matTmp = *pMatRot * matTmp;

	// ���̍��W�l�𑫂�
	matTmp._41 = pMatBase->_41;
	matTmp._42 = pMatBase->_42;
	matTmp._43 = pMatBase->_43;

	return matTmp;
}

//------------------------------------------
//	Name:	GetLengthEX
//	Func:	�x�N�g���̎w�肵���������̒�����Ԃ�
//			(���Ƃ��΂x���𖳂����Ăw�C�y�������̒����𓾂鎞�Ɏg�p)
//	In:		const D3DXVECTOR3*	pVecIn
//			bool				XEnable
//			bool				YEnable
//			bool				ZEnable
//	Out:	float
//------------------------------------------
float GetLengthEX(const D3DXVECTOR3* pVecIn, bool XEnable, bool YEnable, bool ZEnable)
{
	D3DXVECTOR3	vecTmp;

	if(XEnable) vecTmp.x = pVecIn->x;	else vecTmp.x = 0;
	if(YEnable) vecTmp.y = pVecIn->y;	else vecTmp.y = 0;
	if(ZEnable) vecTmp.z = pVecIn->z;	else vecTmp.z = 0;

	return D3DXVec3Length(&vecTmp);

}
//------------------------------------------
//	Name:	D3DXUntiRagian
//	Func:	���W�A�����p�x�ɕϊ����ĕԂ�
//	In:		float	ragian = ���W�A���l
//	Out:	int			   = �ʏ�p�x(0�`360)
//------------------------------------------
float	D3DXUntiRagian(float ragian)
{
	return (ragian / 3.141592654f * 180.0f);
}

//------------------------------------------------------------------------------
//	Name:	SearchPlane
//	Func:	�w��ʒu�A�w��x�N�g���ɂ��
//			���b�V���f�[�^�̒��̈�ԋ߂��ʂƁA���̋��������߂�
//
//	In:		CMeshObject*			pMeshIn		= �ΏۂƂȂ郁�b�V��
//			CONST	D3DXMATRIX*		pMatIn		= ���b�V���̃}�g���b�N�X
//			CONST	D3DXVECTOR3*	pPosIn		= �w��x�N�g�������W
//			CONST	D3DXVECTOR3*	pVecIn		= �w������x�N�g��
//			D3DXVECTOR3*			pCrossOut	= ��_���W�l���i�[���ĕԂ�
//			D3DXPLANE*				pPlaneOut	= ���ʂ̖ʂ̎����i�[���ĕԂ�
//			float*					pfLengthOut	= �ʂ̌�_�Ƃ̋�����Ԃ�	
//	Out:	bool								= �ʂ̎擾�ɐ���������TRUE
//------------------------------------------------------------------------------
bool SearchPlane(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut, D3DXPLANE*	pPlaneOut, float* pfLengthOut)
{
	typedef struct {
		D3DXVECTOR3 v;
		D3DCOLOR color;
	} VERTEX;

	LPDIRECT3DVERTEXBUFFER8	pVB;		// ���_�o�b�t�@�C���^�[�t�F�C�X
	LPDIRECT3DINDEXBUFFER8	pIB;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�C�X
	DWORD	dwNumFaces;					// �ʂ̐�

	// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�ւ̃A�N�Z�X�p
	WORD	*pIndices;
	VERTEX	*pVertices;

	// �o�b�t�@�̃C���^�[�t�F�C�X�擾
	pMeshIn->GetSysMemMesh()->GetVertexBuffer(&pVB);
	pMeshIn->GetSysMemMesh()->GetIndexBuffer(&pIB);
	// �ʂ̐����擾
	dwNumFaces = pMeshIn->GetLocalMesh()->GetNumFaces();

	// �|���S����T��
	D3DXVECTOR3	Vertex[3];
	D3DXVECTOR3	CrossPoint;
	D3DXVECTOR3	CrossPointMax;		// �̗p�����_���W�l
	D3DXPLANE	PlaneTmp;

	D3DXPLANE	PlaneMax;			// �̗p����ʂ̎�
	float		fLengthMax=99999;	// �̗p����ʂƎw����W�Ƃ̋���
	float		fLengthTmp;
	DWORD		i;

	pVB->Lock(0,0,(BYTE**)&pVertices,0);
	pIB->Lock(0,0,(BYTE**)&pIndices,0);

	// �ʂ̐������J��Ԃ�
	for(i=0; i<dwNumFaces; i++)
	{
		// �C���f�b�N�X�o�b�t�@���A�|���S���̂R���_�����߂�
		Vertex[0] = pVertices[pIndices[i*3+0]*2].v;
		Vertex[1] = pVertices[pIndices[i*3+1]*2].v;
		Vertex[2] = pVertices[pIndices[i*3+2]*2].v;

		// ���_�����[���h�ϊ�(�H)
		D3DXVec3TransformCoord(&Vertex[0], &Vertex[0], pMatIn);
		D3DXVec3TransformCoord(&Vertex[1], &Vertex[1], pMatIn);
		D3DXVec3TransformCoord(&Vertex[2], &Vertex[2], pMatIn);

		// �O�̒��_����ʂ̎����Z�o����
		D3DXPlaneFromPoints(&PlaneTmp, &Vertex[0], &Vertex[1], &Vertex[2]);
		// ���ׂ����_�A�x�N�g���������ʂ̕\�ɂ��邩���ׂ�

		D3DXVECTOR3 negVec = (*pVecIn) * -1.0f;
		D3DXVECTOR3 normal(PlaneTmp.a, PlaneTmp.b, PlaneTmp.c);

		if(	D3DXPlaneDotCoord(&PlaneTmp, pPosIn) > 0 &&
			D3DXVec3Dot(&normal, &negVec) > 0)
		{
			// �w�肵�������Ƌ��߂��ʂƂ̌�_�����߂�
			D3DXVECTOR3 linePoint1 = *pPosIn;
			D3DXVECTOR3 linePoint2 = *pPosIn + *pVecIn;
			D3DXVECTOR3 CrossPoint;

			if(D3DXPlaneIntersectLine(&CrossPoint, &PlaneTmp, &linePoint2, &linePoint1))
			//if(D3DXPlaneIntersectLine(&CrossPoint, &PlaneTmp, &(*pPosIn + *pVecIn), pPosIn))
			{
				// �ʂƂ̌�_���O�̒��_�̒��ɂ��邩�ǂ������ʂ���
				if(PointInPoly(&Vertex[0], &Vertex[1], &Vertex[2], &CrossPoint))
				{
					// �w�肵�����_�Ƌ��߂���_�Ƃ̋��������߁A��ԋ����̒Z���ʂ��̗p����
					D3DXVECTOR3 diff = CrossPoint - *pPosIn;
					fLengthTmp = D3DXVec3Length(&diff);
					if(fLengthTmp < fLengthMax){
						fLengthMax = fLengthTmp;
						PlaneMax = PlaneTmp;
						CrossPointMax = CrossPoint;
					}
				}
			}
		}
	}
	pVB->Unlock();
	pIB->Unlock();

	// ���_�o�b�t�@�������[�X
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);

	// �ʂ����������ꍇ�l���i�[����TRUE��Ԃ�
	if(fLengthMax < 99999){
		if(pCrossOut)	*pCrossOut = CrossPointMax;
		if(pPlaneOut)	*pPlaneOut = PlaneMax;
		*pfLengthOut = fLengthMax;
		return	true;
	}
	// ������Ȃ������ꍇFALSE��Ԃ�
	return false;
}

//------------------------------------------------------------------------------
//	Name:	SearchPlane2
//	Func:	�w��ʒu�A�w��x�N�g���ɂ��
//			���b�V���f�[�^�̒��̖ʂ������A�w��ʒu�Ƃ̍ŒZ����(�@���x�N�g��)�����߂�B
//			�����ɁA�w��x�N�g���ƖʂƂ̌�_���Ԃ��B
//			���̍ŒZ��������ԒZ���ʂ��̗p���A��_���W�l�A�ʂ̎��A�ʂƂ̍ŒZ������Ԃ��B
//
//	In:		CMeshObject*				pMeshIn		// �ΏۂƂȂ郁�b�V��
//			CONST	D3DXMATRIX*		pMatIn		// ���b�V���̃}�g���b�N�X
//			CONST	D3DXVECTOR3*	pPosIn		// �w��x�N�g�������W
//			CONST	D3DXVECTOR3*	pVecIn		// �w������x�N�g��
//			D3DXVECTOR3*			pCrossOut1	// �@���x�N�g���Ƃ̌�_���W�l���i�[���ĕԂ�
//			D3DXVECTOR3*			pCrossOut2	// �w��x�N�g���Ƃ̌�_���W�l���i�[���ĕԂ�
//			D3DXPLANE*				pPlaneOut	// ���ʂ̖ʂ̎����i�[���ĕԂ�
//			float*					pfLenOut	// �ʂ̌�_�Ƃ̋�����Ԃ�
//	Out:	bool								// �ʂ̎擾�ɐ���������TRUE
//------------------------------------------------------------------------------
bool SearchPlane2(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut1, D3DXVECTOR3* pCrossOut2, 
				 D3DXPLANE*	pPlaneOut, float* pfLenOut)
{
	typedef struct {
		D3DXVECTOR3 v;
		D3DCOLOR color;
	} VERTEX;

	LPDIRECT3DVERTEXBUFFER8	pVB;		// ���_�o�b�t�@�C���^�[�t�F�C�X
	LPDIRECT3DINDEXBUFFER8	pIB;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�C�X
	DWORD	dwNumFaces;					// �ʂ̐�

	// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�ւ̃A�N�Z�X�p
	WORD	*pIndices;
	VERTEX	*pVertices;

	// �o�b�t�@�̃C���^�[�t�F�C�X�擾
	pMeshIn->GetSysMemMesh()->GetVertexBuffer(&pVB);
	pMeshIn->GetSysMemMesh()->GetIndexBuffer(&pIB);
	// �ʂ̐����擾
	dwNumFaces = pMeshIn->GetLocalMesh()->GetNumFaces();

	// �|���S����T��
	D3DXVECTOR3	Vertex[3];

	D3DXVECTOR3	vecCross1;			// �ꎞ�I�ɕۑ������_���W�l
	D3DXVECTOR3 vecCross2;

	D3DXVECTOR3	vecCrossAdop1;		// �̗p�����_���W�l
	D3DXVECTOR3	vecCrossAdop2;

	D3DXVECTOR3	vecN;				// �@���x�N�g�����i�[����̂Ɏg�p

	D3DXPLANE	plaTmp;				// �̗p����ʂ̎�
	D3DXPLANE	plaAdop;

	float		fLenAdop=99999;		// �̗p����ʂƎw����W�Ƃ̋���
	float		fLen;
	DWORD		i;

	pVB->Lock(0,0,(BYTE**)&pVertices,0);
	pIB->Lock(0,0,(BYTE**)&pIndices,0);

	// �ʂ̐������J��Ԃ�
	for(i=0; i<dwNumFaces; i++)
	{
		// �C���f�b�N�X�o�b�t�@���A�|���S���̂R���_�����߂�
		Vertex[0] = pVertices[pIndices[i*3+0]*2].v;
		Vertex[1] = pVertices[pIndices[i*3+1]*2].v;
		Vertex[2] = pVertices[pIndices[i*3+2]*2].v;

		// ���_�����[���h�ϊ�(�H)
		D3DXVec3TransformCoord(&Vertex[0], &Vertex[0], pMatIn);
		D3DXVec3TransformCoord(&Vertex[1], &Vertex[1], pMatIn);
		D3DXVec3TransformCoord(&Vertex[2], &Vertex[2], pMatIn);

		// �O�̒��_����ʂ̎����Z�o����
		D3DXPlaneFromPoints(&plaTmp, &Vertex[0], &Vertex[1], &Vertex[2]);

		// ���ׂ����_�A�x�N�g���������ʂ̕\�ɂ��邩���ׂ�
		D3DXVECTOR3 normal(plaTmp.a, plaTmp.b, plaTmp.c);
		D3DXVECTOR3 negVec = (*pVecIn) * -1.0f;

		if (D3DXPlaneDotCoord(&plaTmp, pPosIn) > 0 &&
			D3DXVec3Dot(&normal, &negVec) > 0)
		{
			// �w�肵���ړ��x�N�g���ƖʂƂ̌�_�����߂�
			D3DXVECTOR3 linePoint1 = *pPosIn;
			D3DXVECTOR3 linePoint2 = *pPosIn + *pVecIn;
			D3DXVECTOR3 vecCross2;

			if(D3DXPlaneIntersectLine(&vecCross2, &plaTmp, &linePoint2, &linePoint1))
			{
				// ���������ʂ̋t�@���x�N�g�����擾����
				vecN.x = -plaTmp.a;
				vecN.y = -plaTmp.b;
				vecN.z = -plaTmp.c;

				// �w�肵���t�@���x�N�g���Ƃ��̖@���x�N�g�������ʂƂ̌�_�����߂�
				D3DXVECTOR3 linePoint1 = *pPosIn;
				D3DXVECTOR3 linePoint2 = *pPosIn + vecN;  // �ꎞ�I�u�W�F�N�g�ł͂Ȃ��ϐ��Ɋi�[
				D3DXVECTOR3 vecCross1;

				if(D3DXPlaneIntersectLine(&vecCross1, &plaTmp, &linePoint2, &linePoint1))
				{
					// �ʂƂ̌�_���O�̒��_�̒��ɂ��邩�ǂ������ʂ���
					if(PointInPoly(&Vertex[0], &Vertex[1], &Vertex[2], &vecCross1))
					{
						// ���߂��@���x�N�g���́A��ԋ����̒Z���ʂ��̗p����
						D3DXVECTOR3 diff = vecCross1 - *pPosIn;
						fLen = D3DXVec3Length(&diff);
						if(fLen < fLenAdop){
							fLenAdop = fLen;
							plaAdop = plaTmp;
							vecCrossAdop1 = vecCross1;
							vecCrossAdop2 = vecCross2;
						}
					}
				}
			}
		}
	}

	pVB->Unlock();
	pIB->Unlock();

	// ���_�o�b�t�@�������[�X
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);

	// �ʂ����������ꍇ�l���i�[����TRUE��Ԃ�
	if(fLenAdop < 99999){
		if(pCrossOut1)	*pCrossOut1 = vecCrossAdop1;
		if(pCrossOut2)	*pCrossOut2 = vecCrossAdop2;
		if(pPlaneOut)	*pPlaneOut = plaAdop;
		*pfLenOut = fLenAdop;
		return	true;
	}
	// ������Ȃ������ꍇFALSE��Ԃ�
	return false;
}


//------------------------------------------------------------------------------
//	Name:	PointInPoly
//	Func:	�w�肵���R�_�ō����O�p�`�̒��ɁA�R�p�`�ō����ʏ��
//			�w�肵�����W�����邩�ǂ����𔻕ʂ���
//
//	In:		CONST	D3DXVECTOR3*	pV1 = �w����W�P
//			CONST	D3DXVECTOR3*	pV2	= �w����W�Q
//			CONST	D3DXVECTOR3*	pV3	= �w����W�R
//			CONST	D3DXVECTOR3*	pVP	= �w��|�C���g	
//	Out:	bool	= �O�p�`�̒��Ƀ|�C���g����������TRUE
//------------------------------------------------------------------------------
bool PointInPoly(CONST D3DXVECTOR3* pV1, CONST D3DXVECTOR3* pV2,
				 CONST D3DXVECTOR3* pV3, CONST D3DXVECTOR3* pVP)
{
	D3DXVECTOR3 vec1, vec2;
	D3DXVECTOR3	vTmp1,vTmp2,vTmp3;		// �@���x�N�g��

	// �O�ςɂ��@���x�N�g�������߂�
	vec1 = *pV2 - *pV1;
	vec2 = *pVP - *pV1;
	D3DXVec3Cross(&vTmp1, &vec1, &vec2);

	vec1 = *pV3 - *pV2;
	vec2 = *pVP - *pV2;
	D3DXVec3Cross(&vTmp2, &vec1, &vec2);

	vec1 = *pV1 - *pV3;
	vec2 = *pVP - *pV3;
	D3DXVec3Cross(&vTmp3, &vec1, &vec2);


	// �@���x�N�g����P�ʃx�N�g���ɂ���
	D3DXVec3Normalize(&vTmp1, &vTmp1);
	D3DXVec3Normalize(&vTmp2, &vTmp2);
	D3DXVec3Normalize(&vTmp3, &vTmp3);

	// ���ׂĂ̖@���x�N�g�������s���ǂ����m�F
	// �����Ȍ덷�͖�������
	if(	fabs(vTmp1.x-vTmp2.x) < 0.005 &&
		fabs(vTmp1.y-vTmp2.y) < 0.005 &&
		fabs(vTmp1.z-vTmp2.z) < 0.005 &&

		fabs(vTmp1.x-vTmp3.x) < 0.005 &&
		fabs(vTmp1.y-vTmp3.y) < 0.005 &&
		fabs(vTmp1.z-vTmp3.z) < 0.005 )
		return true;

	// �ǂꂩ�ЂƂ̖@���x�N�g����0�Ȃ�A����ɓ_������Ƃ݂Ȃ����
	if(	vTmp1.x == 0 && vTmp1.y == 0 && vTmp1.z == 0 ||
		vTmp2.x == 0 && vTmp2.y == 0 && vTmp2.z == 0 ||
		vTmp3.x == 0 && vTmp3.y == 0 && vTmp3.z == 0)
		return true;

	return false;
}

//------------------------------------------------------------------------------
//	Name:	PlaneReflect
//	Func:	�ʂƂ̔��˃x�N�g�������߂�
//
//	In:		D3DXVECTOR3*			pOut		// ���˃x�N�g��
//			CONST	D3DXPLANE*		pPlaneIn	// �w���
//			CONST	D3DXVECTOR3*	pVecIn		// �w��x�N�g��
//	Out:	D3DXVECTOR3							// ���˃x�N�g��
//------------------------------------------------------------------------------
D3DXVECTOR3 PlaneReflect(D3DXVECTOR3* pOut, CONST D3DXPLANE* pPlaneIn, 
								CONST D3DXVECTOR3* pVecIn)
{

	D3DXVECTOR3 VecN, VecIn, VecOut;
	float fDot;

	// �ʂ̖@���x�N�g�������߂�
	VecN.x = pPlaneIn->a;
	VecN.y = pPlaneIn->b;
	VecN.z = pPlaneIn->c;

	// �w��x�N�g���̋t�����x�N�g���Z�o
	VecIn = *pVecIn * -1.0f;

	// �ʂ̖@���Ǝw��t�x�N�g���̓��ς��v�Z
	// ���̓��ό��ʂ��}�C�i�X�̏ꍇ��
	// �ʂ̗����ɓ������Ă��邱�ƂɂȂ�
	fDot = D3DXVec3Dot(&VecIn, &VecN);

	// �����˃x�N�g���̎Z�o
	VecOut = ( 2 * fDot * VecN ) - VecIn;

	if(pOut)	*pOut = VecOut;
	return VecOut;

}

//------------------------------------------------------------------------------
//	Name:	TransProject
//	Func:	�R�������W����v���W�F�N�V�����ɓ��e�����R�������W�𓾂�
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3D�f�o�C�X
//			D3DXVECTOR3*		pVec3Out	= ���e��̍��W
//			D3DXVECTOR3*		pVec3In		= ���e�O�̍��W
//	Out:	D3DXVECTOR3
//------------------------------------------------------------------------------
D3DXVECTOR3 TransProject(LPDIRECT3DDEVICE8 d3dDevice,
						 D3DXVECTOR3* pVec3Out, D3DXVECTOR3* pVec3In)
{
	D3DVIEWPORT8 Viewport;		// �r���[�|�[�g
	D3DXMATRIX   matView;		// �r���[�}�g���b�N�X
	D3DXMATRIX   matProjct;		// �v���W�F�N�V�����}�g���b�N�X

	/* �v���W�F�N�V�����̐ݒ� */
	d3dDevice->GetViewport ( &Viewport );
	d3dDevice->GetTransform( D3DTS_VIEW, &matView );
	d3dDevice->GetTransform( D3DTS_PROJECTION, &matProjct );

	/* ���[���h���W��ݒ� */
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	/* �v���W�F�N�V�������e���� */
	D3DXVec3Project(
	  pVec3Out,
	  pVec3In,
	  &Viewport,
	  &matProjct,
	  &matView,
	  &matWorld
	);

	return *pVec3Out;
}