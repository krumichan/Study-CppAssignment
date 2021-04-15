#include "AppCamera.h"
#include "../../utility/LoggerUtility.h"
#include "../../exception/FailToGetImageException.h"

/**
 * 写真を取得している状態。
 */
volatile bool AppCamera::isGetting = false;

/**
 * コンストラクタ
 * @param _option カメラオプション
 */
AppCamera::AppCamera(CameraOption _option)
{
	this->owner = false;
	this->cameraDevice = make_unique<CameraDevice>(_option);
}

/**
 * 写真を撮る
 * @param image 写真
 */
bool AppCamera::Start()
{
	//　ロックの状態なので、
	//　取得処理をしない。
	if (isGetting)
	{
		stLoggerUtility::Call().PrintDialog("カメラデバイスが使われています。");
		stLoggerUtility::Call().Warn("カメラデバイスが使われています。");
		return false;
	}

	//　ロックをかける
	lock_guard<mutex> lock(m_bitmap);

	//　ロックフラグを取る
	isGetting = true;

	//　利用者をかける
	this->owner = true;

	//　イメージ取得開始
	unique_ptr<Bitmap> image = make_unique<Bitmap>();
	try
	{
		//　カメラデバイスからイメージ取得
		if (this->cameraDevice->GetImage(*image))
		{
			//　取得成功時、イメージを格納する
			this->curBitmap = move(image);
			stLoggerUtility::Call().Debug("写真を取得しました。");

			return true;
		}
		else
		{
			//　取得失敗したら、例外を投げる
			throw runtime_error("写真取得に失敗しました！！");
		}
	}
	catch (exception& e)
	{
		string message = "fail to get image \n" + string(e.what());
		this->cameraDevice->Dispose();
		throw FailToGetImageException(message);
	}

	return false;
}

/**
 * 処理を終了
 */
void AppCamera::End()
{
	//　ロックを解除する
	lock_guard<mutex> unlock(m_bitmap);

	//　ロックフラグを回収する
	isGetting = false;

	//　利用者を解除する
	this->owner = false;

	//　使用済みのイメージを廃棄する
	this->curBitmap.reset();

	// ログを出力
	stLoggerUtility::Call().Debug("カメラデバイスを解除します。");
}

/**
 * 取っているイメージを取得
 * @return 取っているイメージ
 */
Bitmap* AppCamera::GetImage()
{
	//　イメージが存在し、デバイスを使っている状態の場合。
	if (isGetting && owner)
	{
		return this->curBitmap.get();
	}
	return nullptr;
}

/**
 * カメラデバイスを廃棄する。
 */
void AppCamera::Dispose()
{
	this->owner = false;
	this->curBitmap.reset();
	this->cameraDevice->Dispose();
}
