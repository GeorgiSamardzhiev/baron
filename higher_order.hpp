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

}

#endif // !HIGHER_ORDER_HPP
