#include <iostream>
#include "punto.h"
#include <cmath>

using namespace std;

Punto2D::Punto2D(double x = 0. , double y = 0. )
{

}

double Punto2D::distancia(const Punto2D &a) const {
    return sqrt((_x - a._x) * (_x - a._x) + (_y - a._y) * (_y - a._y));
}

double Punto2D::proyeccion(const Punto2D &p1, const Punto2D &p2) const {
    double dx = p2._x - p1._x;
    double dy = p2._y - p1._y;
    double dot = (_x - p1._x) * dx + (_y - p1._y) * dy;
    double len_sq = dx * dx + dy * dy;
    return dot / len_sq;
}

Punto2D Punto2D::operator+(const Punto2D &a) {
    return Punto2D(_x + a._x, _y + a._y);
}

Punto2D Punto2D::operator-(const Punto2D &a) {
    return Punto2D(_x - a._x, _y - a._y);
}

// Corregir la sobrecarga del operador <<
ostream& operator<<(ostream& out, const Punto2D& a) {
    out << "(" << a._x << ", " << a._y << ")";
    return out;
}

// Adicionaré las funciones get/set
void Punto2D::X(const double &x) {
    _x = x;
}

void Punto2D::Y(const double &y) {
    _y = y;
}

double Punto2D::X() const {
    return _x;
}

double Punto2D::Y() const {
    return _y;
}