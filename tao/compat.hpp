#pragma once
#if !defined(WIN32)

// std::make_index_sequence
//   to
// tao::seq::make_index_sequence
// std::index_sequence
//   to
// tao::seq::index_sequence
#include "../tao/seq/make_integer_sequence.hpp"

#endif

#include <type_traits>
#include <tuple>

namespace tao
{
// remove_reference_t
template< class T >
using remove_reference_t = typename std::remove_reference<T>::type;

// tuple_element_t
template <std::size_t I, class T>
using tuple_element_t = typename std::tuple_element<I, T>::type;

// conditional_t
template< bool B, class T, class F >
using conditional_t = typename std::conditional<B,T,F>::type;

// remove_pointer_t
template< class T >
using remove_pointer_t = typename std::remove_pointer<T>::type;

// decay_t
template< class T >
using decay_t = typename std::decay<T>::type;

// add_lvalue_reference_t
template< class T >
using add_lvalue_reference_t = typename std::add_lvalue_reference<T>::type;

// add_rvalue_reference_t
template< class T >
using add_rvalue_reference_t = typename std::add_rvalue_reference<T>::type;

// remove_cv_t
template< class T >
using remove_cv_t = typename std::remove_cv<T>::type;

// enable_if_t
template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;

// remove_pointer_t
template< class T >
using remove_pointer_t = typename std::remove_pointer<T>::type;

// remove_all_extents_t
template< class T >
using remove_all_extents_t = typename std::remove_all_extents<T>::type;

// equal_to
template< class T = void >
struct equal_to
{
	constexpr bool operator()(const T &lhs, const T &rhs) const
	{
		return lhs == rhs;
	}
};

template<>
struct equal_to<void>
{
	typedef int is_transparent;

	template<class T1, class T2>
	constexpr auto operator()(T1 && t1, T2 && t2) const -> decltype(static_cast<T1&&>(t1) == static_cast<T2&&>(t2))
	{
		return (static_cast<T1&&>(t1) == static_cast<T2&&>(t2));
	}
};

// add_pointer_t
template< class T >
using add_pointer_t = typename std::add_pointer<T>::type;

// add_const_t
template< class T >
using add_const_t = typename std::add_const<T>::type;

// underlying_type_t
template< class T >
using underlying_type_t = typename std::underlying_type<T>::type;

// is_final
// see https://stackoverflow.com/questions/13809359/how-to-detect-if-a-class-is-final-in-c11
template<class T>
struct is_final
{
	static constexpr bool value = false;
	//using value_type = bool;
	//using type = integral_constant;
};
}

// decltype(auto) func(...) { return xxx; } 
//   to
// auto func(...) -> decltype(xxx) { return xxx; }
