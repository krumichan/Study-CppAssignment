#pragma once

#include "../../template/SingleTonTemplate.h"
#include <memory>
#include <map>
#include "../../template/AppTemplate.h"

using namespace std;

/**
 * アプリID
 */
enum class APP_ID {
	APP_NONE  	//!< APP_NONE　何のしない
	,APP_CAMERA	//!< APP_CAMERA　カメラ機能
	,APP_BARCODE//!< APP_BARCODE　バーコード機能
};

/**
 * 全てのアプリを管理するクラス <br>
 * マップでアプリを保持する
 */
class AppFactory : public SingleTonTemplate<AppFactory> {

	friend class SingleTonTemplate<AppFactory>;

private:
	/**
	 * インスタンスの生成を防止
	 */
	AppFactory() { Initialization(); }

public:
	/**
	 * メンバを初期化する関数
	 */
	void Initialization() override;

	/**
	 * 任意のアプリ取得
	 * @param アプリ名
	 * @return アプリ
	 */
	weak_ptr<AppTemplate> GetApp(APP_ID);

private:
	/**
	 * アプリマップ
	 */
	map<APP_ID, shared_ptr<AppTemplate>> apps;
};

//　このクラスのタイプの再定義
using stAppFactory = SingleTonTemplate<AppFactory>;
