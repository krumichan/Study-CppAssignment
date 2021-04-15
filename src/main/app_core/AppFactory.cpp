#include "../app_application/BarcodeApplication.h"
#include "../app_application/CameraApplication.h"
#include "../app_application/NoneApplication.h"
#include "AppFactory.h"

/**
 * メンバを初期化する関数 <br>
 * 呼出元は、SingleTonの内部
 */
void AppFactory::Initialization() {

	//　アプリ挿入
	//　共有が可能なポインターを作成
	apps[APP_ID::APP_BARCODE] = make_unique<BarcodeApplication>();
	apps[APP_ID::APP_CAMERA] = make_unique<CameraApplication>();
	apps[APP_ID::APP_NONE] = make_unique<NoneApplication>();
}

/**
 * 任意のアプリ取得 <br>
 * .use_count()を使って、取得成功かどうかを、呼出元で確認してください。
 * @param appID アプリID
 * @return アプリ
 */
weak_ptr<AppTemplate> AppFactory::GetApp(APP_ID appID) {

	//　該当するコマンドを返す。
	//　無ければ、 .use_count()を使って、呼出元で確認してください。
	return apps[appID];
}
