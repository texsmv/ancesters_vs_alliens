#include "Objeto_animado.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
int random_Number(int x){
    std::srand(std::time(0));
    int h = std::rand()%(x);

    return h;
}
Objeto_animado::Objeto_animado(string nombres_archivos[],int num_imag,float posx, float posy,float t_frecuencia,int im){
    for (int i=0;i<num_imag;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas.push_back(nuevo);
        this->texturas.at(i)->loadFromFile(nombres_archivos[i]);
    }
    this->pos_imag=im;
    cout<<pos_imag<<endl;
    this->setTexture(*texturas.at(pos_imag));
    this->t_frecuencia=t_frecuencia;
    this->r_frecuencia=new sf::Clock;
    this->num_imag=num_imag;
    this->setPosition(posx,posy);

}

void Objeto_animado::update(){
    this->animar();
}

void Objeto_animado::animar(){
    if(this->r_frecuencia->getElapsedTime().asSeconds()>t_frecuencia){
        pos_imag++;
        if(pos_imag==num_imag){
            pos_imag=0;
        }

        this->setTexture(*texturas.at(pos_imag));
        this->r_frecuencia->restart();



    }

}

Objeto_animado::Objeto_animado()
{
    //ctor
}

Objeto_animado::~Objeto_animado()
{
    //dtor
}
