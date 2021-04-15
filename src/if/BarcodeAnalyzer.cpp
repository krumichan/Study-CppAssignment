#include "BarcodeAnalyzer.h"
#include "../exception/FailToDecodeException.h"
#include <sstream>

/**
 * コンストラクタ
 * @param (format)　バーコードのフォーマット
 */
BarcodeAnalyzer::BarcodeAnalyzer(eBarcodeType format) {
	this->_BarcodeFormat = format;
}

/**
 * ディストラクタ
 */
BarcodeAnalyzer::~BarcodeAnalyzer() {

}

/**
 * デコーディングする <br>
 * 引数の画像からバーコードデータをデコードする。
 * @param (image)　対象イメージ
 * @return デコーディング時のバーコードの値
 */
string BarcodeAnalyzer::Decode(Bitmap image) {
	static int count = 0;

	if (++count > 2) {
		throw FailToDecodeException("これ以上、デコーディング不可！！！");
	}

	stringstream ss;
	ss << " - decode count : " << count << endl;
	ss << "   width : " << image.width << " // height : " << image.height << endl;
	string result = ss.str();

	return result;
}

/**
 * エンコーディングする <br>
 * 引数の文字列をバーコードデータにエンコードする。
 * @param (data)　??
 * @return エンコーディングされたイメージ
 */
Bitmap& Encode(string data) {
	Bitmap b;
	return b;
}
