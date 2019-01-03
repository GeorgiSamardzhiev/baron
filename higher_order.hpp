#ifndef HIGHER_ORDER_HPP
#define HIGHER_ORDER_HPP

namespace baron {

	template <class C, typename Function>
	C filter(C list, Function f) {
		C res;
		for (typename C::iterator it = list.begin(); it != list.end(); ++it) {
			if (f(*it)) {
				res.push_back(*it);
			}
		}
		return res;
	}

	template <class C, typename Function>
	C map(C list, Function f) {
		C res;
		for (typename C::iterator it = list.begin(); it != list.end(); ++it) {
			res.push_back(f(*it));
		}
		return res;
	}

	template <typename R, class C, typename Function>
	R foldl(R base, C list, Function f) {
		R res = base;
		for (typename C::iterator it = list.begin(); it != list.end(); ++it) {
			res = f(res, (*it));
		}
		return res;
	}

	template <typename R, class C, typename Function>
	R foldr(R base, C list, Function f) {
		R res = base;
		for (typename C::reverse_iterator it = list.rbegin(); it != list.rend(); ++it) {
			res = f(res, (*it));
		}
		return res;
	}

}

#endif // !HIGHER_ORDER_HPP
