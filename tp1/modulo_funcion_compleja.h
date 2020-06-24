#ifndef _MODULO_FUNCIONES_COMPLEJAS_
#define _MODULO_FUNCIONES_COMPLEJAS_

#include <iostream>
#include <string>
#include <cctype>
#include <complex>
#include <sstream>
#include "vector.h"
#include "pila.h"

using namespace std;

typedef complex<double> complejo;

//implementacion del algoritmo shutting yard. Recibe un string que represente una funcion valida y devuelve dicha funcion en formato RPN. Esta implementacion no implementa operadores unarios
string shutting_yard(string const &);
//funcion que recibe un string y devuelve true en caso de que los parentesis, corchetes y llaves se encuentren balanceados
bool esta_balanceada(string const &);
//La funcion precedencia recibe un string correspondiente a un operador o funcion y devuelve su precedencia
int precedencia(string const &);
int precedencia(char const &);
//evaluar_expresion recibe un string correspondiente a una funcion en notacion polaca inversa y un valor de tipo complex<double> correspondiente a 
//la variable Z de la funcion y devuelve el resultado de la expresion
complejo evaluar_expresion_rpn(string &, complejo &var);
//las funciones calc realizan y devuelven el resultado del calculo correspondiente al operador o funcion pasado como char
complejo calc(char &, complejo &, complejo &);
complejo calc(char &, complejo &);
//funcion_valida devuelve true en caso de que la funcion en notacion infija pasada como string sea sintacticamente valida
bool funcion_valida(string const &);

#endif
