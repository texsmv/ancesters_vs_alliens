#include "Obj_anim_temp.h"

Obj_anim_temp::Obj_anim_temp(string nombres_archivos[],int num_imag,float posx, float posy,float t_frecuencia, float t_vida){
    for (int i=0;i<num_imag;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas.push_back(nuevo);
        this->texturas.at(i)->loadFromFile(nombres_archivos[i]);
    }
    this->pos_imag=0;
    this->setTexture(*texturas.at(pos_imag));
    this->t_frecuencia=t_frecuencia;
    this->r_frecuencia=new sf::Clock;
    this->num_imag=num_imag;
    this->setPosition(posx,posy);
    this->t_vida=t_vida;
    this->c_vida=new sf::Clock;
}


Obj_anim_temp::Obj_anim_temp(vector <sf::Texture*> texturas,int num_imag,float posx, float posy,float t_frecuencia, float t_vida){
    this->texturas=texturas;
    this->pos_imag=0;
    this->setTexture(*texturas.at(pos_imag));
    this->t_frecuencia=t_frecuencia;
    this->r_frecuencia=new sf::Clock;
    this->num_imag=num_imag;
    this->setPosition(posx,posy);
    this->t_vida=t_vida;
    this->c_vida=new sf::Clock;
}

void Obj_anim_temp::update(){
    if (this->c_vida->getElapsedTime().asSeconds()<=t_vida){
        this->animar();
    }
    else{
        this->destroy=true;
    }

}

Obj_anim_temp::Obj_anim_temp()
{
    //ctor
}

Obj_anim_temp::~Obj_anim_temp()
{
    //dtor
}
