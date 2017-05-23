/* $Id: test-P0-auto.cpp 310 2016-03-31 08:42:29Z gerardo $
 * Pruebas unitarias automáticas para las clases Fecha y Cadena de la P0
 * ©2015 Los profesores de POO
 */

#include "fecha.hpp"
#include "cadena.hpp"

#include "fct.h"

#include <ctime>
#include <cstdlib>
#include <type_traits>
#include <locale>
#include <stdexcept>
#include <memory>
#include <iostream>
using namespace std;

/*
 *     Funciones y macros auxiliares
 */

#define fecha_is_eq(f, d, m, a) (f.anno() == a && f.mes() == m && f.dia() == d)

#define Fecha_chk_eq(f, d, m, a)\
  fct_xchk(\
    fecha_is_eq(f, d, m, a),\
    "failed Fecha_chk_eq:\n<%02d/%02d/%04d> != <%02d/%02d/%04d>",\
    f.dia(), f.mes(), f.anno(), d, m, a)

/* Función auxiliar para comparar una Cadena con una cadena de C;
 * compara tanto el contenido (los caracteres) como el tamaño.
 * Necesita que los 2 primeros atributos de la clase Cadena sean,
 * por este orden, el puntero y el tamaño.
 */
bool Cadenacmp(const Cadena& cad, const char* c_cad)
{
  Cadena* pc = const_cast<Cadena*>(&cad);
  struct FalsaCadena {
    char*  s;
    size_t t;
  } *pfc = reinterpret_cast<FalsaCadena*>(pc);
  return strcmp(pfc->s, c_cad) == 0 && pfc->t == strlen(c_cad);
}

#define Cadena_chk_eq(c, s) \
  fct_xchk(\
      Cadenacmp(c, s),\
      "La Cadena { \"%s\", %u } no es igual a \"%s\"\n",\
      c.operator const char*(), c.length(), s\
  );


