#pragma once

#include "../../if/CameraDevice.h"
#include <memory>
#include <mutex>

using namespace std;

/**
 * 実際のカメラデバイス
 */
class AppCamera
{
private:
	/**
	 * カメラが持っているイメージ
	 */
	static shared_ptr<Bitmap> curBitmap;

	/**
	 * スレッド排他制御の為の変数
	 */
	static mutex m_bitmap;

	/**
	 * カメラデバイス
	 */
	unique_ptr<CameraDevice> cameraDevice;

	/**
	 * 写真を取得している状態。
	 */
	static volatile bool isGetting;

	/**
	 * デバイスを使用している利用者なのか
	 */
	bool owner;

public:
	/**
	 * コンストラクタ
	 * @param _option カメラオプション
	 */
	AppCamera(CameraOption _option);


public:
	/**
	 * 写真を撮る
	 * @param image 写真
	 */
	bool Start();

	/**
	 * 処理を終了
	 */
	void End();

	/**
	 * カメラデバイスを廃棄する。
	 */
	void Dispose();


public:
	/**
	 * 取っているイメージを取得
	 * @return 取っているイメージ
	 */
	Bitmap* GetImage();

	/**
	 * デバイスを使用している利用者なのか
	 */
	bool isOwner();
};
