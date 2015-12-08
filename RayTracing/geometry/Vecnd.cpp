#include "Vecnd.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cstdarg>

namespace MyMath
{

//////////////////////////////////////////////////////////////////////////
//  Constructors and Deconstructors
	template<unsigned dim>
	Vecnd<dim>::Vecnd() :_len(dim)
    {
        memset(_p,0,sizeof(double)*_len);
    }

	template<unsigned dim>
	Vecnd<dim>::Vecnd(double x, ...) : _len(dim){
		va_list arg_ptr;
		va_start(arg_ptr, x);
		for (int i = 0; i < _len; ++i)
			_p[i] = va_arg(arg_ptr, double);
		va_end(arg_ptr);
	}

    template<unsigned dim>
	Vecnd<dim>::Vecnd(const Vecnd<dim> &v) : _len(dim)
    {
        memcpy(_p,v._p,sizeof(double)*_len);
    }
	template<unsigned dim>
    Vecnd<dim>::~Vecnd()
    {
		delete _p;
    }

//////////////////////////////////////////////////////////////////////////
// Operators

	template<unsigned dim>
	Vecnd<dim>& Vecnd<dim>::operator =( const Vecnd<dim>& v)
    {
        memcpy(_p,v._p,sizeof(double)*_len);        
        return (*this);
    }

	template<unsigned dim>
    void Vecnd<dim>::operator +=(const Vecnd<dim>& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] += v._p[i];
    }
	template<unsigned dim>
    void Vecnd<dim>::operator +=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] += f;
    }

	template<unsigned dim>
    void Vecnd<dim>::operator -=(const Vecnd<dim>& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= v._p[i];
    }
	template<unsigned dim>
    void Vecnd<dim>::operator -=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= f;
    }

	template<unsigned dim>
    void Vecnd<dim>::operator *=(const Vecnd<dim>& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= v._p[i];
    }
	template<unsigned dim>
    void Vecnd<dim>::operator *=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= f;
    }

	template<unsigned dim>
    void Vecnd<dim>::operator /=(const Vecnd<dim>& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= v._p[i];
    }
	template<unsigned dim>
    void Vecnd<dim>::operator /=(double f)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= f;
    }

	template<unsigned dim>
    Vecnd<dim> Vecnd<dim>::operator +(const Vecnd<dim>&v) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + v[i];
        return res;
    }

	template<unsigned dim>
    Vecnd<dim> Vecnd<dim>::operator +(double f) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + f;
        return res;
    }

	template<unsigned dim>
    Vecnd<dim> Vecnd<dim>::operator -(const Vecnd<dim>&v) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - v[i];
        return res;
    }
	template<unsigned dim>
    Vecnd<dim> Vecnd<dim>::operator -(double f) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - f;
        return res;
    }

	template<unsigned dim>
    Vecnd<dim> Vecnd<dim>::operator *(const Vecnd<dim>&v) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * v[i];
        return res;
    }
	template<unsigned dim>
    Vecnd<dim> Vecnd<dim>::operator *(double f) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * f;
        return res;
    }

	template<unsigned dim>
	Vecnd<dim> Vecnd<dim>::operator /(const Vecnd<dim>&v) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / v[i];
        return res;
    }
	template<unsigned dim>
	Vecnd<dim> Vecnd<dim>::operator /(double f) const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / f;
        return res;
    }

	template<unsigned dim>
	Vecnd<dim> Vecnd<dim>::operator - () const
    {
        Vecnd<dim> res;
        for(int i=0;i<_len;i++)
            res[i] = -(*this)[i];
        return res;
    }

//////////////////////////////////////////////////////////////////////////
// Other Methods
	template<unsigned dim>
    void Vecnd<dim>::Normalize()
    {
        double fSqr = L2Norm_Sqr();
        if(fSqr>Epsilon)
            (*this) /= sqrt(fSqr);
    }

	template<unsigned dim>
    double Vecnd<dim>::L2Norm_Sqr()
    {
		double sqr = 0;
		for (int i = 0; i < _len; ++i)
			sqr += _p[i] * _p[i];
        return sqr;
    }


}


