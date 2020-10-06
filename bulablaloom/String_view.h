#pragma once

#include "common.h"

#define __N(msgid)     (msgid)


namespace space
{
	template <typename _CharT, typename _Traits = space::char_traits<_CharT>>
	class basic_string_view
	{
	public:
		using traits_type = _Traits;
		using iterator = const _CharT*;
		using const_iterator = const _CharT*;
		using size_type = std::size_t;

		constexpr basic_string_view() noexcept 
			: _M_len{ 0 }, _M_str{ nullptr } { }
		constexpr basic_string_view(const _CharT* __str) noexcept 
			: _M_len{ __str == nullptr ? 0 : traits_type::length(__str) }, _M_str{ __str } { } 
		constexpr basic_string_view(const _CharT* __str, size_t __len) noexcept 
			: _M_len{ __len }, _M_str{ __str } { }

		constexpr basic_string_view(const basic_string_view&) noexcept = default;

		constexpr basic_string_view& operator=(const basic_string_view&) noexcept = default;

		constexpr size_type length() const noexcept { return _M_len; }
		constexpr size_type size() const noexcept { return _M_len; }

		constexpr const_iterator begin() const noexcept { return _M_str; }
		constexpr const_iterator end() const noexcept { return _M_str + _M_len; }

		constexpr const _CharT* data() const noexcept { return _M_str; }

		size_type copy(_CharT* __str, size_type __n, size_type __pos = 0) const
		{
			__pos = _M_check(__pos, "basic_string_view::copy");
			const size_type __rlen = std::min(__n, _M_len - __pos);
			for (auto __begin = _M_str + __pos, __end = __begin + __rlen; __begin != __end;)
				*__str++ = *_begin++;
			return len;
		}

		constexpr size_type _M_check(size_type __pos, const char* __s) const noexcept(false)
		{
			if (__pos > this->size())
				__throw_out_of_range_fmt(__N("%s: __pos (which is %zu) > "
					"this->size() (which is %zu)"),
					__s, __pos, this->size());
			return __pos;
		}

	private:
		size_type     _M_len;
		const _CharT* _M_str;
	};

	using string_view = basic_string_view<char>;

	// -------------------- operator+ --------------------
	// PROBLEM: _M_str allocated on the heap
	template <typename _CharT, typename _Traits>
	basic_string_view<_CharT, _Traits> operator+(const basic_string_view<_CharT, _Traits>& lhs,
		                                         const basic_string_view<_CharT, _Traits>& rhs) 
	{
		size_t __len = lhs.length() + rhs.length();

		std::allocator<_CharT> chAllocator;
		_CharT* __cs = chAllocator.allocate(__len + 1);
		memcpy(__cs, lhs.data(), lhs.length());
		memcpy(__cs + lhs.length(), rhs.data(), rhs.length());
		__cs[__len] = '\0';

		return { __cs, __len };
	}

	template <typename _CharT, typename _Traits>
	basic_string_view<_CharT, _Traits> operator+(const _CharT* lhs,
		                                         const basic_string_view<_CharT, _Traits>& rhs)
	{
		size_t __lhs_len = _Traits::length(lhs);
		size_t __len = __lhs_len + rhs.length();

		std::allocator<_CharT> chAllocator;
		_CharT* __cs = chAllocator.allocate(__len + 1);
		memcpy(__cs, lhs, __lhs_len);
		memcpy(__cs + __lhs_len, rhs.data(), rhs.length());
		__cs[__len] = '\0';

		return { __cs, __len };
	}

	template <typename _CharT, typename _Traits>
	basic_string_view<_CharT, _Traits> operator+(_CharT lhs,
												 const basic_string_view<_CharT, _Traits>& rhs)
	{
		size_t __len = sizeof(lhs) + rhs.length();

		std::allocator<_CharT> chAllocator;
		_CharT* __cs = chAllocator.allocate(__len + 1);
		chAllocator.construct(__cs, lhs);
		memcpy(__cs + sizeof(lhs), rhs.data(), rhs.length());
		__cs[__len] = '\0';

		return { __cs, __len };
	}

}
