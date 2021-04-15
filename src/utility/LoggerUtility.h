#pragma once

#include "../template/SingleTonTemplate.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * デバックレーベル <br>
 * INFO : 知らせる情報 <br>
 * DEBUG : デバック用の情報 <br>
 * TRACE : 詳しい情報 <br>
 *
 *  --　下記は、必ず、出力　--
 *  --　下記の場合は、INFOだけを出力　--
 * WARN : 警告情報 <br>
 * ERROR : 機能に問題があり、機能を終了する必要がある情報 <br>
 * FATAL : プログラム異常終了の情報 <br>
 */
#define LOGGER_LEVEL "TRACE"

class LoggerUtility : SingleTonTemplate<LoggerUtility> {

	friend class SingleTonTemplate<LoggerUtility>;

private:
	/**
	 * インスタンスの生成を防止
	 */
	LoggerUtility() { Initialization(); }

	/**
	 * ディストラクタ
	 */
	~LoggerUtility() { loggerStream.close(); }

public:
	/**
	 * メンバを初期化する関数 <br>
	 * 呼出元は、SingleTonの内部
	 */
	void Initialization() override;

	/**
	 * Info用のコンソールメッセージを出力
	 * @param メッセージ
	 */
	void Info(string);

	/**
	 * Debug用のコンソールメッセージを出力
	 * @param メッセージ
	 */
	void Debug(string);

	/**
	 * Trace用のコンソールメッセージを出力
	 * @param メッセージ
	 */
	void Trace(string);

	/**
	 * Warn用のコンソールメッセージを出力
	 * @param メッセージ
	 */
	void Warn(string);

	/**
	 * Error用のコンソールメッセージを出力
	 * @param メッセージ
	 */
	void Error(string);

	/**
	 * Fatal用のコンソールメッセージを出力
	 * @param メッセージ
	 */
	void Fatal(string);

	/**
	 * ダイアログを出力する
	 * @param メッセージ
	 */
	void PrintDialog(string);


private:
	/**
	 * ログファイルの出力先
	 */
	string logFilePath;

	/**
	 * ログファイルの書き込む為のストリーム
	 */
	fstream loggerStream;
};

//　このクラスのタイプの再定義
using stLoggerUtility = SingleTonTemplate<LoggerUtility>;
