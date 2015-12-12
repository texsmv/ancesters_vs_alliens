#include "Objeto.h"

Objeto::Objeto(std::string nombreArchivo, float alto, float ancho){

    this->alto = alto;
    this->ancho = ancho;



    this ->textura.loadFromFile(nombreArchivo);
    this ->setTexture(textura);

    this->Coordenadas=this->getPosition();



}

void Objeto::cambiar_anim(vector<sf::Texture*> nueva_anim){
    this->anim_actual=nueva_anim;
    this->t_animacion->restart();
}

void Objeto::animar(float t){
    if(this->anim_anterior!=this->anim_actual){
        t=0;
    }
    if(pos_animacion>=anim_actual.size()){
            pos_animacion=0;
        }
    if (t_animacion->getElapsedTime().asSeconds()>t){
        this->setTexture(*anim_actual.at(pos_animacion));
        pos_animacion++;
        this->t_animacion->restart();
        if(pos_animacion==anim_actual.size()){
            pos_animacion=0;
        }
    }

}
void Objeto::update(){

}



Objeto::Objeto()
{
    //ctor
}

Objeto::~Objeto()
{
    //dtor
}
