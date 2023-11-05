/*
	һ���򵥵ľ�����
	���ߣ�jyl
*/
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
#include <cmath>

class Matrix {
private:
	int rows, columns;		//������к���
	double** value;			//�����ֵ
	void initialization();	//��ʼ����Ϊ���󿪱��ڴ�ռ�

public:
	Matrix(int row, int col, int init_value = 0);	//���캯��
	Matrix(int row);		//���ɵ�λ����
	virtual ~Matrix();		//��������
	Matrix(const Matrix& p);	//�������캯��

	int get_rows()const;		//��þ�������
	int get_columns()const;	//��þ�������

	friend std::istream& operator>>(std::istream&, const Matrix&);	//������
	friend std::ostream& operator<<(std::ostream&, const Matrix&);	//�����

	Matrix& operator=(const double* arr);		//�����������ֵ��Ҫ������Ѿ������С
	Matrix& operator=(const Matrix& p);		//����丳ֵ

	//���жϼ����Ƿ�Ϸ������Ϸ����˳�����
	Matrix operator+(const Matrix&);		//����ӷ�
	Matrix operator-(const Matrix&);		//�������
	Matrix operator*(const Matrix&);		//����˷�
	
	Matrix pow(int);		//��������

	//�������б任���±��Ǵ�0��ʼ��
	//���Ϸ������з�Χ�Ǵ�0 ~ rows-1/columns-1
	void add_row(int row1, int row2, double k);		//�����б任��row1+k*row2
	void add_col(int col1, int col2, double k);		//�����б任��col1+k*col2
	void exchange_row(int row1, int row2);			//���󽻻�����
	void exchange_col(int col1, int col2);			//���󽻻�����
	void multiply_row(int row, double k);				//����һ�г���һ��ϵ��
	void multiply_col(int col, double k);				//����һ�г���һ��ϵ��
	void multiply(double k);		//�����������һ������

	double get_point(int x, int y)const;		//��þ����ض������ֵ
	double calcu_det();		//��������ʽ
	Matrix T();			//����

	void print() const;		//���������Ϣ
};

#endif // !MATRIX_H