// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_SINGLETON
#define REAL_SINGLETON

#include <iostream>

namespace real {
	template<typename T>
	class singleton {
		using type = singleton<T>;
	private:
		static T *instance_;
	public:
		singleton() {
			real_assert(instance_ == nullptr, "Only one instance of singleton is allowed!");
			instance_ = static_cast<T *>(this);
		}

		~singleton() {
			instance_ = nullptr;
		}

		static T &instance() {
			return *instance_;
		}

		// region Forbidden Operations
		singleton(type &) = delete;
		void operator=(const type &) = delete;
		// endregion
	};

	template <typename T> T* singleton<T>::instance_ = nullptr;
}

// region util macros
#define SINGLETON(x) x : public real::singleton<x>
#define DEFINE_SINGLETON_INSTANCE(x, val) template <> (x)* singleton<x>::instance_ = val;
// endregion

#endif //REAL_SINGLETON
