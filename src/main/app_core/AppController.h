#pragma once

#include "../../template/SingleTonTemplate.h"
#include <memory>
#include <string>
#include "../../template/AppTemplate.h"
#include "AppFactory.h"

using namespace std;

/**
 * アプリの決定、実行を担当するクラス
 */
class AppController : SingleTonTemplate<AppController> {

private:
	friend class SingleTonTemplate<AppController>;
	AppController();

public:
	/**
	 * メンバを初期化する関数 <br>
	 * 呼出元は、SingleTonの内部
	 */
	void Initialization() override;

public:
	/**
	 * アプリを入力する関数
	 * @param 入力値
	 * @return 入力されたアプリID
	 */
	APP_ID InputApp(string);

	/**
	 * 次のアプリを判断する関数
	 * @param 入力されたアプリID
	 * @return 判断済みのアプリID
	 */
	APP_ID JudgmentApp(APP_ID);

	/**
	 * 現在のアプリを実行する関数
	 * @param 現在のアプリID
	 * @param 入力値
	 */
	void ExecuteApp(APP_ID, string);

	/**
	 * このクラスの実際の動作関数
	 */
	void Controll();

private:
	/**
	 * 現在のアプリ <br>
	 * 初期値：NoneApplication
	 */
	weak_ptr<AppTemplate> curApp;

	/**
	 * 入力されたアプリID <br>
	 * 初期値：COMMAND_NONE
	 */
	APP_ID curAppId;

	/**
	 * 直ぐ前のアプリID <br>
	 * 初期値：COMMAND_NONE
	 */
	APP_ID prevAppId;
};

//　このクラスのタイプの再定義
using stAppController = SingleTonTemplate<AppController>;
