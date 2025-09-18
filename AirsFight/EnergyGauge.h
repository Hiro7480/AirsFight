//==========================================================
// EnergyGauge.h
// Auther : ���� ���V
// Data   : 2002/05/04
//==========================================================

#if !defined(AFX_ENERGYGAUGE_H__BA0EE9C3_70F3_4B94_ACDE_93759D70DE69__INCLUDED_)
#define AFX_ENERGYGAUGE_H__BA0EE9C3_70F3_4B94_ACDE_93759D70DE69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------
//	�C���N���[�h
//--------------------------
#include "Sprite.h"

//------------------------------------------
//	Name:	CEnergyGauge
//	Func:	�G�l���M�[�Q�[�W�̕`��
//------------------------------------------
class CEnergyGauge : public CSprite
{
private:
	int				m_nMaxEnergy;	// �ő�G�l���M�[�l
	int				m_nNowEnergy;	// ���݃G�l���M�[�l

	D3DXVECTOR2		m_vecPos;		// ��{�`��ʒu

public:
	void	FrameMove();	// ���t���[���̏���
	void	Render();		// �`�揈��	

	/* �A�N�Z�X�֐� */
	void SetMaxEnergy(int nMaxEnergy){m_nMaxEnergy = nMaxEnergy;};	// �ő�G�l���M�[�l�̃Z�b�g
	void SetNowEnergy(int nNowEnergy){m_nNowEnergy = nNowEnergy;};	// ���݃G�l���M�[�l�̃Z�b�g

	CEnergyGauge(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* srcFileName);
	virtual ~CEnergyGauge();

};

#endif // !defined(AFX_ENERGYGAUGE_H__BA0EE9C3_70F3_4B94_ACDE_93759D70DE69__INCLUDED_)
