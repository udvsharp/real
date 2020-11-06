// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_SINGLETON
#define REAL_SINGLETON

namespace Real
{
	template<typename T>
	class Singleton
	{
		using type = Singleton<T>;
	private:
		static T* instance;
	public:
		Singleton()
		{
			real_msg_assert(instance == nullptr,
					"Only one instance of singleton is allowed!");
			instance = static_cast<T*>(this);
		}

		~Singleton()
		{
			instance = nullptr;
		}

		static T& Instance()
		{
			return *instance;
		}

		// region Forbidden Operations
		Singleton(type&) = delete;
		void operator=(const type&) = delete;
		// endregion
	};

	template<typename T> T* Singleton<T>::instance = nullptr;
}

// region util macros
#define SINGLETON(x) x : public Real::Singleton<x>
// endregion

#endif //REAL_SINGLETON
