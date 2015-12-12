#include "Nave.h"
#include <cstdlib>
#include <ctime>
#include <math.h>

int rand_Number(int x){
    std::srand(std::time(0));
    int h = std::rand()%(x);

    return h;
}



Nave::Nave(string nombre_imagen, float alto, float ancho,int** matriz){
    this->matriz=matriz;
    this->textura.loadFromFile(nombre_imagen);
    this->setTexture(textura);
    this->alto=alto;
    this->ancho=ancho;
    this->setPosition(1200,rand_Number(500));
    this->mov_nave=new sf::Clock;
    this->var_mov=rand_Number(3)+1;
    this->t_cambio=rand_Number(6);
    this->angle=0;
    this->mov2_nave=new sf::Clock;

    string nomb_anim_mov[4]={"move_0.png","move_1.png","move_2.png","move_3.png"};

    for (int i=0;i<4;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_mov[i]);
        this->anim_mov.push_back(nuevo);
    }

    string nomb_anim_muerte[7]={"die1_0.png","die1_1.png","die1_2.png","die1_3.png","die1_4.png","die1_5.png","die1_6.png"};

    for (int i=0;i<7;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_muerte[i]);
        this->anim_muerte.push_back(nuevo);
    }

    this->anim_actual=anim_mov;
    this->anim_anterior=anim_actual;
    this->t_animacion=new sf::Clock;
    this->t_muerte=new sf::Clock;
/*
    this->buffer.loadFromFile("nave.wav");
    this->bip.setBuffer(buffer);
    bip.play();
*/
}

void Nave::animar(float t){
    if  (this->start_destroy==true){

        if(pos_animacion>=anim_actual.size()){
                pos_animacion=0;
            }
        if (t_animacion->getElapsedTime().asSeconds()>t){
            this->setTexture(*anim_actual.at(pos_animacion));
            this->setTextureRect(sf::IntRect(25, 25, 50, 50));
            pos_animacion++;
            this->t_animacion->restart();
            if(pos_animacion==anim_actual.size()){
                pos_animacion=0;
            }
        }
    }

    else if(this->anim_anterior!=this->anim_actual){
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

void Nave::muerte(){
    t_muerte=new sf::Clock;
}

void Nave::verif_choque(float tam_bloque){
    this->Coordenadas=this->getPosition();
    int i=Coordenadas.x/tam_bloque;
    int j=Coordenadas.y/tam_bloque;
    if (i+3<28&&j>0&&i>0){
        if (*(*(this->matriz+j)+i-3)==0){
            this->angle=180;
            if(this->t_cambio==0){
                this->move(0,-3);
            }
        }
        if (*(*(this->matriz+j+3)+i)==0){
            this->angle=180;
            if(this->t_cambio==0){
                this->move(0,-1);
            }
        }
    }

}

void Nave::update(){

    if(this->start_destroy==true){
        this->anim_actual=anim_muerte;
    }
    else{
    this->move(-var_mov,sin(angle)*t_cambio);

    if(mov_nave->getElapsedTime().asSeconds()>1){
        mov_nave->restart();
        angle=angle+1;


    }
    if(this->mov2_nave->getElapsedTime().asSeconds()>2){
        this->t_cambio=rand_Number(6);
    }
    }
    if(start_destroy==true){
        if (t_muerte->getElapsedTime().asSeconds()>1.5){
            destroy=true;
        }
    }
    else{
        t_muerte->restart();
    }
    this->animar(0.3);
}

Nave::Nave()
{
    //ctor
}

Nave::~Nave()
{
    //dtor
}
