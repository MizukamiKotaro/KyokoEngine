#pragma once
#include <memory>
// 響子
namespace Kyoko {
	/// <summary>
	/// シングルトン
	/// </summary>
	namespace Singleton {
		/// <summary>
		/// シングルトンの生成
		/// </summary>
		void CreateSingletons();
		/// <summary>
		/// シングルトンの解放
		/// </summary>
		void DestroySingletons();
		/// <summary>
		/// シングルトンの基底クラス
		/// </summary>
		template <typename T>
		class BaseSingleton {
		public:
			static void Create();
			static T* GetInstance();
			static void DestroyInstance();
		protected:
			BaseSingleton() = default;
			~BaseSingleton() = default;
			BaseSingleton(const BaseSingleton&) = delete;
			const BaseSingleton& operator=(const BaseSingleton&) = delete;

			static std::unique_ptr<T> instance_;
		};

	}
}