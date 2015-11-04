#ifndef Vecnd_H
#define Vecnd_H

#include "Num.h"
#include <cassert>


namespace MyMath
{
	template <unsigned dim>
    class Vecnd
    {
	public:
		//Data field
		struct{
			double _p[dim];
		};
		unsigned _len;

    public:

        //Constructors
        Vecnd();
        Vecnd(double x, ...);
        Vecnd(const Vecnd<dim>& v);
        //Deconstructor
        ~Vecnd();
    public:
        //Operators

        //Operator []
        inline double& operator [](unsigned index)
        {
            assert(index<_len);
            return _p[index];
        }
        inline const double& operator [](unsigned index) const
        {
            assert(index<_len);
            return _p[index];
        }

		//Operator ()
		inline double& operator ()(unsigned index)
		{
			assert(index < _len);
			return _p[index];
		}
		inline const double& operator ()(unsigned index) const
		{
			assert(index < _len);
			return _p[index];
		}
        
        //Operator =
        Vecnd<dim>& operator = (const Vecnd<dim>& v);

        //Operators +=,-=, *=, /=
        void operator +=(const Vecnd<dim> & v);
        void operator +=(double f);
        void operator -=(const Vecnd<dim> & v);
        void operator -=(double f);
        void operator *=(const Vecnd<dim> & v);
        void operator *=(double f);
        void operator /=(const Vecnd<dim> & v);
        void operator /=(double f);

        //Operators +,-.*,/
        Vecnd<dim> operator +(const Vecnd<dim> &v) const;
        Vecnd<dim> operator +(double f) const;
        Vecnd<dim> operator -(const Vecnd<dim> &v) const;
        Vecnd<dim> operator -(double f) const;
        Vecnd<dim> operator *(const Vecnd<dim> &v) const;
        Vecnd<dim> operator *(double f) const;
        Vecnd<dim> operator /(const Vecnd<dim> &v) const;
        Vecnd<dim> operator /(double f) const;

        Vecnd<dim> operator -() const;
        
    public:
        void Normalize();
        double L2Norm_Sqr();       
    };

	typedef Vecnd<3> Vec3d;
	typedef Vecnd<4> Vec4d;
}

#endif