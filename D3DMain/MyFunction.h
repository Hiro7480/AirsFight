// =================================
//	File:	MyFunction.h
//	Func:	����ėp�֐�
//  Date:	2002/01/04
//	Author:	���� ���V
// =================================

#ifndef MYFUNCTION_H
#define MYFUNCTION_H

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "MeshData.h"

//------------------------------
//	�v���g�^�C�v�錾
//------------------------------

//------------------------------------------
//	Name:	GetAngle
//	Func:	��̒����̒l����A���̊p�x�����߂�
//------------------------------------------
double		GetAngle(CONST double dwY, CONST double dwX);

//------------------------------------------
//	Name:	SetVec3Length
//	Func:	�x�N�g����C�ӂ̒����ɕԂ�
//------------------------------------------
D3DXVECTOR3	SetVec3Length(D3DXVECTOR3* pOut, CONST D3DXVECTOR3*	pIn, float fLength);

//------------------------------------------
//	Name:	GetVec3Inverce
//	Func:	�x�N�g�����t�ɂ��ĕԂ�(��)
//------------------------------------------
D3DXVECTOR3 GetVec3Inverce(D3DXVECTOR3* pOut, CONST D3DXVECTOR3* pIn);

//------------------------------------------
//	Name:	GetNormalVec3ToMat
//	Func:	�}�g���b�N�X����
//			�P�ʕ����x�N�g�������߂�
//------------------------------------------
D3DXVECTOR3 GetNormalVec3ToMat(D3DXVECTOR3* pVecOut, CONST D3DXMATRIX* pMatIn);

//------------------------------------------
//	Name:	GetMatrixToVec
//	Func:	�ʒu�x�N�g���A�����x�N�g������
//			�}�g���N�X�����߂�
//------------------------------------------
D3DXMATRIX	GetMatrixToVec(D3DXMATRIX* pMatOut, CONST D3DXVECTOR3* pVecPos, CONST D3DXVECTOR3* pVecDir);

//------------------------------------------
//	Name:	MatUpdate
//	Func:	�}�g���N�X����]�l�̂ݍX�V
//------------------------------------------
D3DXMATRIX	MatUpdate(const D3DXMATRIX* pMatBase, const D3DXMATRIX* pMatRot);

//------------------------------------------------------------------
//	Name:	GetLengthEX
//	Func:	�x�N�g���̎w�肵���������̒�����Ԃ�
//			(���Ƃ��΂x���𖳂����Ăw�C�y�������̒����𓾂鎞�Ɏg�p)
//------------------------------------------------------------------
float		GetLengthEX(const D3DXVECTOR3* pVecIn, bool XEnable, bool YEnable, bool ZEnable);

//------------------------------------------
//	Name:	D3DXUntiRagian
//	Func:	���W�A�����p�x�ɕϊ����ĕԂ�
//------------------------------------------
float		D3DXUntiRagian(float ragian);

//------------------------------------------------------------------------------
//	Name:	SearchPlane
//	Func:	�w��ʒu�A�w��x�N�g���ɂ��
//			���b�V���f�[�^�̒��̈�ԋ߂��ʂƁA���̋��������߂�
//------------------------------------------------------------------------------
bool SearchPlane(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut, D3DXPLANE*	pPlaneOut, float* pfLengthOut);

//------------------------------------------------------------------------------
//	Name:	SearchPlane2
//	Func:	�w��ʒu�A�w��x�N�g���ɂ�胁�b�V���f�[�^�̒��̖ʂ������A
//			�w��ʒu�Ƃ̍ŒZ����(�@���x�N�g��)�����߂�B
//			�����ɁA�w��x�N�g���ƖʂƂ̌�_���Ԃ��B
//			���̍ŒZ��������ԒZ���ʂ��̗p���A��_���W�l�A�ʂ̎��A�ʂƂ̍ŒZ������Ԃ��B
//------------------------------------------------------------------------------
bool SearchPlane2(CMeshObject* pMeshIn, CONST D3DXMATRIX* pMatIn,
				 CONST D3DXVECTOR3* pPosIn, CONST D3DXVECTOR3* pVecIn,
				 D3DXVECTOR3* pCrossOut1, D3DXVECTOR3* pCrossOut2, 
				 D3DXPLANE*	pPlaneOut, float* pfLenOut);

//------------------------------------------------------------------------------
//	Name:	PointInPoly
//	Func:	�w�肵���R�_�ō����O�p�`�̒��ɁA�R�p�`�ō����ʏ��
//			�w�肵�����W�����邩�ǂ����𔻕ʂ���
//------------------------------------------------------------------------------
bool PointInPoly(CONST D3DXVECTOR3* pV1, CONST D3DXVECTOR3* pV2,
				 CONST D3DXVECTOR3* pV3, CONST D3DXVECTOR3* pVP);

//------------------------------------------------------------------------------
//	Name:	PlaneReflect
//	Func:	�ʂƂ̔��˃x�N�g�������߂�
//------------------------------------------------------------------------------
D3DXVECTOR3 PlaneReflect(D3DXVECTOR3* pOut, CONST D3DXPLANE* pPlaneIn, 
						 CONST D3DXVECTOR3* pVecIn);
//------------------------------------------------------------------------------
//	Name:	TransProject
//	Func:	�R�������W����v���W�F�N�V�����ɓ��e�����R�������W�𓾂�
//------------------------------------------------------------------------------
D3DXVECTOR3 TransProject(LPDIRECT3DDEVICE8 d3dDevice,
						 D3DXVECTOR3* pVec3Out, D3DXVECTOR3* pVec3In);


#endif