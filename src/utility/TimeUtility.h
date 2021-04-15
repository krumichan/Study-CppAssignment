#pragma once

#include <iostream>

using namespace std;

/**
 * タイムフォーマット文字列
 */
#define COMMON_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

/**
 * タイムフォーマット配列
 */
#define COMMON_TIME_FORMAT_CHAR_ARR "%Y-%m-%d %H:%M:%S"

/**
 * タイムユーティリティ
 */
class TimeUtility
{
private:
	/**
	 * インスタンスの生成を防止
	 */
	TimeUtility() { }

public:
	/**
	 * 現在時刻をミリ秒までの文字列で返す。
	 * @return 現在時刻文字列
	 */
	static string CurrentTimeToString();
};
