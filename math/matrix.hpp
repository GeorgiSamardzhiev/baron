#include "../functional/higher_order.hpp"
#include <vector>
#include <ostream>
#include <iostream>

namespace baron {
	template <typename T>
	class Matrix {
	private:
		using Table = std::vector<std::vector<T>>;

		Table table;
	public:
		Matrix(unsigned short i = 5, unsigned short j = 5) : table(std::vector<std::vector<T>>(i, std::vector<T>(j))) { }
		Matrix(const Table& table) {
			this->table = table;
		}

		Table getTable() const {
			return this->table;
		}

		void setTable(const Table& other) {
			this->table = other.table;
		}

		void setElement(const T& element, unsigned short i, unsigned short j) {
			this->table[i][j] = element;
		}

		Matrix operator+(const Matrix& other) const {
			int sizeI = table.size(), sizeJ = table[0].size();
			if (sizeI != other.table.size() || sizeJ != other.table.size()) {
				throw "Cannot sum matrices with diffrent dimensions";
			}
			Matrix res(sizeI, table[0].size());
			for (int i = 0; i < sizeI; i++) {
				res[i] = zipWith(this->table[i], other.table[i], [](const T& a, const T& b) { return a + b; });
			}
			return res;
		}

		Matrix operator-(const Matrix& other) const {
			int sizeI = table.size(), sizeJ = table[0].size();
			if (sizeI != other.table.size() || sizeJ != other.table.size()) {
				throw "Cannot subtract matrices with diffrent dimensions";
			}
			Matrix res(sizeI, table[0].size());
			for (int i = 0; i < sizeI; i++) {
				res[i] = zipWith(this->table[i], other.table[i], [](const T& a, const T& b) { return a - b; });
			}
			return res;
		}

		Matrix operator*(const Matrix& other) const {
			int thisSizeI = this->table.size(), thisSizeJ = this->table[0].size(),
				otherSizeI = other.table.size(), otherSizeJ = other.table[0].size();

			if (thisSizeJ != otherSizeI) {
				throw "Cannot multiply this matrices";
			}
			Matrix res(thisSizeI, otherSizeJ);

			for (int i = 0; i < thisSizeI; i++) {
				for (int j = 0; j < otherSizeJ; j++) {

					for (int k = 0; k < thisSizeJ; k++) {
						res.table[i][j] += this->table[i][k] * other.table[k][j];
					}

				}
			}

			return res;
		}

		Matrix calcInverse() const;

		T calcDeterminant() const {
			int size = this->table.size();
			if (size != this->table[0].size()) {
				throw "Non square matrices does not have determinants";
			}
			if (size == 1) {
				return this->table[0][0];
			}
			Matrix copy = *this;
			unsigned short k = 0;
			for (int i = 1; i < size; i++) {
				for (int l = i; l < size; l++) {
					if (copy.table[i - 1][k] == 0) {
						continue;
					}
					auto row = map(copy.table[i - 1], [copy, k, l, i](const T& elem) { return elem * copy.table[l][k] / copy.table[i - 1][k]; });
					for (int j = 0; j < size; j++) {
						copy.table[l][j] = copy.table[l][j] - row[j];
					}
					if (accumulate(false, copy.table[l], [](bool base, const T& elem) { return base && elem == 0; })) {
						return 0;
					}
				}
				++k;
			}
			T res = copy.table[0][0];
			for (int i = 1; i < size; i++) {
				res *= copy.table[i][i];
			}
			return res;
		}

		Matrix calcTranspose() const {
			int sizeI = this->table.size(), sizeJ = this->table[0].size();
			Matrix res(sizeJ, sizeI);
			for (int i = 0; i < sizeI; i++) {
				for (int j = 0; j < sizeJ; j++) {
					res.table[j][i] = this->table[i][j];
				}
			}
			return res;
		}

		std::vector<T>& operator[](unsigned short i) {
			return this->table[i];
		}
	};

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
		auto table = matrix.getTable();
		int sizeI = table.size(), sizeJ = table[0].size();
		for (int i = 0; i < sizeI; i++) {
			for (int j = 0; j < sizeJ; j++) {
				os << table[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}

}