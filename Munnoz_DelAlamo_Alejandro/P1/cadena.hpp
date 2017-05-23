/* Clase Cadena */
/* Archivo HPP*/
/* Alejandro Muñoz Del Álamo Copyright 2016*/

#ifndef _CADENA_H_
#define _CADENA_H_

#include <iterator>
#include <cstring>
#include <stdexcept>
#include <functional>

class Cadena{
    public:
      static const size_t npos = -1;
      typedef char* iterator;
      typedef const char* const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      explicit Cadena (size_t tamanno = 0, char caracter = ' ');
      Cadena (const Cadena& cadenaOriginal, size_t posInicial=0, size_t longitudCopia=npos);

      Cadena (const char* charOriginal, size_t n_primeros=npos);	
      
      Cadena substr (size_t indice,size_t tamanno) const ;
      
      Cadena (Cadena&& cadenaOriginal);
      Cadena& operator = (const Cadena& cadenaOriginal);
      Cadena& operator = (const char* charOriginal);
      Cadena& operator = (Cadena&& cadenaOriginal);
      const char* c_str() const;
      
      char operator [] (size_t indice) const;
      char& operator [] (size_t indice);
      size_t length () const;
      char at (size_t indice) const;
      char& at (size_t indice);
      ~Cadena ();
      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      const_iterator cbegin() const noexcept;
      iterator end() noexcept;
      const_iterator end() const noexcept;
      const_iterator cend() const noexcept;
      reverse_iterator rbegin() noexcept;
      const_reverse_iterator rbegin() const noexcept;
      const_reverse_iterator crbegin() const noexcept;
      reverse_iterator rend() noexcept;
      const_reverse_iterator rend() const noexcept;
      const_reverse_iterator crend() const noexcept;

    private:
	size_t tamanno_;
	char* cadena_;
};

Cadena& operator += (Cadena& operando1, const Cadena& operando2);
Cadena operator + (const Cadena& operando1, const Cadena& operando2);
bool operator == (const Cadena& operando1, const Cadena& operando2);
bool operator != (const Cadena& operando1, const Cadena& operando2);
bool operator > (const Cadena& operando1, const Cadena& operando2);
bool operator < (const Cadena& operando1, const Cadena& operando2);
bool operator >= (const Cadena& operando1, const Cadena& operando2);
bool operator <= (const Cadena& operando1, const Cadena& operando2);
std::ostream& operator << (std::ostream& os,const Cadena& cad);
std::istream& operator >> (std::istream& is,Cadena& cad);

/* Para P2 y siguientes */

namespace std
{
      template <> struct hash<Cadena>
      {
            size_t operator()(const Cadena& cad) const
            {
                  return hash<string>{}(cad.c_str());
            }
      };
}

#endif //_CADENA_H_
