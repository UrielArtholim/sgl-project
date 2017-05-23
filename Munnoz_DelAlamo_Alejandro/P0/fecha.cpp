/* 
 	* Práctica 0: Fecha 
	* POO 2016-2017
	* Fecha.cpp
	* Copyright © Alejandro Muñoz Del Álamo  2017
 	*/ 

#include "fecha.hpp"

// Constructores
Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a)
{
	/* Obtener fecha del sistema SÓLO cuando al menos un atributo es 0 */
	/* if(dia_ == 0 || mes_ ==0 || anno_ == 0) */
	if(dia_ == 0 || mes_ ==0 || anno_ == 0)
	{
		std::time_t tiempo_calendario = std::time(nullptr);
		std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
		if(dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;
		if(mes_ == 0) mes_ = tiempo_descompuesto->tm_mon +1;
		if(anno_ == 0) anno_ = tiempo_descompuesto->tm_anno + 1900;
	}

	/* Comprobación de la corrección de la fecha */
	/* No se comprueba en caso de tomar la fecha del sistema */
	else 
	{
		validar(*this);
	}
}

// Constructor de copia
Fecha::Fecha(const Fecha& fecha)
{
	this->dia_ = fecha.dia();
	this->mes_ = fecha.mes();
	this->anno_ = fecha.anno();
}

// Constructor de conversion
Fecha::Fecha(const char* cadena)
{
	if (this != &fecha)
	{
		this->dia_ = fecha.dia();
		this->mes_ = fecha.mes();
		this->anno_ = fecha.anno();
	}
}

// Operadores 
// Preincremento
Fecha& operator ++()
{
	return (*this)+= 1;
}

// Predecremento
Fecha& operator --()
{
	return (*this) += (-1);
}

// Postincremento
Fecha operator ++(int)
{
	Fecha devolverFecha(*this);
    *this += 1;
    return devolverFecha;
}

// Postdecremento
Fecha operator --(int)
{
	Fecha devolverFecha(*this);
    *this += (-1);
    return devolverFecha;
}

// Suma
Fecha operator +(const Fecha& fecha, int numeroDias)
{
	return Fecha(fecha) += numeroDias;
}

// Suma
Fecha operator +(int numeroDias, const Fecha& fecha)
{
	return Fecha(fecha) += numeroDias;
}

// Resta
Fecha operator -(const Fecha& fecha, int numeroDias)
{
	return Fecha(fecha) += (-numeroDias);
}

// Suma con asignación 
Fecha& Fecha::operator +=(int num)
{
	tm fecha_struct = { 0,0,0,dia_+numeroDias,mes_-1,anno_-1900,0,0,0 };

	if(std::mktime(&fecha_struct) == -1) throw Invalida("Error de mktime en +=.");
	dia_ = fecha_struct.tm_mday;
	mes_ = fecha_struct.tm_mon+1;
	anno_ = fecha_struct.tm_year+1900;
	if(anno_>AnnoMaximo || anno_<AnnoMinimo) throw Invalida("Fecha fuera de rango en anno.");

    return *this;
}

// Resta con asignación 
Fecha& Fecha::operator -=(int num)
{
	return operator +=(-numeroDias);
}

// Resta con numero de dias como entero largo sin signo	
long int Fecha::operator - (const Fecha& fecha)
{
	tm fecha_struct1 = {0,0,0,fecha1.dia(),fecha1.mes()-1,fecha1.anno()-1900,0,0,0 };
	tm fecha_struct2 = {0,0,0,fecha2.dia(),fecha2.mes()-1,fecha2.anno()-1900,0,0,0 };
	long int segundosF1 = std::mktime(&fecha_struct1);
	long int segundosF2 = std::mktime(&fecha_struct2);

	return std::difftime(segundosF1,segundosF2)/86400;
}

// Conversión implicita a cadena
const char* Fecha::cadena() const
{
	tm fecha_struct = {0,0,0,day_,month_-1,year_-1900,0,0,0 };
	static char fecha_caracteres[sizeof("miércoles 20 de septiembre de 2000")];
	static const char* const nombre_dia[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};	//mie'rcoles
	static const char* const nombre_mes[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

	std::mktime(&fecha_struct);

	sprintf(fecha_caracteres,"%s %d de %s de %d",nombre_dia[fecha_struct.tm_wday],day_,nombre_mes[fecha_struct.tm_mon],year_);

	return fecha_caracteres;
}

// Operadores de comparación

// Operador menor
bool operator <(const Fecha& fecha1, const Fecha& fecha2)
{
	bool resultado=false;

	if(fecha1.anno() < fecha2.anno())
		resultado = true;

	else if(fecha1.anno() == fecha2.anno() && fecha1.mes() < fecha2.mes())
		resultado = true;

	else if(fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() < fecha2 .dia())
		resultado = true;

	return resultado;
}

// Operador mayor
bool operator >(const Fecha& fecha1, const Fecha& fecha2)
{
	return (fecha2<fecha1);
}

// Operador menor o igual
bool operator <=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha2>fecha1);
}

// Operador mayor o igual
bool operator >=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1<fecha2);
}


// Operador igual 
bbool operator ==(const Fecha& fecha1, const Fecha& fecha2)
{
	return((fecha1.dia() == fecha2.dia()) && (fecha1.mes() == fecha2.mes()) && (fecha1.anno() == fecha2.anno()));
}

// Operador distinto
bool operator !=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1==fecha2);
}


// Función para comprobar la corrección de las fechas
bool Fecha::validar(const Fecha& fecha)
{
	if(anno_<AnnoMinimo || anno_>AnnoMaximo)
		throw Invalida("El anno esta fuera de rango.");
	
	else if(mes_<1 || mes_>12)
		throw Invalida("El mes esta fuera de rango.");
	
	else if(dia_<1 || dia_>nDiasMes(mes_,anno_))
		throw Invalida("El dia esta fuera de rango.");
}


// Función para comprobar la corrección de las fechas
bool Fecha::num_dias_mes(const int mes, const int anno)
{
	static const int dias_mes[] {0,31,28,31,30,31,30,31,31,30,31,30,31};

	if ((mes == 2 )&& (bisiesto(anno)))
		return 29;
	else
		return dias_mes[mes];
}


// Función para comprobar si el año introducido es bisiesto
bool Fecha::bisiesto(const int anno)
{
	return (anno % 4 == 0 && (anno % 400 == 0 || anno % 100 != 0));
}