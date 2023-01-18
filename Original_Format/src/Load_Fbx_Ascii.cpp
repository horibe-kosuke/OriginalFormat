#include "Load_Fbx_Ascii.h"

const char* Load_Fbx_Ascii::FileOpen;
FILE* Load_Fbx_Ascii::fp;
int Load_Fbx_Ascii::FileLine = -1;
namespace {
	template<class T>
	void SearchMesh(const char* SearchStr, std::vector<T>& vec) {
		char str[256] = { NULL };		//�t�@�C���̕�����
		char fstr[256] = { NULL };		//�t�@�C���̕����񂩂琔���������
		float number = 0;				//�t�@�C�����̐���
		int FileLineCount = 0;			//�t�@�C���s�J�E���g
		int count = 0;					//fstr�̔z��p


		//��������v����܂Ńt�@�C�������s���Ƃ�
		while (strstr(str, SearchStr) == NULL) {
			memset(str, 0, sizeof(str));
			fgets(str, 256, Load_Fbx_Ascii::fp);

			if (feof(Load_Fbx_Ascii::fp)) {
				fclose(Load_Fbx_Ascii::fp);
				fopen_s(&Load_Fbx_Ascii::fp, Load_Fbx_Ascii::FileOpen, "r");
				for (int i = 0; i < Load_Fbx_Ascii::FileLine; i++) {
					fgets(str, 256, Load_Fbx_Ascii::fp);
				}
				return;
			}

			FileLineCount++;
		}

		//�t�@�C���s���L�^
		Load_Fbx_Ascii::FileLine += FileLineCount;


		//�����������o��
		while (true) {
			int i = 0;
			for (i = 0; str[i] != NULL; i++) {
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-') {
					fstr[count] = str[i];
					count++;
				}
				else if (str[i] == ',' && str[i + 1] == '\n') {

				}
				else if (str[i] == ',' || str[i] == '\n') {
					count = 0;
					if (fstr[count] == NULL) {
						continue;
					}
					number = atof(fstr);
					memset(fstr, 0, sizeof(fstr));
					vec.push_back((T)number);
				}

			}


			//�R�������������瑱����
			if (str[(i - 2)] != ',') {
				return;
			}
			else {
				//������
				memset(str, 0, sizeof(str));
				fgets(str, 256, Load_Fbx_Ascii::fp);
			}
		}
	}

}



Load_Fbx_Ascii::Load_Fbx_Ascii(const char* FileOpen, const char* FileSave)
	: m_NumMesh(0)
	, m_NumMaterial(0)
	, WriteFile(NULL)
{
	Load_Fbx_Ascii::FileOpen = FileOpen;
	fp = fopen(FileOpen, "rb");

	if (fp == NULL) {
		printf("�t�@�C�����J���܂���ł���");
		return;
	}
	LoadInfo();

	for (int i = 0; i < m_NumMesh; i++) {
		LoadVertex();
		LoadIndex();
		LoadNormal();
		LoadUV();
	}


	LoadMaterialIndex();


	for (int i = 0; i < m_NumMaterial; i++) {
		LoadMaterial();
	}




	LoadUV();
	CreateOriginalFormat();

	WriteFile = fopen(FileSave, "w");
	if (WriteFile == NULL) {
		printf("�t�@�C����������ERROR\n");
		return;
	}



	WriteOriginalFormat();
	fclose(WriteFile);


	fclose(fp);
}

Load_Fbx_Ascii::~Load_Fbx_Ascii()
{

}

void Load_Fbx_Ascii::LoadInfo()
{
	//���J�E���g
	SearchMesh("Count", m_Num);
	//Mesh�J�E���g
	SearchMesh("Count", m_Num);
	//�W�I���g���J�E���g
	SearchMesh("Count", m_Num);
	//�}�e���A���J�E���g
	SearchMesh("Count", m_Num);
	//Defomer�J�E���g
	//SearchMesh("Count", m_Num);


	m_NumMesh = m_Num.at(2);
	m_NumMaterial = m_Num.at(3);

	printf("\n");
}

void Load_Fbx_Ascii::LoadVertex()
{
	SearchMesh("Vertices:", m_Vertices);
	for (int i = 0; i < m_Vertices.size(); i += 3) {
		printf("%f,%f,%f", m_Vertices[i], m_Vertices[(UINT64)i + 1], m_Vertices[(UINT64)i + 2]);
		printf("\n");
	}


}

