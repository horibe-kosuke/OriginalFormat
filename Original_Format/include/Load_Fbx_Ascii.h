#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

class Load_Fbx_Ascii
{	
	//FBX情報	(モデル数、マテリアル数)
	std::vector<int> m_Num;

	//Mesh総数
	int m_NumMesh;

	//マテリアル総数
	int m_NumMaterial;
	
	//頂点情報
	std::vector<float>	m_Vertices;

	//インデックス情報
	std::vector<int>	m_Indices;

	//法線情報
	std::vector<float>	m_Normal;

	//マテリアル情報
	std::vector<float>	m_Material;
	std::vector<int>	m_IndexMaterial;

	//UV情報
	std::vector<float>	m_UV;
	std::vector<int>	m_UVIndex;


	//オリジナルフォーマット
	std::vector<float>	m_OriginalVertices;
	std::vector<int>	m_OriginalIndices;
	std::vector<float>	m_OriginalNormal;
	std::vector<float>	m_OriginalMaterial;
	std::vector<float>	m_OriginalUV;


	//! @brief Model,Material 総数取得
	void LoadInfo();


	//! @brief 頂点
	void LoadVertex();

	//! @brief インデックス
	void LoadIndex();

	//! @brief 法線
	void LoadNormal();

	//! @brief マテリアル
	void LoadMaterial();

	//! @brief UV
	void LoadUV();

	//! @brief マテリアルインデックス
	void LoadMaterialIndex();

	void LoadBone();

	//! @brief オリジナルフォーマットを作る
	void CreateOriginalFormat();

	//! @brief オリジナルフォーマットにFBXの情報を書き出し
	void WriteOriginalFormat();

public:
	
	//FBX開く用
	static FILE* fp;
	
	//FBXファイル名
	static const char* FileOpen;

	//ファイル行記録(ファイルで検索できなかった時に使う)
	static int FileLine;

	//書き込み用
	FILE* WriteFile;

	Load_Fbx_Ascii(const char* FileName,const char* FileSave);
	~Load_Fbx_Ascii();
	
	

};

