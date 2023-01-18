#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

class Load_Fbx_Ascii
{	
	//FBX���	(���f�����A�}�e���A����)
	std::vector<int> m_Num;

	//Mesh����
	int m_NumMesh;

	//�}�e���A������
	int m_NumMaterial;
	
	//���_���
	std::vector<float>	m_Vertices;

	//�C���f�b�N�X���
	std::vector<int>	m_Indices;

	//�@�����
	std::vector<float>	m_Normal;

	//�}�e���A�����
	std::vector<float>	m_Material;
	std::vector<int>	m_IndexMaterial;

	//UV���
	std::vector<float>	m_UV;
	std::vector<int>	m_UVIndex;


	//�I���W�i���t�H�[�}�b�g
	std::vector<float>	m_OriginalVertices;
	std::vector<int>	m_OriginalIndices;
	std::vector<float>	m_OriginalNormal;
	std::vector<float>	m_OriginalMaterial;
	std::vector<float>	m_OriginalUV;


	//! @brief Model,Material �����擾
	void LoadInfo();


	//! @brief ���_
	void LoadVertex();

	//! @brief �C���f�b�N�X
	void LoadIndex();

	//! @brief �@��
	void LoadNormal();

	//! @brief �}�e���A��
	void LoadMaterial();

	//! @brief UV
	void LoadUV();

	//! @brief �}�e���A���C���f�b�N�X
	void LoadMaterialIndex();

	void LoadBone();

	//! @brief �I���W�i���t�H�[�}�b�g�����
	void CreateOriginalFormat();

	//! @brief �I���W�i���t�H�[�}�b�g��FBX�̏��������o��
	void WriteOriginalFormat();

public:
	
	//FBX�J���p
	static FILE* fp;
	
	//FBX�t�@�C����
	static const char* FileOpen;

	//�t�@�C���s�L�^(�t�@�C���Ō����ł��Ȃ��������Ɏg��)
	static int FileLine;

	//�������ݗp
	FILE* WriteFile;

	Load_Fbx_Ascii(const char* FileName,const char* FileSave);
	~Load_Fbx_Ascii();
	
	

};

