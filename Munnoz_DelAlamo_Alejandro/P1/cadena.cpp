/* Clase Cadena */
/* Archivo CPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017*/
#include "cadena.hpp"

//Clase Cadena -----------------------------------------------------------------------------------------------------------

Cadena::Cadena (size_t tamanno, char caracter):
    cadena_(new char[(tamanno_ = tamanno)+1])
{
    for(size_t i=0; i<tamanno; ++i)
        cadena_[i] = caracter;
    cadena_[tamanno_] = '\0';
}

Cadena::Cadena (const Cadena& cadenaOriginal,size_t posInicial,
                        size_t longitudCopia)
{
    if (posInicial>cadenaOriginal.tamanno_)
        throw std::out_of_range("Indice inicio superior al tamanno de la cadena.");
    
    if(longitudCopia >=cadenaOriginal.tamanno_ || (posInicial+longitudCopia) >= cadenaOriginal.tamanno_)//Controlamos el 3er parametro.
          cadena_ = new char[(tamanno_ = cadenaOriginal.tamanno_-posInicial)+1];
            //Definimos la cadena y su tamanno.   
    else
          cadena_ = new char[(tamanno_ = longitudCopia)+1];

    for(size_t i=0; i<tamanno_; ++i)
    cadena_[i] = cadenaOriginal.cadena_[posInicial+i];
    // Hasta tamanno_ desde 0
    cadena_[tamanno_] = '\0';      
}

   
Cadena::Cadena (Cadena&& cadenaOriginal): tamanno_ (cadenaOriginal.tamanno_), cadena_(cadenaOriginal.cadena_)
{
    cadenaOriginal.cadena_ = new char[1];
    cadenaOriginal.cadena_[0]='\0';
    cadenaOriginal.tamanno_ = 0;
}

Cadena::Cadena (const char* charOriginal, size_t n_primeros)
{   
   
    if(n_primeros >= strlen(charOriginal)) 
        tamanno_ = strlen(charOriginal);
    else
        tamanno_ = n_primeros;
    
    cadena_ = new char[tamanno_+1];
    for(int i=0; i<tamanno_; ++i)
        cadena_[i] = charOriginal[i];
    
    cadena_[tamanno_] = '\0';
}  
  
Cadena& Cadena::operator = (const Cadena& cadenaOriginal) 
{
    if (this != &cadenaOriginal)//Evitamos autoasignación 
    {
        if( tamanno_ != cadenaOriginal.tamanno_)
        {
            delete[] cadena_;
        tamanno_ = cadenaOriginal.tamanno_;
        cadena_ = new char[tamanno_+1];
        }
        strcpy(cadena_,cadenaOriginal.cadena_);
    }
    return *this;
}

Cadena& Cadena::operator = (const char* charOriginal) 
{
    if (tamanno_ != strlen(charOriginal))
    {
        delete[] cadena_;
        tamanno_ = strlen(charOriginal);
        cadena_ = new char[tamanno_+1];
    }
    strcpy(cadena_,charOriginal);
    return *this;
}

Cadena& Cadena::operator = (Cadena&& cadenaOriginal) 
{
    if (this != &cadenaOriginal) 
    {
    	delete[] cadena_;
        cadena_ = cadenaOriginal.cadena_;
        tamanno_ = cadenaOriginal.tamanno_;
        cadenaOriginal.cadena_ = new char[1];
        cadenaOriginal.cadena_[0]='\0';
        cadenaOriginal.tamanno_ = 0;
    }
    return *this;
}

size_t Cadena::length() const
{
    return tamanno_;
}

char& Cadena::at (size_t indice)
{
    if (indice < tamanno_) 
        return cadena_[indice];
    else
        throw std::out_of_range("Fuera de rango.");
}

char Cadena::at (size_t indice) const
{
    if (indice < tamanno_) 
        return cadena_[indice];
    else
        throw std::out_of_range("Fuera de rango.");
}

Cadena Cadena::substr (size_t indice, size_t longitud) const
{
    if( indice >= tamanno_ )
	throw std::out_of_range ("Indice superior al tamanno de la cadena.");
    if( longitud >= tamanno_-indice) 
	throw std::out_of_range ("El indice mas el tamanno supera el tamanno de la cadena.");

    Cadena cadenaAuxiliar(longitud);
    for (size_t i=0; i<longitud; i++)
	cadenaAuxiliar[i]=cadena_[i+indice];
    
    cadenaAuxiliar[longitud]='\0'; 
    return cadenaAuxiliar;
}

const char* Cadena::c_str() const
{
    return cadena_;
}

char Cadena::operator[] (size_t indice) const{return cadena_[indice];}

char& Cadena::operator[] (size_t indice){return cadena_[indice];}

Cadena::~Cadena(){delete[] cadena_;}

Cadena& operator +=(Cadena& operando1, const Cadena& operando2) 
{
	operando1 = operando1 + operando2;
	return operando1;
}

Cadena operator +(const Cadena& operando1, const Cadena& operando2)
{
    char* resultado = new char[operando1.length()+operando2.length()+1];
    strcpy(resultado,operando1.c_str());
    strcat(resultado,operando2.c_str());
    Cadena cadena_resultado(resultado);
    delete[] resultado;
    return cadena_resultado;
}

bool operator == (const Cadena& operando1, const Cadena& operando2)
{
    return !strcmp(operando1.c_str(),operando2.c_str());
}

bool operator != (const Cadena& operando1, const Cadena& operando2)
{
    return strcmp(operando1.c_str(),operando2.c_str());
}

bool operator > (const Cadena& operando1, const Cadena& operando2)
{
    return ( strcmp(operando1.c_str(),operando2.c_str()) > 0 );
}

bool operator < (const Cadena& operando1, const Cadena& operando2)
{
    return ( strcmp(operando1.c_str(),operando2.c_str()) < 0 );
}

bool operator >= (const Cadena& operando1, const Cadena& operando2)
{
    return !( operando1<operando2 );
}

bool operator <= (const Cadena& operando1, const Cadena& operando2)
{
    return !(operando1>operando2);
}

std::ostream& operator << (std::ostream& os,const Cadena& cad)
{
    os << cad.c_str();
    return os;
}

std::istream& operator >> (std::istream& is,Cadena& cad) 
{
  char palabra[32]="";
  is.width(32);
  is>>palabra;
  cad = palabra;
  return is;
}

Cadena::iterator Cadena::begin() noexcept{return cadena_;}

Cadena::const_iterator Cadena::begin() const noexcept{return cadena_;}

Cadena::const_iterator Cadena::cbegin() const noexcept{return cadena_;}

Cadena::iterator Cadena::end() noexcept{return (cadena_+tamanno_);}

Cadena::const_iterator Cadena::end() const noexcept{return (cadena_+tamanno_);}

Cadena::const_iterator Cadena::cend() const noexcept{return (cadena_+tamanno_);}

Cadena::reverse_iterator Cadena::rbegin() noexcept{return reverse_iterator(end());}

Cadena::const_reverse_iterator Cadena::rbegin() const noexcept{return const_reverse_iterator(cend());}

Cadena::const_reverse_iterator Cadena::crbegin() const noexcept{return const_reverse_iterator(cend());}

Cadena::reverse_iterator Cadena::rend() noexcept{return reverse_iterator(begin());}

Cadena::const_reverse_iterator Cadena::rend() const noexcept{return const_reverse_iterator(cbegin());}

Cadena::const_reverse_iterator Cadena::crend() const noexcept{return const_reverse_iterator(cbegin());}

