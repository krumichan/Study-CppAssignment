#pragma once

#include "../../template/AppTemplate.h"

/**
 * 何のアプリも起動していない状態のコマンドクラス <br>
 * 内部的に、ステートパターンを従っている。
 */
class NoneApplication : public AppTemplate {
public:
	/**
	 * コンストラクタ
	 */
	NoneApplication();

	/**
	 * ディストラクタ
	 */
	~NoneApplication();


private:
	/**
	 * このクラス機能のステート
	 */
	enum class STATE { STATE_NONE };

	/**
	 * 現在のステート
	 */
	STATE curState;

	/**
	 * 入力値
	 */
	string input;

public:
	//　ステート列挙型の再定義
	//　外で、また再定義
	using None_State = NoneApplication::STATE;

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
};

//　使いやすく、再定義
using NON_STATE = NoneApplication::None_State;
