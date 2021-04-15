#include "WriteHelpper.h"
#include "../exception/FailToSaveFileException.h"

using namespace std;

/**
 * ファイルを保存 <br>
 * 引数のpathに、引数のdataで静止画を出力する。
 * @param path 保存先
 * @param data 保存するイメージ
 * @return 出力成功か失敗か
 */
bool WriteHelpper::SaveImage(string path, Bitmap data) {

	static int a = 2;
	if (a-- == 0)
	{
		throw FailToSaveFileException("これ以上、イメージ保存不可！！！");
	}

	cout << "success to save image..." << endl;
	cout << "path : " << path << endl;
	return true;
}
