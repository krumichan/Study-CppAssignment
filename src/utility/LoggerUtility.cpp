#include "LoggerUtility.h"
#include "TimeUtility.h"
#include "../constants/Constants.h"

/**
 * メンバを初期化する関数 <br>
 * 呼出元は、SingleTonの内部
 */
void LoggerUtility::Initialization()
{
	logFilePath = Constants::APPLICATION_NAME + ".log";

	loggerStream.open(logFilePath, fstream::in | fstream::out | fstream::app);

	//　ファイルが存在しない場合、ファイルを作成した後、ログ出力ストリームを作成
	if (!loggerStream)
	{
		loggerStream.open(logFilePath, fstream::in | fstream::out | fstream::trunc);
		loggerStream << "\n";
		loggerStream.close();
	}
}

/**
 * Info用のコンソールメッセージを出力
 * @param メッセージ
 */
void LoggerUtility::Info(string _message)
{
	loggerStream << "[INFO] " << TimeUtility::CurrentTimeToString() << endl;
	loggerStream << "contents : " << _message << endl;
}

/**
 * Debug用のコンソールメッセージを出力
 * @param メッセージ
 */
void LoggerUtility::Debug(string _message)
{
	const string check = LOGGER_LEVEL;
	if (!check.compare("INFO") ||
		!check.compare("WARN") ||
		!check.compare("ERROR") ||
		!check.compare("FATAL"))
	{
		return;
	}

	loggerStream << "[DEBUG] " << TimeUtility::CurrentTimeToString() << endl;
	loggerStream << "contents : " << _message << endl;
}

/**
 * Trace用のコンソールメッセージを出力
 * @param メッセージ
 */
void LoggerUtility::Trace(string _message)
{
	const string check = LOGGER_LEVEL;
	if (!check.compare("INFO") ||
		!check.compare("DEBUG") ||
		!check.compare("WARN") ||
		!check.compare("ERROR") ||
		!check.compare("FATAL"))
	{
		return;
	}

	loggerStream << "[TRACE] " << TimeUtility::CurrentTimeToString() << endl;
	loggerStream << "contents : " << _message << endl;
}

/**
 * Warn用のコンソールメッセージを出力
 * @param メッセージ
 */
void LoggerUtility::Warn(string _message)
{
	loggerStream << "[WARN] " << TimeUtility::CurrentTimeToString() << endl;
	loggerStream << "contents : " << _message << endl;
}

/**
 * Error用のコンソールメッセージを出力
 * @param メッセージ
 */
void LoggerUtility::Error(string _message)
{
	loggerStream << "[ERROR] " << TimeUtility::CurrentTimeToString() << endl;
	loggerStream << "contents : " << _message << endl;
}

/**
 * Fatal用のコンソールメッセージを出力
 * @param メッセージ
 */
void LoggerUtility::Fatal(string _message)
{
	loggerStream << "[FATAL] " << TimeUtility::CurrentTimeToString() << endl;
	loggerStream << "contents : " << _message << endl;
}

/**
 * ダイアログを出力する
 * @param メッセージ
 */
void LoggerUtility::PrintDialog(string _message)
{
	cout << _message << endl;
}
