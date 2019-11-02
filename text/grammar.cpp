#include "grammar.hpp"
#include <algorithm>

namespace baron {

	std::set<NonTerminal*> ContextFreeGrammar::getLeftSideOf(const std::vector<Symbol*>& rightSide) const {
		std::set<NonTerminal*> leftSides;
		for (Rule rule : rules) {
			size_t len = rightSide.size();
			if (rule.rightSide.size() != rightSide.size()) {
				continue;
			}
			auto rightSidesAreTheSame = [rule, rightSide, len]() {
				for (size_t i = 0; i<len; i++) {
					if (*rule.rightSide[i] != *rightSide[i]) {
						return false;
					}
				}
				return true;
			};
			if (rightSidesAreTheSame()) {
				leftSides.insert(rule.leftSide);
			}
		}
		return leftSides;
	}

	bool ContextFreeGrammar::isInChomskyNormalForm() const {
		for (Rule rule : rules) {
			if (rule.rightSide.size() == 1 && rule.rightSide.front()->getType() != TERMINAL) {
				return false;
			}
			if (rule.rightSide.size() == 2 &&
				(rule.rightSide[0]->getType() != rule.rightSide[1]->getType() ||
				 rule.rightSide.front()->getType() != NONTERMINAL)) {
				return false;
			}
			if (rule.rightSide.size() > 2) {
				return false;
			}
		}
		return true;
	}

	bool ContextFreeGrammar::CYK(std::vector<Terminal*> word) const {
		size_t len = word.size();
		std::vector<std::vector<std::vector<NonTerminal>>> table(len,
																 std::vector<std::vector<NonTerminal>>(len,
																									   std::vector<NonTerminal>()));
		for (size_t i = 0; i<word.size(); i++) {
			std::set<NonTerminal*> res = getLeftSideOf(std::vector<Symbol*>({ word[i] }));
			for (NonTerminal* nonTerminal: res) {
				table[i][i].push_back(*nonTerminal);
			}
		}

		for (size_t s = 0; s < len; s++) {
			for (size_t i = 0; i < len-s; i++) {
				for (size_t k = i; k < i + s; k++) {

					for (NonTerminal B : table[i][k]) {
						for (NonTerminal C : table[k+1][i+s]) {
							std::set<NonTerminal*> A = getLeftSideOf(std::vector<Symbol*>({ &B, &C }));
							for (NonTerminal* nonTerminal: A) {
								table[i][i+s].push_back(*nonTerminal);
							}
						}
					}

				}
			}
		}

		return std::find(table[0][len-1].begin(), table[0][len-1].end(), *start) != table[0][len-1].end();
	}

	void ContextFreeGrammar::chomskify() {
		if (isInChomskyNormalForm()) {
			return;
		}
		newStart();
		term();
		bin();
		del();
		unit();
	}

	NonTerminal* ContextFreeGrammar::newNonTerminal() const {
		std::set<NonTerminal> nonTerminals = getNonTerminalsAsValues();
		size_t newStartLenth = this->start->getLen() + 3;
		char* newStartValue = new char[newStartLenth];
		std::memcpy(newStartValue, this->start->getValue(), this->start->getLen());
		newStartValue[this->start->getLen()] = 'N';
		newStartValue[this->start->getLen()+1] = 'E';
		newStartValue[this->start->getLen()+2] = 'W';
		NonTerminal nonTerminal(newStartValue, newStartLenth);
		while (nonTerminals.find(nonTerminal) != nonTerminals.end()) {
			char* temp = new char[newStartLenth + 3];
			memcpy(temp, newStartValue, newStartLenth);
			temp[newStartLenth] = 'N';
			temp[newStartLenth + 1] = 'E';
			temp[newStartLenth + 2] = 'W';
			memcpy(newStartValue, temp, newStartLenth += 3);
			nonTerminal.setValue(newStartValue, newStartLenth);
		}
		return new NonTerminal(nonTerminal);
	}

	void ContextFreeGrammar::newStart() {
		NonTerminal* newStartNonTerminal = newNonTerminal();
		Rule newRule;
		newRule.leftSide = newStartNonTerminal;
		newRule.rightSide = std::vector<Symbol*>({ this->start });
		this->rules.push_back(newRule);
		this->start = newStartNonTerminal;
	}

