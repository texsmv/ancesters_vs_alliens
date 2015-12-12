#include "Proyectil.h"

Proyectil::Proyectil(string nombreArchivo,float alto, float ancho, sf::Event* evento,sf::RenderWindow* win,sf::Vector2f posicion,float velocidad, bool derecha){
    this->alto = alto;
    this->ancho = ancho;
    this->win=win;


    this ->textura.loadFromFile(nombreArchivo);
    this ->setTexture(textura);

    this->Coordenadas=this->getPosition();
    this->setPosition(posicion);
    this->t_vida=new sf::Clock;
    if(derecha==true){
        this->velocidad=velocidad;
    }
    else{
        this->velocidad=-velocidad;
    }

}


void Proyectil::update(){
    this->move(this->velocidad,0);
    this->Coordenadas=this->getPosition();

}




Proyectil::Proyectil()
{
    //ctor
}

Proyectil::~Proyectil()
{
    //dtor
}
