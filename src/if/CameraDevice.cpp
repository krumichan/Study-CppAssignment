#include "../if/CameraDevice.h"
#include "../exception/FailToGetImageException.h"

/**
 * コンストラクタ
 * @param (option)　カメラオプション
 */
CameraDevice::CameraDevice(CameraOption& option) {
	_Option = option;
}

/**
 * デストラクタ
 */
CameraDevice::~CameraDevice() {

}

/**
 * イメージを取得 <br>
 * privateプロパティ[option]の内容に従い、
 * 呼び出し時のカメラ画像(静止画)を
 * Bitmapクラスで取得
 * @param (result)　取得済みのイメージ
 * @return 取得成功か失敗か
 */
bool CameraDevice::GetImage(Bitmap& result) {

	static int count = 3;
	if (count-- < 1) {
		throw FailToGetImageException("これ以上のイメージは取得できません！！！");
	}

	result.width = _Option.ImageWidth;
	result.height = _Option.ImageHeight;

	cout << "success to get image..." << endl;
	cout << "width : " << result.width << " // " << "height : " << result.height << endl;

	return true;
}

/**
 *　リソースの破棄
 */
void CameraDevice::Dispose() {

}
