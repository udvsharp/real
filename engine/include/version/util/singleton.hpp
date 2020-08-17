// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_SINGLETON
#define VN_SINGLETON

#include <iostream>

namespace vn {
	template<typename T>
	class singleton {
		using type = singleton<T>;
	private:
		static T *instance_;
	public:
		singleton() {
			vn_assert(instance_ == nullptr, "Only one instance of singleton is allowed!");
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
}

// region util macros
#define SINGLETON(x) x : public vn::singleton<x>
#define DEFINE_SINGLETON_INSTANCE(x) template <> x* singleton<x>::instance_ = nullptr;
// endregion

#endif //VN_SINGLETON
