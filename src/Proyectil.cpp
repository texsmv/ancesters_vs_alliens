#include "Proyectil.h"

Proyectil::Proyectil(string nombreArchivo,float alto, float ancho, sf::Event* evento,sf::RenderWindow* win,sf::Vector2f posicion,float velocidad, bool derecha){
    this->alto = 10;
    this->ancho = 50;
    this->win=win;


    this ->textura.loadFromFile(nombreArchivo);
    this ->setTexture(textura);
    this->Coordenadas=this->getPosition();
    this->setPosition(posicion);
    this->t_vida=new sf::Clock;
    if(derecha==true){
        this->velocidad={velocidad,0};
    }
    else{
        this->velocidad={-velocidad,0};
    }
    this->rango_colision=25;
    this->punto_medio=this->getPosition()+sf::Vector2f{ancho/2,alto/2};
    this->damage=10;
}


void Proyectil::update(){
    if(this->start_last_anim==true&&this->empezo_t_muerte==false){
        this->t_muerte= new sf::Clock;
        this->empezo_t_muerte=true;
    }
    if(this->empezo_t_muerte==true){
        if(this->t_muerte->getElapsedTime().asSeconds()<0.5){
            this->destroy=true;
        }
    }
    this->move(velocidad);
    this->Coordenadas=this->getPosition();
    this->punto_medio=this->getPosition()+sf::Vector2f{ancho/2,alto/2};

}




Proyectil::Proyectil()
{
    //ctor
}

Proyectil::~Proyectil()
{
    //dtor
}
