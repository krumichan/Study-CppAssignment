#include "AppInput.h"

/**
 * コンストラクタ
 */
AppInput::AppInput()
{
	Initialization();
}

/**
 * メンバを初期化する関数
 */
void AppInput::Initialization()
{
	//　マップの追加
	inpMapper[0x31] = "camera";
	inpMapper[0x32] = "barcode";
	inpMapper[VK_BACK] = "lobby";
	inpMapper[VK_RETURN] = "shutter";

	//　作成しているツールのバージョンでは
	//　for (const aut& [key, value] : inpMapper)
	//　が使えない。


	//　マップをToggleリストに渡す
	map<int, string>::iterator itr;

	//　マップ要素を繰り返す
	for (itr = inpMapper.begin(); itr != inpMapper.end(); itr++)
	{
		//　Toggle生成　（入力値、入力値に対する動作文字列）
		Toggle toggle(itr->first, itr->second);

		//　リストに挿入
		toggleList.push_back(toggle);
	}
}

/**
 * 機器から、入力を受け取る。
 * @return 入力値
 */
string AppInput::GetInput()
{
	list<Toggle>::iterator itr;

	//　Toggleリストの中身を確認
	for (itr = toggleList.begin(); itr != toggleList.end(); itr++)
	{
		if (*itr)
		{
			return itr->Get();
		}
	}

	return "";
}
