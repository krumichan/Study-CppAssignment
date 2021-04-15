/**
 * 練習問題用に用意。
 * 実際にはファイルはしゅつろy九されないが、
 * 本ヘルパークラスのメソッドの呼び出しで
 * ファイルが保存できるものとする。
 */

#pragma once

#include <iostream>
#include "Bitmap.h"

using namespace std;

/**
 * ファイルの出力を補助するクラス
 */
class WriteHelpper {

public:
	/**
	 * ファイルを保存 <br>
	 * 引数のpathに、引数のdataで静止画を出力する。
	 * @param (path) 保存先
	 * @param (data) 保存するイメージ
	 * @return 出力成功か失敗か
	 */
	bool SaveImage(string, Bitmap);
};
