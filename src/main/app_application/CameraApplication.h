#pragma once

#include "../app_core/AppCamera.h"
#include "../../helpper/WriteHelpper.h"
#include <memory>
#include "../../template/AppTemplate.h"

/**
 * カメラアプリを起動している状態のコマンドクラス <br>
 * 内部的に、ステートパターンを従っている。
 */
class CameraApplication : public AppTemplate {
private:
	/**
	 * カメラ機能のステート
	 */
	enum class STATE { STATE_NONE, STATE_START, STATE_END };


public:
	/**
	 * コンストラクタ
	 */
	CameraApplication();
	/**
	 * デストラクタ
	 */
	~CameraApplication();


public:
	//　ステート列挙型の再定義
	//　外で、また再定義
	using Camera_State = CameraApplication::STATE;

public:
	/**
	 * アプリを実行する関数
	 * @param 入力値
	 */
	void Execute(string) override;

	/**
	 * フォーカス取得
	 */
	void FocusHere() override;

	/**
	 * フォーカスロスト
	 */
	void LostHere() override;


public:
	/**
	 * ファイル保存先を登録する
	 * @param 保存先パス
	 * @return 保存先パス登録に成功したのかどうか
	 */
	bool SetSavePath(string);



///　内部動作関数
private:
	/**
	 * None状態の動作
	 * @return 次のステート
	 */
	STATE NoneState();

	/**
	 * Start状態の動作
	 * @return 次のステート
	 */
	STATE StartState();

	/**
	 * End状態の動作
	 * @return 次のステート
	 */
	STATE EndState();


private:
	/**
	 * 現在のステート
	 */
	STATE curState;

	/**
	 * 入力値
	 */
	string input;

	/**
	 * カメラ
	 */
	unique_ptr<AppCamera> camera;

	/**
	 * イメージの保存先
	 */
	string savePath;

	/**
	 * ファイル保存ヘルパー
	 */
	unique_ptr<WriteHelpper> writeHelpper;
};

//　使いやすく、再定義
using CAM_STATE = CameraApplication::Camera_State;
