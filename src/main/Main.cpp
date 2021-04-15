#include <iostream>
#include <thread>
#include <chrono>

#include "app_core/AppController.h"

int main(void)
{
	//　ディレイの間隔
	std::chrono::milliseconds duration(100);

	while (1)
	{
		try
		{
			//　アプリのコントローラーを実行
			stAppController::Call().Controll();
		}
		catch (exception& e)
		{
			break;
		}

		//　負荷を下げる為のディレイ
		std::this_thread::sleep_for(duration);
	}

	return 0;
}
