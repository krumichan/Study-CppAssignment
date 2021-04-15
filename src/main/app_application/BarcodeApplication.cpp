#include "BarcodeApplication.h"
#include "../../utility/LoggerUtility.h"
#include "../../exception/FailToGetImageException.h"
#include "../../exception/FailToDecodeException.h"
#include <iostream>
#include <sstream>

/**
 * コンストラクタ
 */
BarcodeApplication::BarcodeApplication()
{
	this->input = "";
	this->curState = BRC_STATE::STATE_NONE;

	CameraOption _option { 640, 320 };
	eBarcodeType barType = eBarcodeType::CODE_128;

	this->camera = make_unique<AppCamera>(_option);
	this->barcodeAnalyzer = make_unique<BarcodeAnalyzer>(barType);
}

/**
 * デストラクタ
 */
BarcodeApplication::~BarcodeApplication()
{

}

/**
 * アプリを実行する関数
 */
void BarcodeApplication::Execute(string input)
{
	//　次のステート
	BRC_STATE nextState;

	//　入力値保存
	this->input = input;

	//　今回の動作実行及び次のステート取得
	switch (curState) {

		//　現在のステートがNONEの場合
		case BRC_STATE::STATE_NONE:
		{
			//　NONEの動作実行
			nextState = NoneState();
			break;
		}

		//　現在のステートがSTARTの場合
		case BRC_STATE::STATE_START:
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
		case BRC_STATE::STATE_END:
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
void BarcodeApplication::FocusHere()
{
	//　何もしない
}

/**
 * フォーカスロスト
 */
void BarcodeApplication::LostHere()
{
	//　何もしない
}

/**
 * None状態の動作
 * @return 次のステート
 */
BRC_STATE BarcodeApplication::NoneState()
{
	stLoggerUtility::Call().Trace("[BARCODE] execute NoneState()");

	//　シャッターが押下されたら、開始
	if (!input.compare("shutter"))
	{
		return BRC_STATE::STATE_START;
	}

	// TODO: NONE機能具現必要
	return BRC_STATE::STATE_NONE;
}

/**
 * Start状態の動作
 * @return 次のステート
 */
BRC_STATE BarcodeApplication::StartState()
{
	stLoggerUtility::Call().Trace("[BARCODE] execute StartState()");

	try
	{
		//　イメージを取得
		if(!this->camera->Start())
		{
			throw runtime_error("他のアプリからカメラデバイスを使っています！！");
		}

		stLoggerUtility::Call().Info("[BARCODE] カメラディバイスから写真を取得しました。");
	}
	catch (exception& e)
	{
		stringstream stream;
		stream << "[BARCODE] カメラディバイスから写真を取得に失敗しました。" << "\n" << "fail reason : " << string(e.what());
		stLoggerUtility::Call().Fatal(stream.str());
		throw FailToGetImageException("写真の取得に失敗しました。");
	}

	return BRC_STATE::STATE_END;
}

/**
 * End状態の動作
 * @return 次のステート
 */
BRC_STATE BarcodeApplication::EndState()
{
	stLoggerUtility::Call().Trace("[BARCODE] execute EndState()");

	try
	{
		//　デバイスの権限を持っているか？
		if (this->camera->GetImage() != nullptr)
		{
			throw runtime_error("他のアプリからカメラデバイスを使っています！！");
		}

		string barcode = this->barcodeAnalyzer->Decode(*(this->camera->GetImage()));
		cout << "barcode : " << barcode << endl;
	}
	catch (exception& e)
	{
		stringstream stream;
		stream << "[BARCODE] バーコードを出力に失敗しました。" << "\n" << "fail reason : " << string(e.what());
		stLoggerUtility::Call().Fatal(stream.str());
		throw FailToDecodeException("バーコードを出力に失敗しました。");
	}

	stLoggerUtility::Call().Info("バーコードを出力しました。");

	return BRC_STATE::STATE_NONE;
}
