#include "TimeUtility.h"
#include <ctime>

/**
 * 現在時刻をミリ秒までの文字列で返す。
 * @return 現在時刻文字列
 */
string TimeUtility::CurrentTimeToString()
{
	struct timespec tSpec;
	struct tm timeInfo;
	char timeBuf[32];
	char milliBuf[32];

	clock_gettime(CLOCK_REALTIME, &tSpec);
	localtime_r(&tSpec.tv_sec, &timeInfo);

	strftime(timeBuf, sizeof(timeBuf), COMMON_TIME_FORMAT_CHAR_ARR, &timeInfo);

	const int msec = tSpec.tv_nsec / 1000000;
	snprintf(milliBuf, sizeof(milliBuf), "%s.%03d", timeBuf, msec);

	string curTimeMilliStr(milliBuf);

	return curTimeMilliStr;
}
