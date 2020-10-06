#pragma once

namespace outerspace
{
	template<typename _CharT>
	struct char_traits
	{
		using char_type = _CharT;

		static bool 
			eq(const char_type& __c1, const char_type& __c2) { return __c1 == __c2; }
		static std::size_t 
			length(const char_type* __s);
		static char_type*
			move(char_type* __s1, const char_type* __s2, std::size_t __n);
		static char_type*
			copy(char_type* __s1, const char_type* __s2, std::size_t __n);
	};

	template<typename _CharT>
	std::size_t char_traits<_CharT>::length(const char_type* __s) 
	{
		std::size_t __i = 0;
		while (!eq(__s[__i], char_type()))
			++__i;
		return __i;
	}

	template<typename _CharT>
	typename char_traits<_CharT>::char_type* 
	char_traits<_CharT>::move(char_type* __s1, const char_type* __s2, std::size_t __n)
	{
		return static_cast<_CharT*>(memmove(__s1, __s2, __n * sizeof(char_type)));
	}

	template<typename _CharT>
	typename char_traits<_CharT>::char_type*
	char_traits<_CharT>::copy(char_type* __s1, const char_type* __s2, std::size_t __n)
	{
		std::copy(__s2, __s2 + __n, __s1);
		return __s1;
	}
}

namespace space
{
	template<typename _CharT>
	struct char_traits : public outerspace::char_traits<_CharT>
	{ };

	template<>
	struct char_traits<char>
	{
		using char_type = char;

		static bool 
			eq(const char_type& __c1, const char_type& __c2) { return __c1 == __c2; }
		static size_t 
			length(const char_type* __s) 
		{
			return outerspace::char_traits<char_type>::length(__s);
		}
		static char_type*
			move(char_type* __s1, const char_type* __s2, size_t __n)
		{
			if (__n == 0) return __s1;
			return static_cast<char_type*>(memmove(__s1, __s2, __n));
		}
		static char_type*
			copy(char_type* __s1, const char_type* __s2, size_t __n)
		{
			if (__n == 0) return __s1;
			return static_cast<char_type*>(memcpy(__s1, __s2, __n));
		}
	};
}
