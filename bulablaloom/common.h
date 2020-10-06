#pragma once

#include <cstring>
#include <memory> 
#include <stdarg.h>
#include <stdexcept>


namespace snprintf_lite
{
	void __throw_insufficient_space(const char *__buf, const char *__bufend)
	{
		const size_t __len = __bufend - __buf + 1;

		const char __err[] = "not enough space for format expansion "
			"(Please submit full bug report at https://gcc.gnu.org/bugs/):\n    ";
		const size_t __errlen = sizeof(__err) - 1;

		std::allocator<char> chAllocator;
		char *const __e = chAllocator.allocate(__errlen + __len);
		memcpy(__e, __err, __errlen);
		memcpy(__e + __errlen, __buf, __len - 1);
		__e[__errlen + __len - 1] = '\0';

		throw std::logic_error(__e);
	}

	// Private routine to append decimal representation of VAL to the given
	// BUFFER, but not more than BUFSIZE characters.
	// Does not NUL-terminate the output buffer.
	// Returns number of characters appended, or -1 if BUFSIZE is too small.
	int __concat_size_t(char *__buf, size_t __bufsize, size_t __val)
	{
		int __ilen = 3 * sizeof(__val);
		std::allocator<char> chAllocator;
		char* __cs = chAllocator.allocate(__ilen);
		char* __end = __cs + __ilen;
		do
		{
			*--__end = "0123456789"[__val % 10];
			__val /= 10;
		} while (__val != 0);

		size_t __len = __cs + __ilen - __end;
		if (__bufsize < __len)
			return -1;
		memcpy(__buf, __cs + __ilen - __len, __len);
		return __len;
	}

	// Private routine to print into __buf arguments according to format,
	// not to exceed __bufsize.
	// Only '%%', '%s' and '%zu' format specifiers are understood.
	// Returns number of characters printed (excluding terminating NUL).
	// Always NUL-terminates __buf.
	// Throws logic_error on insufficient space.
	int __snprintf_lite(char* __buf, size_t __bufsize, const char* __fmt, va_list __ap)
	{
		char* __d = __buf;
		const char* __s = __fmt;
		const char* const __limit = __d + __bufsize - 1; 

		while (__s[0] != '\0' && __d < __limit)
		{
			if (__s[0] == '%')
				switch (__s[1])
				{
				default:  // Stray '%'. Just print it.
					break;
				case '%':  // '%%'
					__s += 1;
					break;
				case 's':  // '%s'.
					{
					const char *__v = va_arg(__ap, const char *);
					while (__v[0] != '\0' && __d < __limit)
						*__d++ = *__v++;
					if (__v[0] != '\0')
						__throw_insufficient_space(__buf, __d);
					__s += 2;  
					continue;
					}
					break;
				case 'z':
					if (__s[2] == 'u')  
					{
						const int __len = __concat_size_t(__d, __limit - __d, va_arg(__ap, size_t));
						if (__len > 0)
							__d += __len;
						else
							__throw_insufficient_space(__buf, __d);
						__s += 3;  
						continue;
					}
					// Stray '%zX'. Just print it.
					break;
				}

			*__d++ = *__s++;
		}
		if (__s[0] != '\0')
			__throw_insufficient_space(__buf, __d);
		*__d = '\0';
		return __d - __buf;
	}
}

namespace functexcept
{
	void __throw_out_of_range_fmt(const char* __fmt, ...)
	{
		const size_t __len = strlen(__fmt);
		const size_t __alloca_size = __len + 512;
		std::allocator<char> chAllocator;
		char *const __s = chAllocator.allocate(__alloca_size);

		va_list __ap;
		va_start(__ap, __fmt);
		snprintf_lite::__snprintf_lite(__s, __alloca_size, __fmt, __ap);
		va_end(__ap);
	}
}
