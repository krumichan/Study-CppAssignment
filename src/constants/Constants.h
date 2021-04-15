#pragma once

#include <iostream>

using namespace std;

/**
 * 共通定数クラス
 */
class Constants
{
private:
	Constants() { };
	~Constants() { };
public:
	/**
	 * アプリ名
	 */
	static const string APPLICATION_NAME;
};
