/* $Id: compra_check.cpp 383 2017-03-25 20:41:45Z gerardo $
*/
#include "checkCode.h"

#include <vector>
#include <iostream>

using namespace std;


int main(int argc, const char **argv)
{
  checkCode c1(argc, argv, "articulo.cpp", 
	       "Orden: ./compra_check articulo.cpp tarjeta.cpp usuario.cpp"
	       " -- -std=c++11 -I../P1");

  c1.setCorrectMessage("Verificación correcta de la clase Artículo.");
  c1.setIncorrectMessage("REVISA LOS ERRORES DE ARTÍCULO.");

  if(c1.findClass("Articulo")) {
    vector<string> functionNames = {"strlen", "strcat", "memset", 
				    "strcpy", "strcmp"};
    string headerName = "cstring";
    c1.includedHeader(functionNames, headerName, true, 
		      "Revisa de dónde son tomadas las funciones"
		      " de la biblioteca estándar como strlen, strcpy...");
    c1.memberVariableAccessLevel("Articulo", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c1.notFriendMember("Articulo", 
		       "Revisa por qué es necesario incluir 'friend'");
    c1.guardClauses("articulo.hpp", "Recuerda añadir las guardas de inclusión");
    c1.check();
  }
  else
    llvm::outs()<<"No se ha encontrado la clase 'Articulo'.\n";

  checkCode c2(argc, argv, "tarjeta.cpp", "");
  c2.setCorrectMessage("Verificación correcta de la clase Tarjeta.");
  c2.setIncorrectMessage("REVISA LOS ERRORES DE TARJETA.");

  if(c2.findClass("Tarjeta")){
    vector<string> functionNames = {"strlen", "strcat", "memset", 
				    "strcpy", "strcmp"};
    string headerName = "cstring";
    c2.includedHeader(functionNames, headerName, true, 
		      "Revisa de dónde son tomadas las funciones"
		      " de la biblioteca estándar como strlen, strcpy...");
    c2.memberVariableAccessLevel("Tarjeta", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c2.notFriendMember("Tarjeta", 
		       "Revisa por qué es necesario incluir 'friend'");
    c2.deletedMethod({"Tarjeta", "operator="}, 
		     {{"const class Tarjeta &"}, {"const class Tarjeta &"}},
		     "Tarjeta", {{"?"}, {"?"}}, 
		     "Revisa el enunciado respecto a la copia de objetos.");  
    c2.guardClauses("tarjeta.hpp", "Recuerda añadir las guardas de inclusión");
    c2.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Tarjeta'.\n";

  checkCode c3(argc, argv,"usuario.cpp", "");
  c3.setCorrectMessage("Verificación correcta de la clase Usuario.");
  c3.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO.");
  if(c3.findClass("Usuario")){
    vector<string> functionNames = {"strlen", "strcat", "memset", 
				    "strcpy", "strcmp"};
    string headerName = "cstring";
    c3.includedHeader(functionNames, headerName, true, 
		      "Revisa de dónde son tomadas las funciones"
		      " de la biblioteca estándar como strlen, strcpy...");
    c3.memberVariableAccessLevel("Usuario", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c3.deletedMethod({"Usuario", "operator="}, 
		     {{"const class Usuario &"}, {"const class Usuario &"}}, 
		     "Usuario", {{"?"}, {"?"}}, 
		     "Revisa el enunciado respecto a la copia de objetos.");
    c3.numberOfConstructors("Usuario", 1, false, 
			    "Revisa el enunciado respecto a los constructores"
			    " en esta clase.");
    c3.friendFunction({"operator<<"}, {{"?"}}, "Usuario", 
		      "Revisa si existen funciones que deben ser marcadas"
		      " como amigas de la clase");
    c3.guardClauses("usuario.hpp", "Recuerda añadir las guardas de inclusión");	
    c3.check();
  }
  else
    llvm::outs()<<"No se ha encontrado la clase 'Usuario'.\n";
}
