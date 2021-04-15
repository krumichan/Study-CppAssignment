#pragma once

#include "../helpper/Bitmap.h"

/**
 * カメラのオプション
 */
struct CameraOption {
	/**
	 * 取得する画像の幅
	 */
	int ImageWidth;

	/**
	 * 取得する画像の高さ
	 */
	int ImageHeight;

};

using CameraOption = struct CameraOption;

/**
 * カメラディバイス
 */
class CameraDevice {
public:
	/**
	 * コンストラクタ
	 * @param (option)　カメラオプション
	 */
	CameraDevice(CameraOption&);

	/**
	 * デストラクタ
	 */
	~CameraDevice();


public:
	/**
	 * イメージを取得 <br>
	 * privateプロパティ[option]の内容に従い、
	 * 呼び出し時のカメラ画像(静止画)を
	 * Bitmapクラスで取得
	 * @param (result)　取得済みのイメージ
	 * @return 取得成功か失敗か
	 */
	bool GetImage(Bitmap&);

	/**
	 *　リソースの破棄
	 */
	void Dispose();

private:
	/**
	 * 取得する画像データの設定
	 */
	CameraOption _Option;
};
