#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include "symbol.hpp"
#include <vector>
#include <set>

namespace baron {

	struct Rule {
		NonTerminal* leftSide;
		std::vector<Symbol*> rightSide;
	};

	bool operator==(const Rule& first, const Rule& second);
	bool operator!=(const Rule& first, const Rule& second);

	class ContextFreeGrammar {
	private:
		NonTerminal* start;
		std::vector<Rule> rules;

		NonTerminal* newNonTerminal() const;

		void newStart(); //new starting sybmol
		void term(); //Eliminate rules with nonsolitary terminals
		void bin(); //Eliminate right-hand sides with more than 2 nonterminals
		void del(); // Eliminate ε-rules
		void unit(); //Eliminate unit rules

	public:

		ContextFreeGrammar(const NonTerminal* start = new NonTerminal(), std::vector<Rule> rules = std::vector<Rule>());
		ContextFreeGrammar(const ContextFreeGrammar& other);
		const ContextFreeGrammar& operator=(const ContextFreeGrammar& other);
		~ContextFreeGrammar();

		void setStart(NonTerminal* s);
		void setRules(std::vector<Rule> rules);
		const NonTerminal* getStart() const;
		const std::vector<Rule> getRules() const;
		std::set<NonTerminal*> getNonTerminals() const;
		std::set<NonTerminal> getNonTerminalsAsValues() const;

		void addRule(const Rule& rule);
		void removeRule(const Rule& rule);

		std::set<NonTerminal*> getLeftSideOf(const std::vector<Symbol*>& rightSide) const;
		bool isInChomskyNormalForm() const;
		bool CYK(std::vector<Terminal*>) const;

		void chomskify();
	};

	ContextFreeGrammar concatenationOverGrammars(const ContextFreeGrammar& first, const ContextFreeGrammar& second);
	ContextFreeGrammar unionOverGrammars(const ContextFreeGrammar& first, const ContextFreeGrammar& second);
	ContextFreeGrammar iterationOverGrammar(const ContextFreeGrammar& grammar);

}

#endif // !GRAMMAR_HPP
