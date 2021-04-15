#pragma once

#include <string>

#define COMMON_SEPARATE '\\'

using namespace std;

/**
 * パスユーティリティ
 */
class PathUtility
{
private:
	/**
	 * インスタンスの生成を防止
	 */
	PathUtility() { }

public:
	/**
	 * パスのセパレートを変換し、戻す
	 * @param パス
	 * @return 変換済みパス
	 */
	static string CommonSeparatePath(string);

	/**
	 * 親パスを取得
	 * @param 現在パス
	 * @return ルートパス
	 */
	static string GetParentPath(string);
};
