#pragma once

#include "../app_core/AppCamera.h"
#include "../../if/BarcodeAnalyzer.h"
#include <memory>
#include "../../template/AppTemplate.h"

/**
 * バーコードアプリを起動している状態のコマンドクラス <br>
 * 内部的に、ステートパターンを従っている。
 */
class BarcodeApplication : public AppTemplate {
private:
	/**
	 * バーコード機能のステート
	 */
	enum class STATE { STATE_NONE, STATE_START, STATE_END };

public:
	/**
	 * コンストラクタ
	 */
	BarcodeApplication();

	/**
	 * デストラクタ
	 */
	~BarcodeApplication();


public:
	//　ステート列挙型の再定義
	//　外で、また再定義
	using Barcode_State = BarcodeApplication::STATE;


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
	 * バーコード分析器
	 */
	unique_ptr<BarcodeAnalyzer> barcodeAnalyzer;
};

//　使いやすく、再定義
using BRC_STATE = BarcodeApplication::Barcode_State;
