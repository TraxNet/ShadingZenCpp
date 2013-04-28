#ifndef __SHZ_TYPES__
#define __SHZ_TYPES__

namespace shz{ namespace math{
	///////////////////////////////////
	// Types from Irrlicht 3D Engine //
	///////////////////////////////////

	//! 8 bit unsigned variable.
	/** This is a typedef for unsigned char, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef unsigned __int8		u8;
	#else
	typedef unsigned char		u8;
	#endif

	//! 8 bit signed variable.
	/** This is a typedef for signed char, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int8			s8;
	#else
	typedef signed char		s8;
	#endif

	//! 8 bit character variable.
	/** This is a typedef for char, it ensures portability of the engine. */
	typedef char			c8;



	//! 16 bit unsigned variable.
	/** This is a typedef for unsigned short, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef unsigned __int16	u16;
	#else
	typedef unsigned short		u16;
	#endif

	//! 16 bit signed variable.
	/** This is a typedef for signed short, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int16			s16;
	#else
	typedef signed short		s16;
	#endif



	//! 32 bit unsigned variable.
	/** This is a typedef for unsigned int, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef unsigned __int32	u32;
	#else
	typedef unsigned int		u32;
	#endif

	//! 32 bit signed variable.
	/** This is a typedef for signed int, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int32			s32;
	#else
	typedef signed int		s32;
	#endif


	#ifdef __IRR_HAS_S64
	//! 64 bit unsigned variable.
	/** This is a typedef for 64bit uint, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef unsigned __int64			u64;
	#elif __GNUC__
	#if __WORDSIZE == 64
	typedef unsigned long int			u64;
	#else
	__extension__ typedef unsigned long long	u64;
	#endif
	#else
	typedef unsigned long long			u64;
	#endif

	//! 64 bit signed variable.
	/** This is a typedef for 64bit int, it ensures portability of the engine. */
	#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int64					s64;
	#elif __GNUC__
	#if __WORDSIZE == 64
	typedef long int				s64;
	#else
	__extension__ typedef long long			s64;
	#endif
	#else
	typedef long long				s64;
	#endif
	#endif	// __IRR_HAS_S64



	//! 32 bit floating point variable.
	/** This is a typedef for float, it ensures portability of the engine. */
	typedef float				f32;

	//! 64 bit floating point variable.
	/** This is a typedef for double, it ensures portability of the engine. */
	typedef double				f64;
} }

#endif // __SHZ_TYPES__

