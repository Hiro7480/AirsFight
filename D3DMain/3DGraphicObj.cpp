//==========================================================
// 3DGraphicObj.cpp
// Auther : ���� ���V
// Data   : 2002/02/26
//==========================================================

#include "3DGraphicObj.h"

//----------------------------------------------
//	Name:	C3DGraphicObj
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------
C3DGraphicObj::C3DGraphicObj(LPDIRECT3DDEVICE8 d3dDevice)
{
	/* D3D�f�o�C�X�̃Z�b�g */
	m_pd3dDevice = d3dDevice;

	/* �}�g���N�X�l�̏����� */
	D3DXMatrixIdentity(&m_matBase);
	D3DXMatrixIdentity(&m_matStock);
}

//----------------------------------------------
//	Name:	~C3DGraphicObj
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
C3DGraphicObj::~C3DGraphicObj()
{

}
//----------------------------------------------
//	Name:	GetPosBase
//	Func:	�����p�}�g���N�X�̒l���x�N�g���ŕԂ�
//	in:		�Ȃ�
//	Out:	D3DXVECTOR3
//----------------------------------------------
D3DXVECTOR3 C3DGraphicObj::GetPosBase()
{
	D3DXVECTOR3	vecTmp;

	vecTmp.x = m_matBase._41;
	vecTmp.y = m_matBase._42;
	vecTmp.z = m_matBase._43;

	return vecTmp;
}

//----------------------------------------------
//	Name:	GetPosStock
//	Func:	�`��p�}�g���N�X�̒l���x�N�g���ŕԂ�
//	in:		�Ȃ�
//	Out:	D3DXVECTOR3
//----------------------------------------------
D3DXVECTOR3 C3DGraphicObj::GetPosStock()
{
	D3DXVECTOR3	vecTmp;

	vecTmp.x = m_matStock._41;
	vecTmp.y = m_matStock._42;
	vecTmp.z = m_matStock._43;

	return vecTmp;
}
