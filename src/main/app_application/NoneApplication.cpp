#include "NoneApplication.h"
#include <iostream>
#include "../../utility/LoggerUtility.h"

/**
 * コンストラクタ
 */
NoneApplication::NoneApplication()
{
	this->input = "";
	this->curState = NON_STATE::STATE_NONE;
}

/**
 * ディストラクタ
 */
NoneApplication::~NoneApplication()
{
	//　何もしない
}

/**
 * アプリを実行する関数
 */
void NoneApplication::Execute(string input)
{
	//　次のステート
	NON_STATE nextState;

	//　入力値保存
	this->input = input;

	//　今回の動作実行及び次のステート取得
	switch (this->curState) {

		//　現在のステートがNONEの場合
		case NON_STATE::STATE_NONE:
		{
			//　NONEの動作実行
			nextState = NoneState();
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
void NoneApplication::FocusHere()
{
	//　何もしない
}

/**
 * フォーカスロスト
 */
void NoneApplication::LostHere()
{
	//　何もしない
}

/**
 * None状態の動作
 * @return 次のステート
 */
NON_STATE NoneApplication::NoneState()
{
	stLoggerUtility::Call().Trace("[NONE] execute NoneState()");

	//　NONEたけの返す
	return NON_STATE::STATE_NONE;
}