void Load_Fbx_Ascii::LoadIndex()
{
	SearchMesh("PolygonVertexIndex", m_Indices);
	int NumIndices = m_Indices.size();

	for (int i = 0; i < NumIndices; i += 3) {
		printf("%d,%d,%d", m_Indices[i], m_Indices[(UINT64)i + 1], m_Indices[(UINT64)i + 2]);
		printf("\n");
	}

	//�O�p�|���S�����l�p�|���S�����m���߂�COUNT
	int count = 0;
	int PolygonCount = 1;
	for (int i = 0; i < NumIndices; i++) {
		count++;
		if (m_Indices[i] < 0) {
			m_Indices[i] = (m_Indices[i] * -1) - 1;
			printf("PolygonCount:%d		���_��:%d\n", PolygonCount++, count);
			count = 0;
		}
	}


	printf("�č\�z\n");
	for (int i = 0; i < NumIndices; i += 3) {
		printf("%d,%d,%d", m_Indices[i], m_Indices[(UINT64)i + 1], m_Indices[(UINT64)i + 2]);
		printf("\n");
	}
}

void Load_Fbx_Ascii::LoadNormal()
{
	SearchMesh("Normals", m_Normal);

	for (int i = 0; i < m_Normal.size(); i += 3) {
		printf("%f,%f,%f", m_Normal[i], m_Normal[i + 1], m_Normal[i + 2]);
		printf("\n");
	}
}

void Load_Fbx_Ascii::LoadMaterial()
{
	SearchMesh("\"Ambient\"", m_Material);
	SearchMesh("\"Diffuse\"", m_Material);
	SearchMesh("\"Specular\"", m_Material);

	for (int i = 0; i < m_Material.size(); i += 3) {
		printf("%f,%f,%f", m_Material[i], m_Material[(UINT64)i + 1], m_Material[(UINT64)i + 2]);
		printf("\n");
	}
}

void Load_Fbx_Ascii::LoadUV()
{
	SearchMesh("\t\tUV", m_UV);
	SearchMesh("UVIndex", m_UVIndex);
}


void Load_Fbx_Ascii::LoadMaterialIndex()
{
	SearchMesh("Materials", m_IndexMaterial);

	if (m_IndexMaterial.size() == 1) {
		//�|���S�����ƂɃ}�e���A���C���f�b�N�X�����邩��	���C���f�b�N�X��3
		for (int i = 1; i < m_Indices.size() / 3; i++) {
			m_IndexMaterial.push_back(0);
		}
	}
}


void Load_Fbx_Ascii::CreateOriginalFormat()
{
	//�����C���f�b�N�X�ԍ����ǂꂾ�����邩
	int IndexNumber[256][256] = { 0 };
	//������
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			IndexNumber[i][j] = -1;
		}
	}

	int NumIndex = m_Indices.size();
	//�C���f�b�N�X��ԍ����ɂ���
	for (int i = 0; i < NumIndex; i++) {
		int count = 0;
		for (int j = 0; j < NumIndex; j++) {
			if (m_Indices[j] == i) {
				IndexNumber[i][count] = j;
				count++;
			}
		}
	}


	//�C���f�b�N�X�ԍ����Œ��_��ǉ�
	for (int Number = 0; Number < NumIndex; Number++) {
		for (int j = 0;; j++) {
			if (IndexNumber[Number][j] == -1) {
				break;
			}

			//���_
			m_OriginalVertices.push_back(m_Vertices.at(Number * 3 + 0));
			m_OriginalVertices.push_back(m_Vertices.at(Number * 3 + 1));
			m_OriginalVertices.push_back(m_Vertices.at(Number * 3 + 2));

			//�@��
			m_OriginalNormal.push_back(m_Normal.at(IndexNumber[Number][j] * 3 + 0));
			m_OriginalNormal.push_back(m_Normal.at(IndexNumber[Number][j] * 3 + 1));
			m_OriginalNormal.push_back(m_Normal.at(IndexNumber[Number][j] * 3 + 2));

			//UV
			if (m_UV.size() > 0) {
				m_OriginalUV.push_back(m_UV.at(m_UVIndex.at(IndexNumber[Number][j]) * 2));
				m_OriginalUV.push_back(m_UV.at(m_UVIndex.at(IndexNumber[Number][j]) * 2 + 1));
			}
		}
	}

	int IndexCount = 0;

	//�C���f�b�N�X�ԍ��̍ő吔
	int MaxValue = *std::max_element(m_Indices.begin(), m_Indices.end());


	m_OriginalIndices.resize(m_Indices.size());
	//�C���f�b�N�X���č\�z
	for (int Number = 0; Number < (MaxValue + 1); Number++) {
		for (int j = 0; j < m_Indices.size(); j++) {
			if (m_Indices.at(j) == Number) {
				m_OriginalIndices.at(j) = IndexCount;
				IndexCount++;
			}
		}
	}
}

