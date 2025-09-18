//==========================================================
// MeshData.h
// Auther : 桜井 博之
// Data   : 2002/04/17
//==========================================================

#if !defined(AFX_MESHMANAGE_H__CB3368AD_E699_4815_BB1F_E754620B133B__INCLUDED_)
#define AFX_MESHMANAGE_H__CB3368AD_E699_4815_BB1F_E754620B133B__INCLUDED_

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
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }
#endif
//----------------------------------------------------------
//	Name	: CMeshObject
//	Func	: ひとつのＸメッシュを管理するクラス
//----------------------------------------------------------
class CMeshObject  
{
public:
	LPDIRECT3DDEVICE8	m_pd3dDevice;		// D3Dデバイス

	TCHAR				m_strName[512];		// メッシュの名前
	LPD3DXMESH          m_pSysMemMesh;		// システムメモリに取得するメッシュ
	LPD3DXMESH          m_pLocalMesh;		// 実際使用するメッシュ
	float				m_fLength;			// バウンディングスフィアの半径
    
	DWORD				m_dwNumMaterials;	// メッシュの中のマテリアルの数
	D3DMATERIAL8*		m_pMaterials;		// マテリアルの先頭アドレス
	LPDIRECT3DTEXTURE8*	m_pTextures;		// テクスチャの先頭アドレス

public:

	HRESULT Render(BOOL bNoAlpha=TRUE, BOOL bAlpha=TRUE);	// 描画関数

	HRESULT Create( TCHAR* strFilename );					// ファイルからの作成
	HRESULT Create( LPDIRECTXFILEDATA pFileData );			// 階層構造時の作成
	HRESULT	ComputLength();									// バウンディングスフィアの半径の算出
	HRESULT Destroy();										// オブジェクトの削除
	HRESULT	RestoreDeviceObjects();							// オブジェクトの修理
	HRESULT InvalidateDeviceObjects();						// ＶＲＡＭを破棄する

	/* アクセス関数 */
	LPD3DXMESH	GetSysMemMesh();				// システムメッシュの取得
	LPD3DXMESH	GetLocalMesh();					// ローカルメッシュの取得
	float		GetLength();					// バウンディングスフィアの半径の取得

	/* オプション関数 */
	HRESULT	SetFVF(DWORD dwFVF);				// 頂点フォーマットの設定

	CMeshObject(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMeshObject();

};

//----------------------------------------------
//	Name:	GetSysMemMesh
//	Func:	システムメッシュの取得
//	in:		なし
//	Out:	LPD3DXMESH = メッシュデータ
//----------------------------------------------
inline LPD3DXMESH CMeshObject::GetSysMemMesh()
{
	return m_pSysMemMesh;
}

//----------------------------------------------
//	Name:	GetSysMemMesh
//	Func:	ローカルメッシュの取得
//	in:		なし
//	Out:	LPD3DXMESH = メッシュデータ
//----------------------------------------------
inline LPD3DXMESH CMeshObject::GetLocalMesh()
{
	return m_pLocalMesh;
}

//----------------------------------------------
//	Name:	GetLength
//	Func:	バウンディングスフィアの半径の取得
//	in:		なし
//	Out:	float = 半径の長さ
//----------------------------------------------
inline float CMeshObject::GetLength()
{
	return m_fLength;
}

//----------------------------------------------------------
//	Name	: CMeshFrame
//	Func	: メッシュの階層構造等を持つクラス
//----------------------------------------------------------
class CMeshFrame
{
friend class CMeshData;

private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;		// D3Dデバイス

	TCHAR				m_strName[512];		// フレームの名前
	int					m_nNumber;			// 階層構造での順番番号
	D3DXMATRIX			m_matBase;			// マトリクス
	CMeshObject*		m_pMesh;			// メッシュオブジェクト

	CMeshFrame*			m_pNext;			// 同階層メッシュ
	CMeshFrame*			m_pChild;			// 子供メッシュ

public:
	/* 通常描画 */
	HRESULT Render( BOOL bNoAlpha=TRUE,BOOL bAlpha=TRUE );
	/* モーション補正値を含めた描画 */
	HRESULT Render( D3DXMATRIX matMotion[], BOOL bNoAlpha=TRUE,BOOL bAlpha=TRUE );

	HRESULT Destroy();							// オブジェクトの削除
	HRESULT	RestoreDeviceObjects();				// オブジェクトの修理
	HRESULT InvalidateDeviceObjects();			// オブジェクトの初期化

	/* アクセス関数 */
	void		SetMatrix(D3DXMATRIX matTmp);	// マトリクスのセット
	void		SetName(TCHAR* strName);		// 名前のセット
	void		SetNumber(int nNum);			// 番号のセット

	TCHAR*		GetName();						// 名前の取得
	D3DXMATRIX	GetMatrix();					// マトリクスの取得
	CMeshFrame*	GetFrame(int nFrame);			// 指定番号のフレームを返す
	int			GetNumber();					// 番号の取得

