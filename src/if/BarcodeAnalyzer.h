#pragma once

#include <iostream>
#include "../helpper/Bitmap.h"

using namespace std;

/**
 * バーコードの種類
 */
enum class eBarcodeType {
	CODE_39 = 0//!< CODE_39
	,CODE_128  //!< CODE_128
	,CODE_JAN  //!< CODE_JAN
	,CODE_ITF  //!< CODE_ITF
};

/**
 * バーコードの解析するクラス
 */
class BarcodeAnalyzer {
public:
	/**
	 * コンストラクタ
	 * @param (format)　バーコードのフォーマット
	 */
	BarcodeAnalyzer(eBarcodeType);

	/**
	 * ディストラクタ
	 */
	~BarcodeAnalyzer();


public:
	/**
	 * デコーディングする <br>
	 * 引数の画像からバーコードデータをデコードする。
	 * @param (image)　対象イメージ
	 * @return デコーディング時のバーコードの値
	 */
	string Decode(Bitmap);

	/**
	 * エンコーディングする <br>
	 * 引数の文字列をバーコードデータにエンコードする。
	 * @param (data)　??
	 * @return エンコーディングされたイメージ
	 */
	Bitmap& Encode(string);

private:
	/**
	 * バーコードのフォーマット
	 */
	eBarcodeType _BarcodeFormat;
};