FCT_BGN() {

/**************************************************************************
 *************************** FECHA ****************************************
 **************************************************************************/

  int annoSistema, mesSistema, diaSistema;
  bool bPrimera = true;

  // 1.º establecemos la zona horaria a UTC para evitar cosas raras
  setenv("TZ", "", 1);
  tzset();
  // y después la localización española en UTF-8
  try {
    locale::global(locale("es_ES.UTF-8"));
  }
  catch(const runtime_error& e) {
    cerr << "Parece que no tienes la localización española "
      "\"es_ES.UTF-8\". Instálala antes. El mensaje de error es:\n"
	 << e.what() << "\nFin del programa" << endl;
    return 1;
  }

  FCT_FIXTURE_SUITE_BGN(Fecha) {

    if (bPrimera) {
      cout << "\n--------------------------------"
	" Fecha -------------------------------------" << endl;
      bPrimera = false;
    }

    FCT_SETUP_BGN() {
      const time_t ahora = time(nullptr);
      const tm*    fecha = gmtime(&ahora);
      annoSistema        = 1900 + fecha->tm_year;
      mesSistema         = 1 + fecha->tm_mon;
      diaSistema         = fecha->tm_mday;
    }
    FCT_SETUP_END();

    FCT_TEARDOWN_BGN() {
    }
    FCT_TEARDOWN_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-mes-anyo; no ceros) {
      const Fecha f(18, 7, 1936);
      Fecha_chk_eq(f, 18, 7, 1936);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-mes; no ceros) {
      const Fecha f(17, 7);
      Fecha_chk_eq(f, 17, 7, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-mes-anno cero) {
      const Fecha f(3, 7, 0);
      Fecha_chk_eq(f, 3, 7, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia; no cero) {
      const Fecha f(1);
      Fecha_chk_eq(f, 1, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia; no conversion implicita) {
      bool conversion_implicita = ! is_convertible<int, Fecha>::value;
      fct_chk(conversion_implicita);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-cero) {
      const Fecha f(2, 0);
      Fecha_chk_eq(f, 2, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-cero-cero) {
      const Fecha f(2, 0, 0);
      Fecha_chk_eq(f, 2, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-cero-anno) {
      const Fecha f(3, 0, 2010);
      Fecha_chk_eq(f, 3, mesSistema, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-cero-anno) {
      const Fecha f(0, 0, 2012);
      Fecha_chk_eq(f, diaSistema, mesSistema, 2012);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-mes-anno) {
      const Fecha f(0, 5, 2000);
      Fecha_chk_eq(f, diaSistema, 5, 2000);
    }
    FCT_TEST_END();
    FCT_TEST_BGN(Fecha - Ctor.: predeterminado) {
      const Fecha hoy;
      Fecha_chk_eq(hoy, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-cero-cero) {
      const Fecha f(0, 0, 0);
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: copia) {
      const Fecha f(2, 3, 2000);
      const Fecha g(f);
      Fecha_chk_eq(f, g.dia(), g.mes(), g.anno());
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: copia trivial) {
#if __GNUC__ >= 5
      fct_chk(is_trivially_copy_constructible<Fecha>());
#endif
      fct_chk(is_nothrow_copy_constructible<Fecha>());
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena dd/mm/aaaa) {
      const Fecha f("11/09/2001");
      Fecha_chk_eq(f, 11, 9, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena d/m/aaaa) {
      const Fecha f = "1/5/2010";
      Fecha_chk_eq(f, 1, 5, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena d/m/0) {
      const Fecha f = "1/5/0";
      Fecha_chk_eq(f, 1, 5, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena d/0/aaaa) {
      const Fecha f = "1/0/2010";
      Fecha_chk_eq(f, 1, mesSistema, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/mm/aaaa) {
      const Fecha f = "0/08/2010";
      Fecha_chk_eq(f, diaSistema, 8, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena dd/0/0) {
      const Fecha f = "01/0/0";
      Fecha_chk_eq(f, 1, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/0/0) {
      const Fecha f = "0/0/0";
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/0/aaaa) {
      const Fecha f = "0/0/2012";
      Fecha_chk_eq(f, diaSistema, mesSistema, 2012);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena formato incorrecto) {
      fct_chk_ex(Fecha::Invalida, Fecha("22/03"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena sobran caracteres no numericos) {
      const Fecha f("11/09/2001)&...");
      Fecha_chk_eq(f, 11, 9, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha (31, 4));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: mes no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha (31, 13));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: anno no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha (2, 5, 1808));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor. cadena: dia invalido y Fecha::Invalida::por_que)
      try {
        Fecha f("29/2/2015");
        fct_chk(!"Se esperaba una excepción");
      } catch (const Fecha::Invalida& e) {
        fct_chk(e.por_que());
      }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor. cadena: mes no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha("1/-1/2028"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor. cadena: anno no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha("1/1/-1"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Preincremento) {
      Fecha f(31, 3, 2010);
      const Fecha g(++f);
      Fecha_chk_eq(f, 1, 4, 2010);
      Fecha_chk_eq(g, 1, 4, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Preincremento - asociatividad) {
      Fecha f(31, 3, 2010);
      const Fecha g(++++f);
      Fecha_chk_eq(f, 2, 4, 2010);
      Fecha_chk_eq(g, 2, 4, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Preincremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(31, 12, Fecha::AnnoMaximo);
		 ++f;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postincremento) {
      Fecha f(31, 3, 2010);
      const Fecha g(f++);
      Fecha_chk_eq(f, 1, 4, 2010);
      Fecha_chk_eq(g, 31, 3, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postincremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(31, 12, Fecha::AnnoMaximo);
		 f++;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Predecremento) {
      Fecha f(1, 1, 2010);
      const Fecha g(--f);
      Fecha_chk_eq(f, 31, 12, 2009);
      Fecha_chk_eq(g, 31, 12, 2009);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Predecremento - asociatividad) {
      Fecha f(1, 1, 2010);
      const Fecha g(----f);
      Fecha_chk_eq(f, 30, 12, 2009);
      Fecha_chk_eq(g, 30, 12, 2009);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Predecremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(1, 1, Fecha::AnnoMinimo);
		 --f;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postdecremento) {
      Fecha f(1, 1, 2010);
      const Fecha g(f--);
      Fecha_chk_eq(f, 31, 12, 2009);
      Fecha_chk_eq(g, 1, 1, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postdecremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(1, 1, Fecha::AnnoMinimo);
		 f--;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma de dias - fecha + dias) {
      const Fecha f(30, 4, 2003);
      const Fecha g(f + 10);
      Fecha_chk_eq(g, 10, 5, 2003);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma de dias - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 const Fecha f(31, 12, Fecha::AnnoMaximo);
		 f + 7;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta de dias - fecha - dias) {
      const Fecha f(1, 4, 2008);
      const Fecha g(f - 10);
      Fecha_chk_eq(g, 22, 3, 2008);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta de dias - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(1, 1, Fecha::AnnoMinimo);
		 f - 3;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma con asignacion) {
      Fecha f(5, 5, 2005);
      f += 3;
      Fecha_chk_eq(f, 8, 5, 2005);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma con asignacion - asociatividad) {
      Fecha f(5, 5, 2005);
      (f += 3) += 2;
      Fecha_chk_eq(f, 10, 5, 2005);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma con asignacion: fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(31, 12, Fecha::AnnoMaximo);
		 f += 2;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta con asignacion) {
      Fecha f(2, 1, 2010);
      f -= 2;
      Fecha_chk_eq(f, 31, 12, 2009);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta con asignacion - asociatividad) {
      Fecha f(2, 7, 2010);
      (f -= 2) -= 5;
      Fecha_chk_eq(f, 25, 6, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta con asignacion: fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida,
		 Fecha f(1, 1, Fecha::AnnoMinimo);
		 f -= 2;);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Asignacion entre fechas) {
      const Fecha f(1, 1, 2001);
      Fecha g(3, 4, 2005);
      g = f;
      Fecha_chk_eq(g, 1, 1, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Asignacion trivial entre fechas) {
#if __GNUC__ >= 5
      fct_chk(is_trivially_copy_assignable<Fecha>());
#endif
      fct_chk(is_nothrow_copy_assignable<Fecha>());
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Asignacion entre fechas - asociatividad) {
      const Fecha f(1, 1, 2001);
      Fecha g(3, 4, 2005);
      Fecha h(g);
      h = g = f;
      Fecha_chk_eq(h, 1, 1, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Obervadores dia-mes-anno){
      const Fecha f(29, 2, 2000);
      fct_chk_eq_int(f.dia(), 29);
      fct_chk_eq_int(2, f.mes());
      fct_chk_eq_int(f.anno(), 2000);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Conversion implicita a cadena) {
      const Fecha f(2, 4, 2006);
      fct_chk(strstr(f, "domingo") != 0);
      fct_chk(strstr(f, "abril") != 0);
      fct_chk(strstr(f, "2006") != 0);
      const Fecha g("25/09/1968");
      fct_chk(strstr(g, "miércoles"));
      fct_chk(strstr(g, "de septiembre"));
      fct_chk(strstr(g, "de 1968"));
    }
    FCT_TEST_END();

    // Anuladas las comparaciones con cadenas por ambigüedad en P0
    // al haber ctor. de conversión y operador de conversión

    FCT_TEST_BGN(Fecha - Comparacion: igualdad) {
      const Fecha f(1, 2, 2000);
      const Fecha g(f);
      const Fecha h(2, 3, 2001);
      fct_chk(f == g);
      fct_chk(!(f == h));
      //fct_chk(f == "1/2/2000");
      //fct_chk("2/3/2001" == g);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: desigualdad) {
      const Fecha f(1, 2, 2000);
      const Fecha g(f);
      const Fecha h(2, 3, 2001);
      fct_chk(!(f != g));
      fct_chk(f != h);
      //fct_chk(f != "00002/003/02001");
      //fct_chk("1/1/2001" != g);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: mayor) {
      const Fecha f(10, 2, 2000);
      const Fecha g( 9, 2, 2001);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(!(f > f));
      fct_chk(g > f);
      fct_chk(f > h);
      fct_chk(i > f);
      fct_chk(f > j);
      fct_chk(k > f);
      //fct_chk(f > "11/2/1999");
      //fct_chk("1/1/2005" > k);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: mayor o igual) {
      const Fecha f(10, 2, 2000);
      const Fecha g( 9, 2, 2001);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(f >= f);
      fct_chk(g >= f);
      fct_chk(f >= h);
      fct_chk(i >= f);
      fct_chk(f >= j);
      fct_chk(k >= f);
      //fct_chk(f >= "9/2/1999");
      //fct_chk("10/4/2001" >= i);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: menor) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(!(f < f));
      fct_chk(f < g);
      fct_chk(h < f);
      fct_chk(f < i);
      fct_chk(j < f);
      fct_chk(f < k);
      //fct_chk(f < "11/3/2001");
      //fct_chk("9/5/2000" < i);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: menor o igual) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(f <= f);
      fct_chk(f <= g);
      fct_chk(h <= f);
      fct_chk(f <= i);
      fct_chk(j <= f);
      fct_chk(f <= k);
      //fct_chk(f <= "10/02/2000");
      //fct_chk("20/001/2000" <= h);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Diferencia en dias entre 2 fechas distintas) {
      const Fecha f1(06, 02, 2015);
      const Fecha f2(29, 12, 1958);
      long int d1 = f1 - f2;
      long int d2 = f2 - f1;
      fct_chk(d1 == 20493l && d2 == -20493l);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Diferencia en dias entre 2 fechas muy distintas) {
      const Fecha f1(31, 12, Fecha::AnnoMaximo);
      const Fecha f2( 1,  1, Fecha::AnnoMinimo);
      long int d1 = f1 - f2;
      long int d2 = f2 - f1;
      // Dejamos un margen de ±1 por si acaso
      fct_chk((d1 >=  49672l && d1 <=  49674l) &&
	      (d2 <= -49672l && d2 >= -49674l));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Diferencia en dias entre 2 fechas iguales) {
      const Fecha f1(16, 3, 2013);
      const Fecha f2(f1);
      long int d = f1 - f2;
      fct_chk(d == 0l);
    }
    FCT_TEST_END();
  }
  FCT_FIXTURE_SUITE_END();

/**************************************************************************
 *********************** CADENA *******************************************
 *************************************************************************/

  bPrimera = true;

  FCT_SUITE_BGN(Cadena) {

    if (bPrimera) {
      cout << "\n--------------------------------"
	" Cadena ------------------------------------" << endl;
      bPrimera = false;
    }

    FCT_TEST_BGN(Cadena - Ctor.: tamanno y caracter de relleno) {
      const Cadena a(5, 'A');
      Cadena_chk_eq(a, "AAAAA");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: tamanno y rellenado con espacios) {
      const Cadena a(10);
      Cadena_chk_eq(a, "          ");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: tamanno cero) {
      const Cadena a(0, '0');
      Cadena_chk_eq(a, "");
    }
    FCT_TEST_END();
#if 0
    FCT_TEST_BGN(Cadena - Ctor.: tamanno negativo) {
      fct_chk_ex(bad_alloc, const Cadena a(-1, '0'));
    }
    FCT_TEST_END();
#endif
    FCT_TEST_BGN(Cadena - Ctor.: tamanno; no conversion implicita) {
      bool conversion_implicita = ! is_convertible<int, Cadena>::value;
      fct_chk(conversion_implicita);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: sin parametros; Cadena vacia) {
      const Cadena a;
      Cadena_chk_eq(a, "");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: por copia de otra Cadena) {
      const Cadena a(3, '_');
      const Cadena b(a);
      Cadena_chk_eq(b, "___");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: conversion desde cadena de bajo nivel) {
      const Cadena  a ("Con amor y aguardiente, nada se siente.");
      Cadena_chk_eq(a, "Con amor y aguardiente, nada se siente.");
      bool conversion_implicita = is_convertible<const char*, Cadena>::value;
      fct_chk(conversion_implicita);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: N primeros caracteres de cadena de C; normal) {
      const Cadena a("Quien demande pan y abrigo"
		     ", va a saber quien es su amigo.", 26);
      Cadena_chk_eq(a, "Quien demande pan y abrigo");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: N 1os. caracteres de cadena de C; N > longitud) {
      const Cadena a("Treinta monjes y un abad "
		     "no pueden hacer beber a un asno contra su voluntad.", 90);
      Cadena_chk_eq(a, "Treinta monjes y un abad "
		    "no pueden hacer beber a un asno contra su voluntad.");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: N primeros caracteres de cadena de C; N = 0) {
      const Cadena b("Frijoles con coles, pedos a montones.", 0);
      Cadena_chk_eq(b, "");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: desde sub-Cadena; normal) {
      const Cadena a("Casa de muchos, casa de sucios");
      const Cadena b(a, 16, 4);
      Cadena_chk_eq(b, "casa");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: desde sub-Cadena; se omite la longitud) {
      const Cadena a("Casa de muchos, casa de sucios");
      const Cadena b(a, 16);
      Cadena_chk_eq(b, "casa de sucios");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: desde sub-Cadena; 0 y npos) {
      const Cadena a("Casa de muchos, casa de sucios");
      const Cadena b(a, 0, Cadena::npos);
      Cadena_chk_eq(b, static_cast<const char*>(a));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: desde sub-Cadena; indice y longitud 0) {
      const Cadena a("Casa de muchos, casa de sucios");
      const Cadena b(a, 0, 0);
      Cadena_chk_eq(b, "");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Ctor.: desde sub-Cadena; longitud demasiado grande ) {
      const Cadena a("Casa de muchos, casa de sucios");
      const Cadena b(a, 24, 10);
      Cadena_chk_eq(b, "sucios");
    }
    FCT_TEST_END();


    FCT_TEST_BGN(Cadena - Ctor.: desde sub-Cadena; indice fuera de rango) {
      const Cadena a("Casa de muchos, casa de sucios");
      fct_chk_ex(out_of_range, const Cadena b(a, a.length(), 0));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Asignar una Cadena a otra) {
      Cadena a("Ten qué dar, y el culo te vendrán a besar.");
      const Cadena b("Ni olla sin tocino, ni alegría sin vino.");
      a = b;
      Cadena_chk_eq(a, static_cast<const char*>(b));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Asignar una cadena de bajo nivel) {
      Cadena a = "Tres tocas en un hogar, mal se pueden concertar.";
      a = "Los hijos de mis hijas mis nietos son, los de mis hijos serán o no.";
      Cadena_chk_eq(a, "Los hijos de mis hijas mis nietos son, "
		    "los de mis hijos serán o no.");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Conversion a cadena de C) {
      bool convertible_a_cadC = is_convertible<Cadena, const char*>::value;
      fct_chk(convertible_a_cadC);
      const char* const s = "En junio el día veintinuo, es largo como ninguno.";
      const Cadena a = s;
      Cadena_chk_eq(a, s);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Longitud es entero sin signo) {
      const Cadena a;
      fct_chk(is_unsigned<decltype(a.length())>::value);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Observadora de longitud: cadena vacia) {
      const Cadena a;
      fct_chk_eq_int(a.length(), 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Observadora de longitud: cadena no vacia) {
      const char *s = "Trabajando por cuenta ajena, "
	"poco se gana y mucho se pena.";
      const Cadena a(s);
      fct_chk_eq_int(a.length(), strlen(s));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Concatenacion: con +=) {
      Cadena a("El camino que se sabe,");
      a += Cadena(" bien se anda");
      Cadena_chk_eq(a, "El camino que se sabe, bien se anda");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Concatenacion: con +) {
      const Cadena a("Cada cual,"), b(" en su corral");
      const Cadena c = a + b;
      Cadena_chk_eq(c, "Cada cual, en su corral");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Comparacion: igualdad) {
      fct_chk(  Cadena("hola") == Cadena("hola"));
      fct_chk(!(Cadena("hola") == Cadena("adios")));
      fct_chk(!(Cadena("hola") == Cadena("holas")));
      fct_chk(!(Cadena("holas")== Cadena("hola")));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Comparacion: desigualdad) {
      fct_chk(!(Cadena("hola")  != Cadena("hola")));
      fct_chk(  Cadena("hola")  != Cadena("adios"));
      fct_chk(  Cadena("hola")  != Cadena("holas"));
      fct_chk(  Cadena("holas") != Cadena("hola"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Comparacion: menor que) {
      fct_chk(    Cadena("") < Cadena("x"));
      fct_chk(   Cadena("a") < Cadena("b"));
      fct_chk(!(Cadena("ab") < Cadena("ab")));
      fct_chk(!(Cadena("ca") < Cadena("aa")));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Comparacion: menor o igual que) {
      fct_chk(    Cadena("") <= Cadena("x"));
      fct_chk(   Cadena("a") <= Cadena("b"));
      fct_chk(  Cadena("ab") <= Cadena("ab"));
      fct_chk(!(Cadena("ca") <= Cadena("aa")));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Comparacion: mayor que) {
      fct_chk(!(  Cadena("") > Cadena("x")));
      fct_chk(!( Cadena("a") > Cadena("b")));
      fct_chk(!(Cadena("ab") > Cadena("ab")));
      fct_chk(  Cadena("ca") > Cadena("aa"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Comparacion: mayor o igual que) {
      fct_chk(!( Cadena("") >= Cadena("x")));
      fct_chk(!(Cadena("a") >= Cadena("b")));
      fct_chk( Cadena("ab") >= Cadena("ab"));
      fct_chk( Cadena("ca") >= Cadena("aa"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Leer caracter: [] y posicion valida) {
      const Cadena a("abcd");
      fct_chk(a.operator[](0) == 'a');
      fct_chk(a[3] == 'd');
    }
    FCT_TEST_END();

    /* Este test no puede hacerse si la cadena interna no acaba en '\0',
     * ya que daría un error de ejecución fuera del control del programa.
     */
    FCT_TEST_BGN(Cadena - Leer caracter: [] y posicion no valida) {
      const Cadena a;
      fct_chk(!a[0]);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Leer caracter: at y posicion valida) {
      const Cadena a("abcd");
      fct_chk(a.at(0) == 'a');
      fct_chk(a.at(3) == 'd');
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Leer caracter: at y posicion no valida) {
      const Cadena a;
      fct_chk_ex(out_of_range, a.at(0));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Escribir caracter: []) {
      Cadena a("Lo que en junio se moja, en junio se seca.");
      a.operator[](30) = 'l';
      Cadena_chk_eq(a, "Lo que en junio se moja, en julio se seca.");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Escribir caracter: at()) {
      Cadena a("Marzo, loco, y abril, no poco.");
      a.at(9) = 'k';
      Cadena_chk_eq(a, "Marzo, loko, y abril, no poco.");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Escribir caracter: at() y posicion no valida) {
      Cadena a("Febrero loco, y marzo otro poco.");
      fct_chk_ex(out_of_range, a.at(90) = '.');
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Destructor) {
      fct_chk(is_destructible<Cadena>::value and
              is_nothrow_destructible<Cadena>::value and
              not is_trivially_destructible<Cadena>::value);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Subcadena: caso normal) {
      const Cadena a("El dinero del tonto se escurre pronto.");
      Cadena_chk_eq(a.substr(14, 5), "tonto");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Subcadena: posicion inicial mayor que longitud) {
      const Cadena a("Con más mar, más vela.");
      fct_chk_ex(out_of_range, a.substr(a.length(), 1));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Subcadena: posicion inicial negativa) {
      const Cadena a("Con gente mal criada, nada.");
      fct_chk_ex(out_of_range, a.substr(-2, 10));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Subcadena: tamanno mayor que longitud restante) {
      const Cadena a("Al loco y al malo, quítales el palo.");
      fct_chk_ex(out_of_range, a.substr(32, 10));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Subcadena: tamanno negativo) {
      const Cadena a("Allá va el niño, donde lo tratan con cariño.");
      fct_chk_ex(out_of_range, a.substr(12, -1));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Cadena - Subcadena: tamanno excesivo) {
      const Cadena a("¿Me guardas un secreto, amigo?"
		     " Mejor me lo guardas si no te lo digo.");
      fct_chk_ex(out_of_range, a.substr(12, 100));
    }
    FCT_TEST_END();
  }
  FCT_SUITE_END();
}
FCT_END()
