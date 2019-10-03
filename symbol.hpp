#ifndef SYMBOL_HPP
#define SYMBOL_HPP

namespace baron {

	enum SymbolType {
		SYMBOL,
		TERMINAL,
		NONTERMINAL,
		EMPTY_WORD
	};

	class Symbol {
	private:
		char* value;
		size_t len;
	public:
		Symbol(const char* _value = "", size_t _len = 0);
		Symbol(const Symbol& other);
		Symbol& operator=(const Symbol& other);
		~Symbol();

		void setValue(const char* newValue, size_t newLen);
		const char* getValue() const;
		size_t getLen() const;

		virtual SymbolType getType() const;
	};

	bool operator==(const Symbol& first, const Symbol& second);
	bool operator!=(const Symbol& first, const Symbol& secont);
	bool operator<(const Symbol& first, const Symbol& second);


	class Terminal : public Symbol {
	public:
		Terminal(const char* _value = "", size_t _len = 0): Symbol(_value, _len) {}
		Terminal(const Terminal& other): Symbol(other) {}

		SymbolType getType() const;
	};

	class NonTerminal : public Symbol {
	public:
		NonTerminal(const char* _value = "", size_t _len = 0): Symbol(_value, _len) {}
		NonTerminal(const NonTerminal& other): Symbol(other) {}

		SymbolType getType() const;
	};

	class EmptyWord : public Symbol {
	private:
		static EmptyWord* emptyWord;
		EmptyWord();
	public:
		SymbolType getType() const;

		static EmptyWord* getInstance();
	};

}
#endif // !SYMBOL_HPP
