/*
	一个简单的矩阵类
	作者：jyl
*/
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
#include <cmath>

class Matrix {
private:
	int rows, columns;		//矩阵的行和列
	double** value;			//矩阵的值
	void initialization();	//初始化，为矩阵开辟内存空间

public:
	Matrix(int row, int col, int init_value = 0);	//构造函数
	Matrix(int row);		//生成单位矩阵
	virtual ~Matrix();		//析构函数
	Matrix(const Matrix& p);	//拷贝构造函数

	int get_rows()const;		//获得矩阵行数
	int get_columns()const;	//获得矩阵列数

	friend std::istream& operator>>(std::istream&, const Matrix&);	//输入流
	friend std::ostream& operator<<(std::ostream&, const Matrix&);	//输出流

	Matrix& operator=(const double* arr);		//用数组给矩阵赋值，要求矩阵已经定义大小
	Matrix& operator=(const Matrix& p);		//矩阵间赋值

	//会判断计算是否合法，不合法将退出程序
	Matrix operator+(const Matrix&);		//矩阵加法
	Matrix operator-(const Matrix&);		//矩阵减法
	Matrix operator*(const Matrix&);		//矩阵乘法
	
	Matrix pow(int);		//求矩阵的幂

	//初等行列变换，下标是从0开始的
	//即合法的行列范围是从0 ~ rows-1/columns-1
	void add_row(int row1, int row2, double k);		//矩阵行变换，row1+k*row2
	void add_col(int col1, int col2, double k);		//矩阵列变换，col1+k*col2
	void exchange_row(int row1, int row2);			//矩阵交换两行
	void exchange_col(int col1, int col2);			//矩阵交换两列
	void multiply_row(int row, double k);				//矩阵一行乘上一个系数
	void multiply_col(int col, double k);				//矩阵一列乘上一个系数
	void multiply(double k);		//整个矩阵乘上一个常数

	double get_point(int x, int y)const;		//获得矩阵特定坐标的值
	double calcu_det();		//计算行列式
	Matrix T();			//矩阵

	void print() const;		//输出矩阵信息
};

#endif // !MATRIX_H