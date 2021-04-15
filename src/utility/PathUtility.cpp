#include "PathUtility.h"

/**
 * パスのセパレートを変換し、戻す
 * @param パス
 * @return 変換済みパス
 */
string PathUtility::CommonSeparatePath(string path)
{
	//　パスがある場合
	if (!path.empty())
	{
		//　探し始めるパス
		size_t pos = 0;

		//　探すセパレート
		string findSeparate = "/";

		string commonSeparate = COMMON_SEPARATE + "";

		//　探すセパレートの位置を取得
		while ((pos = path.find(findSeparate, pos)) != string::npos)
		{
			//　セパレートを変換
			path.replace(pos, commonSeparate.length(), commonSeparate);
		}
	}

	return path;
}

/**
 * 親パスを取得
 * @param 現在パス
 * @return ルートパス
 */
string PathUtility::GetParentPath(string path)
{
	//　セパレート修正
	path = CommonSeparatePath(path);

	//　最後のキャラがセパレートの場合。
	if (path.back() == COMMON_SEPARATE)
	{
		//　最後のセパレートを消す。
		path = path.substr(0, path.length() - 1);
	}

	//　パスにセパレートがない場合。
	//　そのままリターン
	short check = path.find(COMMON_SEPARATE);
	if (check == -1)
	{
		return path;
	}

	//　後ろからセパレートのポジションを取得
	short rSepPos = path.rfind(COMMON_SEPARATE);

	//　親パスを取得
	string parent = path.substr(0, rSepPos);

	return parent;
}