void Load_Fbx_Ascii::WriteOriginalFormat()
{


	printf("\n");
	printf("\n");
	printf("\n");
	for (int i = 0; i < m_OriginalNormal.size(); i += 3) {
		printf("%f,%f,%f", m_OriginalNormal.at(i), m_OriginalNormal.at(i + 1), m_OriginalNormal.at(i + 2));
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	for (int i = 0; i < m_OriginalUV.size(); i += 2) {
		printf("%f,%f", m_OriginalUV.at(i), m_OriginalUV.at(i + 1));
		printf("\n");
	}

	

	//�O�p�|���S���̍��v��
	int NumTriangle = m_OriginalVertices.size() / 3;
	fprintf(WriteFile, "%d", NumTriangle);
	fprintf(WriteFile, "\n");

	//���_�A�@���AUV
	for (int Vertex = 0, UVcount = 0; Vertex < m_OriginalVertices.size(); Vertex += 3, UVcount += 2) {

		fprintf(WriteFile, "%f,%f,%f", m_OriginalVertices.at(Vertex), m_OriginalVertices.at(Vertex + 1), m_OriginalVertices.at(Vertex + 2));
		fprintf(WriteFile, ",");


		fprintf(WriteFile, "%f,%f,%f", m_OriginalNormal.at(Vertex), m_OriginalNormal.at(Vertex + 1), m_OriginalNormal.at(Vertex + 2));

		if (m_OriginalUV.size() > 0) {
			fprintf(WriteFile, ",");
			fprintf(WriteFile, "%f,%f", m_OriginalUV.at(UVcount), m_OriginalUV.at(UVcount + 1));
		}
		fprintf(WriteFile, "\n");
	}




	//�}�e���A������
	int NumMaterial = m_Material.size() / 9;
	fprintf(WriteFile, "\n");
	fprintf(WriteFile, "%d\n", NumMaterial);

	//�}�e���A���T�C�Y�@(Ambient + Diffuse + Specular)���ƃ}�e���A���T�C�Y9
	int MaterialSize = m_Material.size() / NumMaterial;
	for (int MaterialCount = 0; MaterialCount < NumMaterial; MaterialCount++) {
		//�}�e���A��
		for (int Index = 0; Index < MaterialSize; Index++) {
			fprintf(WriteFile, "%f", m_Material.at((MaterialCount * MaterialSize) + Index));
			if (Index % 3 == 2) {
				fprintf(WriteFile, "\n");
			}
			else {
				fprintf(WriteFile, ",");
			}
		}

		//�C���f�b�N�X
		fprintf(WriteFile, "\n");

		//�C���f�b�N�X�̑���
		int NumIndex = 0;
		for (int Num = 0; Num < m_IndexMaterial.size(); Num++) {
			if (m_IndexMaterial.at(Num) == MaterialCount) {
				NumIndex += 3;
			}
		}
		fprintf(WriteFile, "%d\n", NumIndex);

		//�}�e���A���ԍ����ƂɃC���f�b�N�X�����
		for (int i = 0, j = 0; i < m_OriginalIndices.size(); i += 3, j++) {
			if (m_IndexMaterial.at(j) == MaterialCount) {
				fprintf(WriteFile, "%d,%d,%d", m_OriginalIndices.at(i), m_OriginalIndices.at(i + 1), m_OriginalIndices.at(i + 2));
				fprintf(WriteFile, "\n");
			}
		}
		fprintf(WriteFile, "\n");
	}



}
