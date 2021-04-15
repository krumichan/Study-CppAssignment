#pragma once

#include <iostream>

using namespace std;

/**
 * ファイルユーティリティ
 */
class FileUtility {
private:
	/**
	 * インスタンスの生成を防止
	 */
	FileUtility() { }

public:
	/**
	 * このファイルは存在しているか。
	 * @param ファイル名
	 * @return 存在しているかどうか
	 */
	static bool IsValid(string);

	/**
	 * ディレクトリなのかどうか
	 * @param 現在パス
	 * @return 確認結果
	 */
	static bool IsDirectory(string);

	/**
	 * ファイルなのかどうか
	 * @param 現在パス
	 * @return 確認結果
	 */
	static bool IsFile(string);
};
