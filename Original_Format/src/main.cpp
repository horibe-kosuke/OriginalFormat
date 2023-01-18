#include "Load_Fbx_Ascii.h"

//---------------------------------------------------------------
// Blender (OpenGL) 座標		- DirectX 座標					-
//								-								-
// 		  Y 1					- 		  Y -1					-
//								-								-
//	X -1		X 1				-	X-1			X 1			    -
//								-							    -
// 		  Y -1					-		  Y  1				    -
//---------------------------------------------------------------


int main() {
	//char FileName[256] = "Box_ASC";	//ファイル名
	//char FileName[256] = "Box_Material_ASC";	//ファイル名
	//char FileName[256] = "Box_Anim_ASC";	//ファイル名
	//char FileName[256] = "Cone_ASC";	//ファイル名
	char FileName[256] = "SkinMesh_Easy_ASC";

	char FileOpen[256];
	char FileSave[256];


	const char FolderOpen[256] = "3dModel\\";
	const char FolderSave[256] = "OriginalFormat\\";

	sprintf(FileOpen, "%s%s%s", FolderOpen, FileName, ".fbx");//読み込み
	sprintf(FileSave, "%s%s%s", FolderSave, FileName, ".txt");//書き込み


	//FILE* test;
	//test = fopen(FileOpen, "r");
	//char str[256];
	//while (fgets(str, 256, test) != NULL) {
	//	if (strstr(str, "PoseNode")) {
	//		fgets(str, 256, test);
	//		if (strstr(str, "Bone")) {
	//			fgets(str, 256, test);
	//			printf("%s", str);
	//			printf("\n");
	//		}
	//	}
	//}



	Load_Fbx_Ascii* LoadFBX=new Load_Fbx_Ascii(FileOpen,FileSave);	delete LoadFBX;

	return 0;

}