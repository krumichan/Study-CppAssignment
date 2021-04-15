#ifndef _SINGLETONTEMPLATE_H_
#define _SINGLETONTEMPLATE_H_

/**
 * SingleTon template class...
 */
template <typename T>
class SingleTonTemplate
{
	protected:
	/*コンストラクタとデストラクタは子クラスだけ、扱う。　*/
	/* 外で、このテンプレとを作るのを防止 */
		SingleTonTemplate() { };
		virtual ~SingleTonTemplate() { }

	public:
		/**
		 * 自分のインスタンスを生成し、呼び出す。
		 * @return 自分のインスタンス
		 */
		static T& Call() {
			/* インスタンスを生成 */
			/* 最初、１回しか生成しない */
			static T instance;
			return instance;
		}

	public:
		virtual void Initialization() = 0;

	private:
		/* can't copy */
		/* このクラスの唯一性を維持する為、複写及び代入を防止する。 */
		SingleTonTemplate(SingleTonTemplate const&);
		SingleTonTemplate& operator=(SingleTonTemplate const&);

//		// C++ 11
//	public:
//		SingleTon(SingleTon const&) = delete;
//		SingleTon& operator=(SingleTon const&) = delete;
};

#include "SingleTonTemplate.h"

#endif
