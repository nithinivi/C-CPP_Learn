#include "MVector.h"
#include <stdexcept>
#include <initializer_list>

using namespace std;

MVector::MVector(int s)
{
	if (s < 0) throw std::length_error("");
	elem = new double[s];
	sz = s;

}

MVector::MVector(std::initializer_list<double> lst)
	:elem{ new double[lst.size()] }, sz{ lst.size() }

{
	copy(lst.begin(), lst.end(), elem);

}

MVector::~MVector()
{
	delete[] elem;
}

double& MVector::operator[](int i)
{
	if (i < 0 || size() <= i) throw std::out_of_range("Vector::operator[]");

	return elem[i];
}


MVector::MVector(const MVector& a)
	:elem{ new double[sz] },
	sz{ a.sz }
{
	for (size_t i = 0; i < sz; i++)

		elem[i] = a.elem[i];
}

MVector& MVector::operator=(const MVector& a)
{
	double* p = new double[a.sz];
	for (size_t i = 0; i < a.sz; i++)
		p[i] = a.elem[i];
	delete elem;
	elem = p;
	sz = a.sz;
	return *this;
}


MVector::MVector(MVector&& a)
	:elem{a.elem},
	sz{a.sz}
{
	a.elem = nullptr;
	a.sz = 0;

}

MVector& MVector::operator=(MVector&& a)
{
	return a;
}

size_t MVector::size()
{
	return sz;
}