	void ContextFreeGrammar::term() {
		size_t len = this->rules.size();
		for (size_t i = 0; i<len; i++) {
			if (this->rules[i].rightSide.size() > 1) {
				size_t length = this->rules[i].rightSide.size();
				for (size_t j = 0; j<length; j++) {
					if (this->rules[i].rightSide[j]->getType() == TERMINAL) {
						NonTerminal* nonTerminal = newNonTerminal();
						Rule newRule;
						newRule.leftSide = nonTerminal;
						newRule.rightSide = std::vector<Symbol*>({ this->rules[i].rightSide[j] });
						this->rules.push_back(newRule);
						this->rules[i].rightSide[j] = nonTerminal;
					}
				}
			}
		}
	}

	void ContextFreeGrammar::bin() {
		size_t len = this->rules.size();
		for (size_t i = 0; i<len; i++) {
			size_t size = this->rules[i].rightSide.size();
			if (size > 2) {
				std::vector<NonTerminal*> newNonTerminals;
				size_t newNonTerminalsSize = size-2;
				for (size_t i = 0; i < newNonTerminalsSize; i++) {
					newNonTerminals.push_back(newNonTerminal());
				}
				Rule newRule;
				newRule.leftSide = this->rules[i].leftSide;
				newRule.rightSide = std::vector<Symbol*>({ this->rules[i].rightSide[0], newNonTerminals[0] });
				rules.push_back(newRule);
				for (size_t i = 1; i < newNonTerminalsSize; i++) {
					newRule.leftSide = newNonTerminals[i-1];
					newRule.rightSide = std::vector<Symbol*>({ this->rules[i].rightSide[i], newNonTerminals[i] });
					rules.push_back(newRule);
				}
				newRule.leftSide = newNonTerminals[newNonTerminalsSize-1];
				newRule.rightSide = std::vector<Symbol*>({ this->rules[i].rightSide[size-2], this->rules[i].rightSide[size-1] });
				rules.push_back(newRule);
				rules.erase(this->rules.begin() + i);
				--i; --len;
			}
		}
	}

	void ContextFreeGrammar::del() {
		size_t length = this->rules.size();
		Rule newRule;
		for (size_t j = 0; j<length; j++) {
			if (this->rules[j].rightSide.size() == 1 && this->rules[j].rightSide[0]->getType() == EMPTY_WORD) {
				for (Rule r : this->rules) {
					if (r != this->rules[j]) {
						size_t len = r.rightSide.size();
						for (size_t i = 0; i<len; i++) {
							if (r.rightSide[i] == this->rules[j].leftSide) {
								newRule.leftSide = r.leftSide;
								newRule.rightSide = r.rightSide;
								newRule.rightSide.erase(newRule.rightSide.begin() + i);
								this->rules.push_back(newRule);
							}
						}
					}
				}
				this->rules.erase(this->rules.begin()+j);
			}
		}
	}

	void ContextFreeGrammar::unit() {
		size_t len = this->rules.size();
		for (size_t i = 0; i<len; i++) {
			if (this->rules[i].rightSide.size() == 1 && this->rules[i].rightSide[0]->getType() == NONTERMINAL) {
				for (size_t j = 0; j<len; j++) {
					if (*this->rules[j].leftSide == *this->rules[i].rightSide[0] && i != j) {
						Rule newRule;
						newRule.leftSide = this->rules[i].leftSide;
						newRule.rightSide = this->rules[j].rightSide;
						this->rules.push_back(newRule);
						++len;
					}
				}
				this->rules.erase(this->rules.begin() + i);
				--i; --len;
			}
		}
	}

	ContextFreeGrammar::ContextFreeGrammar(const NonTerminal* _start, std::vector<Rule> _rules):  rules(_rules) { 
		this->start = new NonTerminal( *_start );
	}

	ContextFreeGrammar::ContextFreeGrammar(const ContextFreeGrammar& other) :
		ContextFreeGrammar(other.getStart(), other.getRules()) {
	}

	const ContextFreeGrammar& ContextFreeGrammar::operator=(const ContextFreeGrammar& other) {
		if (this != &other) {
			this->start->setValue(other.start->getValue(), other.start->getLen());
			this->rules = other.rules;
		}
		return *this;
	}

	ContextFreeGrammar::~ContextFreeGrammar() {
		delete this->start;
	}

