#ifndef IMAGEN_H
#define IMAGEN_H

#include "vector.h"
#include <string>
#include <iostream>
#include <sstream>


class imagen{

private:

    int ancho, alto, intensidad; //atributos de ancho, alto (en pixeles) y maxima intensidad de la imagen
    vector<vector<int>> pixel; //matriz de enteros que representa la matriz de pixeles de la imagen

//el siguiente metodo devuelve por referencia al atributo pixel, se encuentra en la parte privada para evitar la realizacion de asignaciones de la matriz
//pixel con otras matrices que no respeten el ancho y alto correspondiente
    vector<vector<int>> & getMatrizPixel();

public:

    imagen();//constructor sin parametros, crea una imagen de 1 pixel negro
    imagen(const int intensidad, const vector<vector<int>> &matriz); //Constructor con parametros
    imagen(const imagen &img); //Constructor copia
    ~imagen();//destructor

    int getAlto();//devuelve el ancho de la imagen
    int getAncho();//devuelve el alto de la imagen
    int getIntensidad();//devuelve la intensidad maxima decada pixel de la imagen


    /*
    el metodo transformar devuelve un objeto imagen creado a partir de la modificacion de la matriz de otro objeto imagen mediante
    la funcion pfuncion, la cual no retorna nada y debe recibir un matriz implementada mediante vectores y el ancho y alto de la matriz.
    La funcion pfuncion no puede modificar el ancho y el alto de la matriz que se le pasa, solo alterar el contenido respetando la intensidad maxima,
    caso contrario devuelve la imagen sin transformar*/
    imagen transformar(void(*pfuncion)(vector<vector<int>>&, int, int));
    imagen & operator = (const imagen &);//operador =

    friend std::ostream &operator<<(std::ostream &, const imagen &);//operador de salida
    friend std::istream &operator>>(std::istream &, imagen &);//operador de entrada

};

#endif // IMAGEN_H
