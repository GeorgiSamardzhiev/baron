#include "symbol.hpp"
#include <cstring>

namespace baron {

	Symbol::Symbol(const char * _value, size_t _len) : len(_len) {
		value = new char[len+1];
		for (size_t i = 0; i<len; i++) {
			value[i] = _value[i];
		}
		value[len] = 0;
	}

	Symbol::Symbol(const Symbol& other) : Symbol(other.value, other.len) {}

	Symbol& Symbol::operator=(const Symbol& other) {
		if (this != &other) {
			delete[] this->value;
			this->len = other.len;
			this->value = new char[this->len+1];
			memcpy(this->value, other.value, other.len);
			this->value[this->len] = 0;
		}
		return *this;
	}

	Symbol::~Symbol() {
		delete[] value;
	}

	void Symbol::setValue(const char* newValue, size_t newLen) {
		delete[] value;
		this->len = newLen;
		this->value = new char[this->len+1];
		memcpy(value, newValue, this->len);
		value[this->len] = 0;
	}

	const char* Symbol::getValue() const {
		return value;
	}

	size_t Symbol::getLen() const {
		return len;
	}

	SymbolType Symbol::getType() const {
		return SYMBOL;
	}

	bool operator==(const Symbol& first, const Symbol& second) {
		if (first.getLen() != second.getLen()) {
			return false;
		}
		return memcmp(first.getValue(), second.getValue(), first.getLen()) == 0;
	}

	bool operator!=(const Symbol& first, const Symbol& secont) {
		return !(first == secont);
	}

	bool operator<(const Symbol& first, const Symbol& second) {
		if (first.getLen() == second.getLen()) {
			return std::memcmp(first.getValue(), second.getValue(), first.getLen()) < 0;
		}
		return first.getLen() < second.getLen();
	}

	SymbolType Terminal::getType() const {
		return TERMINAL;
	}

	SymbolType NonTerminal::getType() const {
		return NONTERMINAL;
	}

	EmptyWord::EmptyWord() : Symbol("", 0) {
		emptyWord = nullptr;
	}

	SymbolType EmptyWord::getType() const {
		return EMPTY_WORD;
	}

	EmptyWord* EmptyWord::getInstance() {
		{
			if (emptyWord == nullptr) {
				emptyWord = new EmptyWord();
			}
			return emptyWord;
		}
	}

	EmptyWord* EmptyWord::emptyWord = nullptr;

}