	CMeshFrame(LPDIRECT3DDEVICE8 m_pd3dDevice);
	virtual ~CMeshFrame();
};

//----------------------------------------------
//	Name:	SetMatrix
//	Func:	マトリクスのセット
//	in:		D3DXMATRIX matTmp = 指定マトリクス
//	Out:	なし
//----------------------------------------------
inline void CMeshFrame::SetMatrix(D3DXMATRIX matTmp)
{
	m_matBase = matTmp;
}

//----------------------------------------------
//	Name:	SetName
//	Func:	名前のセット
//	in:		TCHAR* strName = 指定名
//	Out:	なし
//----------------------------------------------
inline void CMeshFrame::SetName(TCHAR* strName)
{
	//strcpy(m_strName,strName);
	_tcscpy_s(m_strName, _countof(m_strName), strName);
}

//----------------------------------------------
//	Name:	SetNumber
//	Func:	番号のセット
//	in:		int nNum = 指定番号
//	Out:	なし
//----------------------------------------------
inline void CMeshFrame::SetNumber(int nNum)
{
	m_nNumber = nNum;
}

//----------------------------------------------
//	Name:	GetName
//	Func:	名前の取得
//	in:		なし
//	Out:	TCHAR* = 名前
//----------------------------------------------
inline TCHAR* CMeshFrame::GetName()
{
	return m_strName;
}

//----------------------------------------------
//	Name:	GetMatrix
//	Func:	マトリクスの取得
//	in:		なし
//	Out:	D3DXMATRIX = マトリクス
//----------------------------------------------
inline D3DXMATRIX CMeshFrame::GetMatrix()
{
	return m_matBase;
}

//----------------------------------------------
//	Name:	GetFrame
//	Func:	マトリクスの取得
//	in:		int = nFrame	= 指定フレーム番号
//	Out:	CMeshFrame		= メッシュフレーム
//----------------------------------------------
inline CMeshFrame* CMeshFrame::GetFrame(int nFrame)
{
	CMeshFrame* pFrame;

	/* 自分のフレームの番号が同じならそのまま返す */
	if(nFrame == m_nNumber)
		return this;

	/* 子供を調べていく */
	if(m_pChild)
		if(NULL != (pFrame = m_pChild->GetFrame(nFrame)))
			return pFrame;

	/* 次を調べていく */
	if(m_pNext)
		if(NULL != (pFrame = m_pNext->GetFrame(nFrame)))
			return pFrame;

	/* 見つからなかったときはNULLを返す */
	return NULL;
}
//----------------------------------------------
//	Name:	GetNumber
//	Func:	番号の取得
//	in:		なし
//	Out:	int = フレーム番号
//----------------------------------------------
inline int CMeshFrame::GetNumber()
{
	return m_nNumber;
}

//----------------------------------------------------------
//	Name	: CMeshData
//	Func	: 階層構造をもつメッシュを管理するクラス
//----------------------------------------------------------
class CMeshData
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;	// D3Dデバイス

	CMeshFrame*			m_pListTop;		// 階層構造の一番最初にあるデータ
	TCHAR				m_strName[512];	// Ｘファイルの名前
	int					m_nFrameNum;	// 階層構造のフレーム数

public:
	HRESULT	Render();									// 通常の描画
	HRESULT	Render(D3DXMATRIX matMotion[]);				// モーション補正値を含めた描画

	HRESULT	Create(TCHAR* strFilename);					// 階層メッシュをファイルから作成
	HRESULT	CreateTree(	LPDIRECTXFILEDATA pFileData,	// 階層メッシュを作るときに再帰的に使用
						CMeshFrame* pParentFrame);
	HRESULT Destroy();									// 全オブジェクトの削除
	HRESULT	RestoreDeviceObjects();						// 全オブジェクトの修理
	HRESULT InvalidateDeviceObjects();					// 全オブジェクトのＶＲＡＭ破棄

	/* アクセス関数 */
	int			GetFrameNum();							// データの数の取得
	CMeshFrame*	GetFrame(int nFrame);					// 指定フレームの取得

	CMeshData(LPDIRECT3DDEVICE8 pd3dDevice);
	virtual ~CMeshData();

};

//----------------------------------------------
//	Name:	GetFrameNum
//	Func:	データ数の取得
//	in:		なし
//	Out:	int = データ数
//----------------------------------------------
inline int CMeshData::GetFrameNum()
{
	return m_nFrameNum;
}

//----------------------------------------------
//	Name:	GetFrame
//	Func:	指定フレームの取得
//	in:		int nFrame	= 指定フレーム番号
//	Out:	CMeshFrame*	= メッシュフレーム 
//----------------------------------------------
inline CMeshFrame* CMeshData::GetFrame(int nFrame)
{
	return m_pListTop->GetFrame(nFrame);
}

#endif // !defined(AFX_MESHMANAGE_H__CB3368AD_E699_4815_BB1F_E754620B133B__INCLUDED_)
