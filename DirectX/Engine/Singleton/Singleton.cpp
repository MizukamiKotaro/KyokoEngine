#include "Singleton.h"
#include <cassert>
#include "DirectXBase/DirectXBase.h"

// 響子
namespace Kyoko {
	/// <summary>
	/// シングルトン
	/// </summary>
	namespace Singleton {
		template class BaseSingleton<DirectXBase>;
		template<>
		std::unique_ptr<DirectXBase> BaseSingleton<DirectXBase>::instance_ = nullptr;

		void CreateSingletons()
		{
			DirectXBase::Create();
		}

		void DestroySingletons()
		{

		}

		template<typename T>
		void BaseSingleton<T>::Create()
		{
			instance_ = std::make_unique<T>();
		}
		template <typename T>
		T* BaseSingleton<T>::GetInstance()
		{
			assert(instance_);
			return instance_.get();
		}
		template <typename T>
		void BaseSingleton<T>::DestroyInstance()
		{
			instance_.reset();
		}
	}
}