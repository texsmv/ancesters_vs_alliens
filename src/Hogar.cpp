#include "Hogar.h"

Hogar::Hogar(string nombre_archivo, float posx,float posy, int vidas){
    this->textura.loadFromFile(nombre_archivo);
    this->setTexture(textura);
    this->Coordenadas={posx,posy-this->textura.getSize().y};
    this->setPosition(Coordenadas);
    this->vida=vidas;
}

void Hogar::quitarVida(int vid){
    this->vida-=vid;
}

Hogar::Hogar()
{
    //ctor
}

Hogar::~Hogar()
{
    //dtor
}
