#include "fecha.hpp"

Fecha::Fecha(int d, int m, int y) : day_(d), month_(m), year_(y)
{

	if(day_==0 || month_==0 || year_==0)
	{
		std::time_t tiempo_calendario = std::time(nullptr);
		std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
		if(day_==0) day_ = tiempo_descompuesto->tm_mday;
		if(month_==0) month_ = tiempo_descompuesto->tm_mon +1;
		if(year_==0) year_ = tiempo_descompuesto->tm_year + 1900;
	}

	if(year_<AnnoMinimo || year_>AnnoMaximo)
		throw Invalida("El anno esta fuera de rango.");
	
	else if(month_<1 || month_>12)
		throw Invalida("El mes esta fuera de rango.");
	
	else if(day_<1 || day_>nDiasMes(month_,year_))
		throw Invalida("El dia esta fuera de rango.");
}

Fecha::Fecha(const char* cadena)
{
	int d, m, y;
	if(sscanf(cadena,"%d/%d/%d",&d,&m,&y)!=3)
	{
		throw Invalida("La cadena de caracteres introducida no cumple el formato dia/mes/anno");
	}
	*this = Fecha(d,m,y);
}

Fecha& Fecha::operator ++()
{
    return (*this) += 1;
}

Fecha& Fecha::operator --()
{
    return (*this +=(-1));
}

Fecha Fecha::operator ++(int)
{
    Fecha devolverFecha(*this);
    *this += 1;
    return devolverFecha;
}

Fecha Fecha::operator --(int)
{
    Fecha devolverFecha(*this);
    *this -= 1;
    return devolverFecha;
}

Fecha& Fecha::operator +=(int numeroDias)
{
	tm fecha_struct = { 0,0,0,day_+numeroDias,month_-1,year_-1900,0,0,0 };

	if(std::mktime(&fecha_struct) == -1) throw Invalida("error de mktime en +=");
	day_ = fecha_struct.tm_mday;
	month_ = fecha_struct.tm_mon+1;
	year_ = fecha_struct.tm_year+1900;
	if(year_>AnnoMaximo || year_<AnnoMinimo) throw Invalida("fecha fuera de rango en +-=");

    return *this;
}

Fecha& Fecha::operator -=(int numeroDias)
{
	return operator +=(-numeroDias);
}

Fecha operator +(const Fecha& fecha, int numeroDias)
{
	return Fecha(fecha) += numeroDias;
}

Fecha operator +(int numeroDias, const Fecha& fecha)
{
	return Fecha(fecha)+= numeroDias;
}


Fecha operator -(const Fecha& fecha, int numeroDias)
{
	return Fecha(fecha) += -numeroDias;
}

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

long int operator -(const Fecha& fecha1, const Fecha& fecha2)
{
	tm fecha_struct1 = {0,0,0,fecha1.dia(),fecha1.mes()-1,fecha1.anno()-1900,0,0,0 };
	tm fecha_struct2 = {0,0,0,fecha2.dia(),fecha2.mes()-1,fecha2.anno()-1900,0,0,0 };
	long int segundosF1 = std::mktime(&fecha_struct1);
	long int segundosF2 = std::mktime(&fecha_struct2);

	return std::difftime(segundosF1,segundosF2)/86400;
}

bool operator ==(const Fecha& fecha1, const Fecha& fecha2)
{
	return((fecha1.dia() == fecha2.dia()) && (fecha1.mes() == fecha2.mes()) && (fecha1.anno() == fecha2.anno()));
}

bool operator !=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1==fecha2);
}

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

bool operator >(const Fecha& fecha1, const Fecha& fecha2)
{
	return (fecha2<fecha1);
}

bool operator <=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha2<fecha1);
}

bool operator >=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1<fecha2);
}

std::istream& operator >> (std::istream& is, Fecha& fecha)
{
	try
	{
		char cadena[11] = "0/0/0";
    	is.width(11); // esto limita la lectura a 10 caracteres.
    	is >> cadena;
    	fecha = Fecha(cadena);  // estoy haciendo una llamada anónima al constructor, es mas eficiente que crear una variable Fecha.
    	return is;
	}
	catch(const Fecha::Invalida&)
	{
		// Modificar cin para indicar que está en fallo
		/*std::cout << "fecha::dia() = " << fecha.dia() << std::endl
				  << "fecha::mes() = " << fecha.mes() << std::endl
				  << "fecha::anno() = " << fecha.anno() << std::endl;*/
		//std::cin.clear();
		is.setstate(std::ios::failbit);
		throw;
	}	
}

std::ostream& operator << (std::ostream& os,const Fecha& fecha)
{
    return os<<fecha.cadena();
}

bool esBisiesto(int year)
{
	return (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0));
}

int nDiasMes(int mes, int anno)
{
	static const int diasdelmes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	if(mes==2 && esBisiesto(anno))
		return 29;
	else
		return diasdelmes[mes];
}


bool esValida(const Fecha& laFecha)
{
	return (laFecha.anno()>=Fecha::AnnoMinimo && laFecha.anno()<=Fecha::AnnoMaximo);
}

/*void comprobar(const fecha& fecha, const int dias)
{

	int sig_mes = fecha.mes()+1;
	int sig_anno = fecha.anno();
	if (fecha.mes() == 12)
	{
		sig_mes = 1;
		sig_anno = fecha_anno()+1;
	}

	if (fecha.dia()+dias > nDiasMes(fecha.mes(),fecha.anno()))
		fecha.day_= (fecha.day+dias)%nDiasmes(sig_mes, sig_anno());

}*/
