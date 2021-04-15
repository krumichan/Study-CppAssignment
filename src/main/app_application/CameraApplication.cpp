#include "CameraApplication.h"
#include "../../utility/FileUtility.h"
#include "../../utility/PathUtility.h"
#include "../../utility/LoggerUtility.h"
#include "../../exception/FailToGetImageException.h"
#include "../../exception/InvalidPathException.h"
#include "../../exception/FailToSaveFileException.h"
#include <iostream>
#include <sstream>

/**
 * コンストラクタ
 */
CameraApplication::CameraApplication()
{
	this->input = "";
	this->savePath = PathUtility::CommonSeparatePath("C:\\devOld\\workspace");
	this->curState = CAM_STATE::STATE_NONE;

	CameraOption _option{ 1280, 720 };
	this->camera = make_unique<AppCamera>(_option);
	this->writeHelpper = make_unique<WriteHelpper>();
}

/**
 * デストラクタ
 */
CameraApplication::~CameraApplication()
{
	//　何もしない
}

/**
 * アプリを実行する関数
 */
void CameraApplication::Execute(string input)
{
	//　次のステート
	CAM_STATE nextState;

	//　入力値保存
	this->input = input;

	//　今回の動作実行及び次のステート取得
	switch (curState) {

		//　現在のステートがNONEの場合
		case CAM_STATE::STATE_NONE:
		{
			//　NONEの動作実行
			nextState = NoneState();
			break;
		}

		//　現在のステートがSTARTの場合
		case CAM_STATE::STATE_START:
		{
			try
			{
				//　STARTの動作実行
				nextState = StartState();
			}
			catch (exception& e)
			{
				this->camera->Dispose();
				throw e;
			}
			break;
		}

		//　現在のステートがEndの場合
		case CAM_STATE::STATE_END:
		{
			try
			{
				//　Endの動作実行
				nextState = EndState();
			}
			catch (exception& e)
			{
				this->camera->Dispose();
				throw e;
			}
			break;
		}
	}

	//　現在のステートを更新
	this->curState = nextState;

	//　入力値削除
	this->input = "";
}

/**
 * フォーカス取得
 */
void CameraApplication::FocusHere()
{
	//　何もしない
}

/**
 * フォーカスロスト
 */
void CameraApplication::LostHere()
{
	//　何もしない
}

/**
 * None状態の動作
 * @return 次のステート
 */
CAM_STATE CameraApplication::NoneState()
{
	stLoggerUtility::Call().Trace("[CAMERA] execute NoneState()");

	//　シャッターが押下されたら、開始
	if (!input.compare("shutter"))
	{
		return CAM_STATE::STATE_START;
	}

	return CAM_STATE::STATE_NONE;
}

/**
 * Start状態の動作
 * @return 次のステート
 */
CAM_STATE CameraApplication::StartState()
{
	stLoggerUtility::Call().Trace("[CAMERA] execute StartState()");

	try
	{
		//　イメージを取得
		if(!this->camera->Start())
		{
			throw runtime_error("他のアプリからカメラデバイスを使っています！！");
		}

		stLoggerUtility::Call().Info("[CAMERA] カメラディバイスから写真を取得しました。");
	}
	catch (exception& e)
	{
		stringstream stream;
		stream << "[CAMERA] カメラディバイスから写真を取得に失敗しました。" << "\n" << "fail reason : " << string(e.what());
		stLoggerUtility::Call().Fatal(stream.str());
		throw FailToGetImageException("写真の取得に失敗しました。");
	}

	//　開始動作が終わったら、終了動作に入る。
	return CAM_STATE::STATE_END;
}

/**
 * End状態の動作
 * @return 次のステート
 */
CAM_STATE CameraApplication::EndState()
{
	stLoggerUtility::Call().Trace("[CAMERA] execute EndState()");

	try
	{
		//　デバイスの権限を持っているか？
		if (this->camera->GetImage() != nullptr)
		{
			throw runtime_error("他のアプリからカメラデバイスを使っています！！");
		}

		//　保存先が存在しているか
		//　保存先がディレクトリなのか
		if (FileUtility::IsValid(this->savePath) &&
			FileUtility::IsDirectory(this->savePath))
		{
			//　イメージを保存
			this->writeHelpper->SaveImage(this->savePath, *(this->camera->GetImage()));

			stringstream stream;
			stream << "[CAMERA] 写真を保存しました" << "\n" << "filepath : " << this->savePath;
			stLoggerUtility::Call().Info(stream.str());
		}
	}
	catch (exception& e)
	{
		stringstream stream;
		stream << "[CAMERA] 写真の保存に失敗しました。" << "\n" << "fail reason : " << string(e.what());
		stLoggerUtility::Call().Fatal(stream.str());
		throw FailToSaveFileException("写真の保存に失敗しました。");
	}

	//　終了動作が終わったら、待機動作に入る。
	return CAM_STATE::STATE_NONE;
}

/**
 * ファイル保存先を登録する
 * @param _path 保存先パス
 * @return 保存先パス登録に成功したのかどうか
 */
bool CameraApplication::SetSavePath(string _path)
{
	//　有効なパスなのか
	if (!FileUtility::IsValid(_path))
	{
		throw InvalidPathException("パスが不正です。");
		return false;
	}

	//　パスがディレクトリのパスなのか
	if (!FileUtility::IsDirectory(_path))
	{
		throw InvalidPathException("パスが不正です。");
		return false;
	}

	this->savePath = _path;
	return true;
}
