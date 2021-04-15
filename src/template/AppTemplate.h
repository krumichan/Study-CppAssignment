#pragma once

#include <string>

using namespace std;

/**
 * コマンドテンプレートクラス
 */
class AppTemplate {
public:
	/**
	 * デストラクタ
	 */
	virtual ~AppTemplate();

public:
	/**
	 * コマンド実行
	 */
	virtual void Execute(string) = 0;

	/**
	 * フォーカス取得
	 */
	virtual void FocusHere() = 0;

	/**
	 * フォーカスロスト
	 */
	virtual void LostHere() = 0;
};

#include "AppTemplate.h"
