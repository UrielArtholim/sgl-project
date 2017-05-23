#ifndef _FECHA_
#define _FECHA_
#include <ctime>
#include <iostream>
#include <cstring>
#include <stdlib.h>

class Fecha
{
public:
	static const int AnnoMinimo = 1902; //es tipo basico asi que vale aqui dentro de la clase
	static const int AnnoMaximo = 2037; //definicion inline
	class Invalida//se pueden hacer inline porque son MUY simples
	{
	public:
		Invalida(const char* mensaje)
		{
			info_ = mensaje;
		}
		const char* por_que() const
		{
			return info_;
		}

	private:
		const char* info_; //seria la misma direccion de memoria
	};
	explicit Fecha(int=0, int=0, int=0);
	Fecha(const char*);
	//Fecha(const Fecha&);

	const char* cadena() const;
	
	inline int dia() const;//{return dia_;}//es inline
	inline int mes() const;
	inline int anno() const;

	//operadores
	Fecha& operator ++(); //prefijo
	Fecha& operator --(); //prefijo
	Fecha operator ++(int); //posfijo
	Fecha operator --(int); //posfijo
	Fecha& operator +=(int numeroDias);
	Fecha& operator -=(int numeroDias);
	

private:
	int day_, month_, year_;
};

inline int Fecha::dia() const {return day_;}
inline int Fecha::mes() const {return month_;}
inline int Fecha::anno() const {return year_;}

Fecha operator +(const Fecha& fecha, int numeroDias);
Fecha operator -(const Fecha& fecha, int numeroDias);
Fecha operator +(int numeroDias, const Fecha& fecha);


bool operator ==(const Fecha& fecha1, const Fecha& fecha2);
bool operator !=(const Fecha& fecha1, const Fecha& fecha2);
bool operator <(const Fecha& fecha1, const Fecha& fecha2);
bool operator >(const Fecha& fecha1, const Fecha& fecha2);
bool operator <=(const Fecha& fecha1, const Fecha& fecha2);
bool operator >=(const Fecha& fecha1, const Fecha& fecha2);
long int operator -(const Fecha& fecha1, const Fecha& fecha2);

std::istream& operator>>(std::istream&, Fecha&);
std::ostream& operator<<(std::ostream&, const Fecha&);

int nDiasMes(int mes, int anno);


#endif