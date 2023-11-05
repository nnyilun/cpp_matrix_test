#include "matrix.h"

void Matrix::initialization() {		//�����ʼ���������ڴ�ռ�(ȱ��newʧ�ܵ��쳣��׽)
	value = new double*[rows];
	for (int i = 0; i < rows; i++) {
		value[i] = new double[columns];
	}
}

Matrix::Matrix(int row, int col, int init_value) {	//���캯����init_valueĬ��Ϊ0
	rows = row;
	columns = col;
	initialization();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			value[i][j] = init_value;
		}
	}
}

Matrix::Matrix(int row) {		//���ɵ�λ����
	rows = row;
	columns = row;
	initialization();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == j) value[i][j] = 1;
			else value[i][j] = 0;
		}
	}
}

Matrix::~Matrix() {		//��������
	for (int i = 0; i < rows; i++) {
		delete[] value[i];
	}
	delete[] value;
}

Matrix::Matrix(const Matrix& p) {	//�������캯��
	rows = p.rows;
	columns = p.columns;
	initialization();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			value[i][j] = p.value[i][j];
		}
	}
}

int Matrix::get_rows()const {	//��þ�������
	return this->rows;
}
int Matrix::get_columns()const {	//��þ�������
	return this->columns;
}

void Matrix::print() const {	//���
	std::cout << "Matrix--  rows: " << rows << " columns: " << columns << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << std::setprecision(8) << value[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}


std::istream& operator>>(std::istream& is, const Matrix& p) {	//��������
	for (int i = 0; i < p.rows; i++) {
		for (int j = 0; j < p.columns; j++) {
			is >> p.value[i][j];
		}
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Matrix& p) {	//�������
	//os << "Matrix--  rows: " << p.rows << " columns: " << p.columns << std::endl;
	for (int i = 0; i < p.rows; i++) {
		for (int j = 0; j < p.columns; j++) {
			os << std::setprecision(8) << p.value[i][j] << "  ";
		}
		os << std::endl;
	}
	return os;
}

Matrix& Matrix::operator=(const double* arr) {	//�����������������ֵ
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			value[i][j] = *(arr + i * columns + j);
		}
	}
	return *this;
}

Matrix& Matrix::operator=(const Matrix& p) {	//����丳ֵ
	if (this == &p)return *this;

	if (this->rows != p.rows || this->columns != p.columns) {
		std::cout << "operator \"=\" should be used for the same shape matrix!" << std::endl;
		exit(-1);
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			this->value[i][j] = p.value[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& p) {		//����ӷ������ж������Ƿ�Ϸ�
	if (rows != p.rows || columns != p.columns) {
		std::cout << "operator \"+\" should be used for the same shape matrix!" << std::endl;
		exit(-1);
	}

	Matrix temp(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			temp.value[i][j] = value[i][j] + p.value[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& p) {		//������������ж������Ƿ�Ϸ�
	if (rows != p.rows || columns != p.columns) {
		std::cout << "operator \"-\" should be used for the same shape matrix!" << std::endl;
		exit(-1);
	}

	Matrix temp(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			temp.value[i][j] = value[i][j] - p.value[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& p) {		//����˷������ж������Ƿ�Ϸ�
	if (p.rows != columns) {
		std::cout << "operator \"*\" should be used for rows and columns matching matrices!" << std::endl;
		exit(-1);
	}

	Matrix temp(rows, p.columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < p.columns; j++) {
			for (int k = 0; k < columns; k++) {
				temp.value[i][j] += this->value[i][k] * p.value[k][j];
			}
		}
	}
	return temp;
}

Matrix Matrix::pow(int p) {
	if (rows != columns) {
		std::cout << "the rows and columns are different!can't compute powers!" << std::endl;
		exit(-1);
	}
	if (p <= 0) {
		std::cout << "the parameter should be a positive integer!" << std::endl;
		exit(-1);
	}

	Matrix temp(*this);
	for (int i = 0; i < p - 1; i++) {
		temp = temp * (*this);
	}

	return temp;
}

void Matrix::add_row(int row1, int row2, double k) {		//�����б任��row1+k*row2
	if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
		std::cout << "illegal row!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < columns; i++) {
		value[row1][i] += value[row2][i] * k;
	}
}

void Matrix::add_col(int col1, int col2, double k) {		//�����б任��col1+k*col2
	if (col1 < 0 || col1 >= columns || col2 < 0 || col2 >= columns) {
		std::cout << "illegal column!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < rows; i++) {
		value[i][col1] += value[i][col2] * k;
	}
}
void Matrix::exchange_row(int row1, int row2) {			//���󽻻�����
	if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
		std::cout << "illegal row!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < columns; i++) {
		int temp = value[row1][i];
		value[row1][i] = value[row2][i];
		value[row2][i] = temp;
	}
}
void Matrix::exchange_col(int col1, int col2) {			//���󽻻�����
	if (col1 < 0 || col1 >= columns || col2 < 0 || col2 >= columns) {
		std::cout << "illegal column!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < rows; i++) {
		int temp = value[i][col1];
		value[i][col1] = value[i][col2];
		value[i][col2] = temp;
	}
}
void Matrix::multiply_row(int row, double k) {				//����һ�г���һ��ϵ��
	if (row < 0 || row >= rows) {
		std::cout << "illegal row!" << std::endl;
		exit(-1);
	}
	if (k == 0) {
		std::cout << "the coefficients cannot be zero!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < columns; i++) {
		value[row][i] *= k;
	}
}
void Matrix::multiply_col(int col, double k) {				//����һ�г���һ��ϵ��
	if (col < 0 || col >= columns) {
		std::cout << "illegal column!" << std::endl;
		exit(-1);
	}
	if (k == 0) {
		std::cout << "the coefficients cannot be zero!" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < rows; i++) {
		value[i][col] *= k;
	}
}

void Matrix::multiply(double k) {
	if (k == 0) {
		std::cout << "the parameter should not be zero!" << std::endl;
		exit(-1);
	}

	for (int i = 0; i < rows; i++) {
		this->multiply_row(i, k);
	}
}

double Matrix::get_point(int x, int y)const {
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		std::cout << "access to the overflow!" << std::endl;
		exit(-1);
	}

	return this->value[x][y];
}

double Matrix::calcu_det() {		//��������ʽ
	if (rows != columns) {
		std::cout << "the number of rows and columns of a determinant should be equal!" << std::endl;
		exit(-1);
	}

	if (rows == 1)return value[0][0];
	double result = 1;
	Matrix temp(*this);
	for (int i = 0; i < rows - 1; i++) {
		result *= temp.value[i][i];
		temp.multiply_row(i, 1.0 / temp.value[i][i]);
		for (int j = i + 1; j < rows; j++) {
			temp.add_row(j, i, -temp.value[j][i]);
		}
	}

	for (int i = 0; i < rows; i++) {
		result *= temp.value[i][i];
	}
	return result;
}

Matrix Matrix::T() {
	Matrix temp(columns, rows);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			temp.value[i][j] = value[j][i];
		}
	}
	return temp;
}

