//==========================================================
// MotionData.h
// Auther : 桜井 博之
// Data   : 2002/04/16
//==========================================================

#if !defined(AFX_MOTIONDATA_H__8E2130F7_0AFD_4E37_A6C7_7EBB78D78964__INCLUDED_)
#define AFX_MOTIONDATA_H__8E2130F7_0AFD_4E37_A6C7_7EBB78D78964__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	インクルード
//----------------------
#include "CompatiDX8.h"
#include <d3d8.h>
#include <d3dx8.h>
#include <tchar.h>
#include <rmxfguid.h>

//------------------------------
//		定数定義
//------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_DELETES
#define SAFE_DELETES(p)			{ if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

//----------------------------------------------
//	Name:	tagRotateKey
//	Func:	回転キー構造体
//----------------------------------------------
typedef	struct{
	int				nTime;
	int				nFloats;
	D3DXQUATERNION	quatRot;	
} tagRotateKey;

//----------------------------------------------
//	Name:	tagPositionKey
//	Func:	位置キー構造体
//----------------------------------------------
typedef	struct{
	int			nTime;
	int			nFloats;
	D3DXVECTOR3	vecPos;
} tagPositionKey;

//--------------------------------------------------------------
//	Name	: CMotionFrame
//	Func	: ひとつのフレームに対するアニメーション
//--------------------------------------------------------------
class CMotionFrame  
{
friend class CMotionData;
friend class CActiveFrame;
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3Dデバイス

	CMotionFrame*		m_pNext;		// 次のデータへのポインタ
	TCHAR				m_strName[512];	// フレーム名

	int					m_nRotKeyNum;	// 回転キー配列の最大数
	tagRotateKey*		m_pRotKey;		// 回転キー配列の先頭アドレス
	int					m_nPosKeyNum;	// 位置キー配列の最大数
	tagPositionKey*		m_pPosKey;		// 位置キー配列の先頭アドレス

public:
	HRESULT	CreateKey(LPDIRECTXFILEDATA pFileData);	// アニメーションキーの作成
	HRESULT	Destroy();								// 全てのデータの削除

	/* アクセス関数 */
	CMotionFrame*	GetNext();					// 次のデータへのポインタを取得
	TCHAR*			GetName();					// 名前の取得
	void			SetName(TCHAR* strName);	// 名前のセット

	CMotionFrame(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMotionFrame();

};

//----------------------------------------------
//	Name:	GetNext
//	Func:	次のデータへのポインタを取得
//	in:		なし
//	Out:	CMotionFrame* = 次のデータへのポインタ
//----------------------------------------------
inline CMotionFrame* CMotionFrame::GetNext()
{
	return m_pNext;
}

//----------------------------------------------
//	Name:	GetName
//	Func:	名前の取得
//	in:		なし
//	Out:	TCHAR* = 名前
//----------------------------------------------
inline TCHAR* CMotionFrame::GetName()
{
	return m_strName;
}

//----------------------------------------------
//	Name:	GetName
//	Func:	名前の取得
//	in:		TCHAR* strName = 指定名
//	Out:	なし
//----------------------------------------------
inline void CMotionFrame::SetName(TCHAR* strName)
{
	//strcpy(m_strName,strName);
	_tcscpy_s(m_strName, _countof(m_strName), strName);
}

//--------------------------------------------------------------
//	Name	: CMotionData
//	Func	: アニメーションデータをリスト構造で管理するクラス
//--------------------------------------------------------------
class CMotionData  
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3Dデバイス

	CMotionFrame*		m_pListTop;		// リスト構造の最初にあるデータ
	TCHAR				m_strName[512];	// アニメーションの名前
	int					m_nMaxFrame;	// アニメーションの最大フレーム時間
	int					m_nFrameNum;	// リスト構造のフレーム数

public:
	HRESULT	Create(TCHAR* strFilename);						// ファイルからリスト構造を作成
	CMotionFrame* CreateFrame(LPDIRECTXFILEDATA pFileData,	// Createから呼ばれる
						CMotionFrame* pCurrentFrame);

	HRESULT			ComputMaxFrame();			// 最大フレーム時間を求める
	HRESULT			Destroy();					// 全オブジェクトの削除

	/* アクセス関数 */
	int				GetFrameNum();				// フレーム数を返す
	CMotionFrame*	GetListTop();				// リストの最初にあるデータを返す
	int				GetMaxFrame();				// 最大フレーム時間を返す

	CMotionData(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMotionData();

};

//----------------------------------------------
//	Name:	GetFrameNum
//	Func:	フレーム数を返す
//	in:		なし
//	Out:	int = フレーム数
//----------------------------------------------
inline int CMotionData::GetFrameNum()
{
	return m_nFrameNum;
}

//----------------------------------------------
//	Name:	GetListTop
//	Func:	リスト構造の最初のデータを返す
//	in:		なし
//	Out:	CMotionFrame* = リストの初めのデータ
//----------------------------------------------
inline CMotionFrame* CMotionData::GetListTop()
{
	return m_pListTop;
}

//----------------------------------------------
//	Name:	GetListTop
//	Func:	最大フレーム時間を返す
//	in:		なし
//	Out:	int = 最大フレーム時間
//----------------------------------------------
inline int CMotionData::GetMaxFrame()
{
	return m_nMaxFrame;
}

#endif // !defined(AFX_MOTIONDATA_H__8E2130F7_0AFD_4E37_A6C7_7EBB78D78964__INCLUDED_)
