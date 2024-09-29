#include <iostream>
#include <cmath>
using namespace std;

struct complex{
  double re;
  double im;
  complex(double r =0.0 , double i = 0.0){
    re = r;
    im = i;
  }
};
/*
Se implemento la función complex(double r =0.0 , double i = 0.0) en la parte de struct, lo que realiza esta función es inicializar
las variables con valor 0.0 en cada una.
*/

double angle(const complex &a){
  double real = a.re;
  double imag = a.im;
  return atan2(imag, real);
}
/*
-- Asigna a la variable "real" la parte real del numero a y a la variable "imag" la parte imaginaria del numero a
-- Realiza el calculo de arcotangente de la parte imaginaria entre la parte real del numero a y devuelve el resultado
-- Se usa atan2 con la libreria cmath debido a que esta función implementa el caso de la parte real siendo 0, permitiendo un resultado más exacto
*/

double magnitude(const complex &a){
  double real = a.re;
  double imag = a.im;
  return sqrt(real*real + imag*imag);
  }
/*
-- Asigna a la variable "real" la parte real del numero a y a la variable "imag" la parte imaginaria del numero a
-- Calcula la maginutd de el numero complejo aplicando el teorema de pitagoras con las dos partes del numero a y devuelve el resultado
*/

complex conjugate(const complex &a) {
  return complex(a.re, -a.im);
}
/*
-- Realiza el cambio de signo a la parte imaginaria de el numero complejo a y devuelve el resultado
*/

// Ajuste la declaración de estas funciones para tener parámetros por referencia seguros
// e implementelas.
complex operator+(const complex &a, const complex &b){
  complex c;
  c.re = a.re + b.re;
  c.im = a.im + b.im;
  return c;
}

complex operator-(const complex &a, const complex &b){  
  complex c;
  c.re = a.re - b.re;
  c.im = a.im - b.im;
  return c;
}

complex operator*(const complex &a, const complex &b){ 
  complex c;
  c.re = a.re*b.re - a.im*b.im;
  c.im = a.re*b.im + a.im*b.re;
  return c;
}

bool operator==(const complex &a, const complex &b){
  return (magnitude(a) == magnitude(b)) && (angle(a) == angle(b));
} // Implementar utilizando la magnitude y el angle

bool operator<(const complex &a, const complex &b){
  return (magnitude(a) < magnitude(b)) or (angle(a) < angle(b));
}  // Implementar utilizando la magnitude y el angle

bool operator>(const complex &a, const complex &b){
  return (magnitude(a) < magnitude(b)) or (angle(a) < angle(b));
}  // Implementar utilizando la magnitude y el angle


ostream& operator<<(ostream& out, complex &a){
  out << "(" << a.re << ", " << a.im << ")";
  return out;
}


/*
En todos estos casos de sobrecargas de operadores, lo que realiza es permitir que se puedan realizar operaciones con los
objetos de un struct, como si fueran variables normales, la manera de realizar estas sobrecargas es a partir de
designar las instrucciones para llegar al resultado con los elementos del struct
*/