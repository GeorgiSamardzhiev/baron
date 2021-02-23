#ifndef HIGHER_ORDER_HPP
#define HIGHER_ORDER_HPP

namespace baron {

	template <class C, typename Function>
	C filter(const C& list, Function f) {
		C res;
		for (typename C::const_iterator it = list.begin(); it != list.end(); ++it) {
			if (f(*it)) {
				res.push_back(*it);
			}
		}
		return res;
	}

	template <class C, typename Function>
	C map(const C& list, Function f) {
		C res;
		for (typename C::const_iterator it = list.begin(); it != list.end(); ++it) {
			res.push_back(f(*it));
		}
		return res;
	}
	
	template<typename T, class C, typename Function>
	T accumulate(T base, const C& list , Function f) {
		for (typename C::const_iterator it = list.begin(); it != list.end(); ++it) {
			base = f(base, *it);
		}
		return base;
	}
	
	template<class I, class T, typename Function>
	T accumulate(T base, I first, I last,  Function f) {
		while( first != last) {
			base = f(base, *(first++));
		}
		return base;
	}

	template<class C, typename Function>
	C zipWith(const C& list1, const C& list2, Function function) {
		C res;
		if (list1.size() != list2.size()){
			return C();
		}		
		for (typename C::const_iterator it1 = list1.begin(), it2 = list2.begin(); it1 != list1.end(); ++it1, ++it2) {
			res.push_back(function(*it1, *it2));
		}
		return res;
	}

}

#endif // !HIGHER_ORDER_HPP