	void ContextFreeGrammar::setStart(NonTerminal* s) {
		start = new NonTerminal(*s);
	}

	void ContextFreeGrammar::setRules(std::vector<Rule> rules) {
		this->rules.clear();
		this->rules = rules;
	}

	const NonTerminal* ContextFreeGrammar::getStart() const {
		return start;
	}

	const std::vector<Rule> ContextFreeGrammar::getRules() const {
		return rules;
	}

	std::set<NonTerminal*> ContextFreeGrammar::getNonTerminals() const {
		std::set<NonTerminal*> nonTerminals;
		for (Rule rule : rules) {
			nonTerminals.insert(rule.leftSide);
		}
		return nonTerminals;
	}

	std::set<NonTerminal> ContextFreeGrammar::getNonTerminalsAsValues() const {
		std::set<NonTerminal> nonTerminals;
		for (Rule rule : rules) {
			nonTerminals.insert(*rule.leftSide);
		}
		return nonTerminals;
	}

	void ContextFreeGrammar::addRule(const Rule& rule) {
		this->rules.push_back(rule);
	}

	void ContextFreeGrammar::removeRule(const Rule& rule) {
		this->rules.erase(std::find(this->rules.begin(), this->rules.end(), rule));
	}

	bool operator==(const Rule& first, const Rule& second) {
		return first.leftSide == second.leftSide && first.rightSide == second.rightSide;
	}

	bool operator!=(const Rule& first, const Rule& second) {
		return first.leftSide != second.leftSide || first.rightSide != second.rightSide;
	}

	ContextFreeGrammar concatenationOverGrammars(const ContextFreeGrammar & first, const ContextFreeGrammar & second) {
		NonTerminal nonTerminal("ConcatStartNonTerminal", 22);
		ContextFreeGrammar grammar;
		std::vector<Rule> newRules(first.getRules().size() + second.getRules().size()+1);
		newRules = first.getRules();
		for (Rule rule : second.getRules()) {
			newRules.push_back(rule);
		}
		Rule startRule;
		startRule.leftSide = &nonTerminal;
		startRule.rightSide = std::vector<Symbol*>({ (Symbol*)first.getStart(), (Symbol*)second.getStart() });
		newRules.push_back(startRule);
		grammar.setRules(newRules);
		grammar.setStart(&nonTerminal);
		return grammar;
	}

	ContextFreeGrammar unionOverGrammars(const ContextFreeGrammar& first, const ContextFreeGrammar& second) {
		NonTerminal* nonTerminal = new NonTerminal;
		nonTerminal->setValue("UnionStartNonTerminal", 21);
		ContextFreeGrammar grammar;
		std::vector<Rule> newRules(first.getRules().size() + second.getRules().size()+2);
		newRules = first.getRules();
		for (Rule rule : second.getRules()) {
			newRules.push_back(rule);
		}
		Rule rule1, rule2;
		rule1.leftSide = nonTerminal;
		rule1.rightSide = std::vector<Symbol*>({ (Symbol*)first.getStart() });
		newRules.push_back(rule1);
		rule2.leftSide = nonTerminal;
		rule2.rightSide = std::vector<Symbol*>({ (Symbol*)second.getStart() });
		newRules.push_back(rule2);
		grammar.setRules(newRules);
		grammar.setStart(nonTerminal);
		return grammar;
	}

	ContextFreeGrammar iterationOverGrammar(const ContextFreeGrammar& grammar) {
		NonTerminal* nonTerminal = new NonTerminal;
		nonTerminal->setValue("iterStartNonTerminal", 20);
		ContextFreeGrammar newGrammar;
		std::vector<Rule> newRules(grammar.getRules().size() + 2);
		newRules = grammar.getRules();
		Rule rule1;
		rule1.leftSide = nonTerminal;
		rule1.rightSide = std::vector<Symbol*>({ (Symbol*)nonTerminal, (Symbol*)grammar.getStart() });
		Rule rule2;
		rule2.leftSide = nonTerminal;
		rule2.rightSide = std::vector<Symbol*>({ (Symbol*)EmptyWord::getInstance() });

		newRules.push_back(rule1);
		newRules.push_back(rule2);
		newGrammar.setRules(newRules);
		newGrammar.setStart(nonTerminal);
		return newGrammar;
	}

}