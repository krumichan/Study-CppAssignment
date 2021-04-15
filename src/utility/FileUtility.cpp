#include <fstream>
#include "FileUtility.h"
#include <sys/stat.h>
#include <fileapi.h>

/**
 * このファイルは存在しているか。
 * @param ファイル名
 * @return 存在しているかどうか
 */
bool FileUtility::IsValid(string path)
{
	struct stat buf;
	if (stat (path.c_str(), &buf) != -1)
	{
		return true;
	}

	return false;
}

/**
 * ディレクトリなのかどうか
 * @param 現在パス
 * @return 確認結果
 */
bool FileUtility::IsDirectory(string path)
{
	struct stat buf;
	if (stat (path.c_str(), &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
		{
			return true;
		}
	}

	return false;
}

/**
 * ファイルなのかどうか
 * @param 現在パス
 * @return 確認結果
 */
bool FileUtility::IsFile(string path)
{
	auto att = GetFileAttributes(path.c_str());
	if (att == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}

	if (att & FILE_ATTRIBUTE_NORMAL)
	{
		return false;
	}

	if (IsDirectory(path))
	{
		return false;
	}

	return true;
}
