#pragma once

#include <initializer_list>

class MVector {

public:
	MVector(int s);
	MVector(std::initializer_list<double> lst);

	~MVector();
	double& operator[](int i);

	MVector(const MVector& a);  // copy ctor 
	MVector& operator=(const MVector& a);

	MVector( MVector&& a);  // copy ctor 
	MVector& operator=(MVector&& a);


	size_t size();

private:
	double* elem;
	size_t  sz;
};
