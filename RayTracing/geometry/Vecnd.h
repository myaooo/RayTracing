#ifndef Vecnd_H
#define Vecnd_H

#include "Num.h"
#include <cassert>

namespace MyMath
{
	using std::numeric_limits;
	template <unsigned dim>
    class Vecnd
    {
	public:
		//Data field
		double _p[dim];

    public:

        //Constructors
        Vecnd();
        Vecnd(double x, ...);
        Vecnd(const Vecnd<dim>& v);
		Vecnd(double x[]);
        //Deconstructor
        ~Vecnd();
    public:
        //Operators

        //Operator []
        inline double& operator [](unsigned index)
        {
            assert(index<dim);
            return _p[index];
        }
        inline const double& operator [](unsigned index) const
        {
            assert(index<dim);
            return _p[index];
        }

		//Operator ()
		inline double& operator ()(unsigned index)
		{
			assert(index < dim);
			return _p[index];
		}
		inline const double& operator ()(unsigned index) const
		{
			assert(index < dim);
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

		// static generator
		static inline Vecnd<dim> max(){
			return Vecnd<dim>::Vecnd(MAXNUM,MAXNUM,MAXNUM);
		}

		static inline Vecnd<dim> min(){
			return Vecnd<dim>::Vecnd(MAXNUM,MAXNUM,MAXNUM);
		}

    public:
        void Normalize();
        double L2Norm_Sqr();
    };

	typedef Vecnd<3> Vec3d;
	typedef Vecnd<4> Vec4d;
}

#endif
