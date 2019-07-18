// sol2 

// The MIT License (MIT)

// Copyright (c) 2013-2018 Rapptz, ThePhD and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SOL_STACK_PROXY_HPP
#define SOL_STACK_PROXY_HPP

#include "stack_proxy_base.hpp"

namespace sol {
	struct stack_proxy : public stack_proxy_base {
	public:
		stack_proxy()
		: stack_proxy_base() {
		}
		stack_proxy(lua_State* L, int index)
		: stack_proxy_base(L, index) {
		}

		// sure todo
		/*template <typename... Ret, typename... Args>
		auto call(Args&&... args) -> decltype(stack_function(this->lua_state(), this->stack_index()).call<Ret...>(std::forward<Args>(args)...));*/

		template <std::size_t... I, typename... Ret, typename... Args>
		auto invoke(types<Ret...>, tao::seq::index_sequence<I...>, Args&&... args) const
			//-> decltype(popper<meta::unqualified_t<T>>{}.pop((lua_State *)1))
			->decltype(stack::pop<std::tuple<Ret...>>(lua_state()))
		{
			stack_function sf(this->lua_state(), this->stack_index());
			return sf.call<Ret...>(std::forward<Args>(args)...);
		}

		template <std::size_t I, typename Ret, typename... Args>
		Ret invoke(types<Ret>, tao::seq::index_sequence<I>, Args&&... args) const {
			stack_function sf(this->lua_state(), this->stack_index());
			return sf.call<Ret...>(std::forward<Args>(args)...);
		}

		template <std::size_t I, typename... Args>
		void invoke(types<void>, tao::seq::index_sequence<I>, Args&&... args) const {
		}

		template <typename... Args>
		protected_function_result invoke(types<>, tao::seq::index_sequence<>, Args&&... args) const {
			stack_function sf(this->lua_state(), this->stack_index());
			return sf.call<>(std::forward<Args>(args)...);
		}

		template <typename... Ret, typename... Args>
		auto call(Args&&... args)
			-> decltype(invoke(types<Ret...>(), tao::seq::make_index_sequence<sizeof...(Ret)>()))
		{
			return invoke(types<Ret...>(), tao::seq::make_index_sequence<sizeof...(Ret)>());
		}

		template <typename... Args>
		auto operator()(Args&&... args) -> decltype(call<>(std::forward<Args>(args)...)) {
			return call<>(std::forward<Args>(args)...);
		}
	};

	namespace stack {
		template <>
		struct getter<stack_proxy> {
			static stack_proxy get(lua_State* L, int index = -1) {
				return stack_proxy(L, index);
			}
		};

		template <>
		struct pusher<stack_proxy> {
			static int push(lua_State*, const stack_proxy& ref) {
				return ref.push();
			}
		};
	} // namespace stack
} // namespace sol

#endif // SOL_STACK_PROXY_HPP
