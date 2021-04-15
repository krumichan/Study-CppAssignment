#include "AppInput.h"
#include "AppController.h"
#include "AppFactory.h"
#include <Windows.h>

#include <iostream>
using namespace std;

/**
 * コンストラクタ
 */
AppController::AppController()
{
	Initialization();

	curApp = stAppFactory::Call().GetApp(APP_ID::APP_NONE);

	curAppId = APP_ID::APP_NONE;

	prevAppId = APP_ID::APP_NONE;
}

/**
 * メンバを初期化する関数 <br>
 * 呼出元は、SingleTonの内部
 */
void AppController::Initialization() {
	/**
	 * 現在のアプリ <br>
	 * 初期値：NoneCommand
	 */
	AppController::curApp = AppFactory::Call().GetApp(APP_ID::APP_NONE);

	/**
	 * 入力されたアプリID <br>
	 * 初期値：COMMAND_NONE
	 */
	AppController::curAppId = APP_ID::APP_NONE;

	/**
	 * 直ぐ前のアプリID <br>
	 * 初期値：COMMAND_NONE
	 */
	AppController::prevAppId = APP_ID::APP_NONE;
}

/**
 * アプリを入力する関数
 * @return 入力されたアプリID
 */
APP_ID AppController::InputApp(string input) {

	//　現在値を入れる。
	//　入力がない場合、現在の状態を維持する為。
	APP_ID get = curAppId;

	if (!input.compare("barcode"))
	{
		get = APP_ID::APP_BARCODE;
	} else
	if (!input.compare("camera"))
	{
		get = APP_ID::APP_CAMERA;
	} else
	if (!input.compare("lobby"))
	{
		get = APP_ID::APP_NONE;
	}

	return get;
}

/**
 * 次のアプリを判断する関数
 * @param 入力されたアプリID
 * @return 判断済みのアプリID
 */
APP_ID AppController::JudgmentApp(APP_ID inpId) {

	switch (prevAppId) {
	case APP_ID::APP_BARCODE: {
		switch (inpId) {
		case APP_ID::APP_BARCODE:
			break;

		case APP_ID::APP_CAMERA:
			inpId = APP_ID::APP_BARCODE;
			break;

		case APP_ID::APP_NONE:
			inpId = APP_ID::APP_NONE;
			break;
		}
		break;
	}

	case APP_ID::APP_NONE:
		switch (inpId) {
		case APP_ID::APP_BARCODE:
			inpId = APP_ID::APP_BARCODE;
			break;

		case APP_ID::APP_CAMERA:
			inpId = APP_ID::APP_CAMERA;
			break;

		case APP_ID::APP_NONE:
			break;
		}
		break;

	case APP_ID::APP_CAMERA:
		switch (inpId) {
		case APP_ID::APP_BARCODE:
			inpId = APP_ID::APP_CAMERA;
			break;

		case APP_ID::APP_CAMERA:
			break;

		case APP_ID::APP_NONE:
			inpId = APP_ID::APP_NONE;
			break;
		}
		break;
	}

	return inpId;
}

/**
 * 現在のアプリを実行する関数
 * @param 現在のアプリ
 */
void AppController::ExecuteApp(APP_ID curAppId, string input)
{
	//　現在のコマンドを取得
	shared_ptr<AppTemplate> spCurApp = curApp.lock();

	//　実行対象コマンドが変更された場合
	if (curAppId != this->prevAppId) {
		//　今、実行中のコマンドのロスト処理を行う
		spCurApp->LostHere();

		//　入力コマンドIDのコマンド取得
		weak_ptr<AppTemplate> wpInpApp = stAppFactory::Call().GetApp(curAppId);

		//　weak_ptrからshared_ptr取得
		shared_ptr<AppTemplate> shInpApp = wpInpApp.lock();

		//　フォーカス取得処理を行う
		shInpApp->FocusHere();

		//　現在のコマンドを更新
		curApp = shInpApp;

	//　実行対象コマンドが以前と同じ場合
	} else {
		try
		{
			//　現在のコマンドの処理を行う
			spCurApp->Execute(input);
		}
		catch (exception& e)
		{
			throw e;
		}
	}
}

/**
 * このクラスの実際の動作関数
 */
void AppController::Controll()
{
	//　入力マネージャーから入力を取得
	string input = stAppInput::Call().GetInput();

	//　入力値の取得
	APP_ID inpId = InputApp(input);

	//　入力の有効を検査及び有効なコマンドID取得
	curAppId = JudgmentApp(inpId);

	try
	{
		//　今回のコマンドを実行
		ExecuteApp(curAppId, input);
	}
	catch (exception& e)
	{
		throw e;
	}

	//　実行済みのコマンドIDを以前実行コマンドIDに入れる
	this->prevAppId = curAppId;
}
