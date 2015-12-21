#include "Pet.h"

Pet::Pet(float posx , float posy)
{

    string nom_stand[19]={"stand1_0_d.png","stand1_1_d.png","stand1_2_d.png","stand1_3_d.png","stand1_4_d.png","stand1_5_d.png","stand1_6_d.png",
    "stand1_7_d.png","stand1_8_d.png","stand1_9_d.png","stand1_10_d.png","stand1_11_d.png","stand1_12_d.png","stand1_13_d.png","stand1_14_d.png","stand1_15_d.png","stand1_16_d.png","stand1_17_d.png","stand1_18_d.png"};
    for (int i=0;i<19;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nom_stand[i]);
        this->anim_stand.push_back(nuevo);
    }

    string nom_angry[7]={"angry_0_d.png","angry_1_d.png","angry_2_d.png","angry_3_d.png","angry_4_d.png","angry_5_d.png","angry_6_d.png"};
    for (int i=0;i<7;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nom_angry[i]);
        this->anim_angry.push_back(nuevo);
    }
    this->anim_actual=anim_stand;
    this->anim_anterior=anim_actual;


    this->setTexture(*anim_actual.at(0),true);


    this->setPosition(posx,posy);

    this->t_atacar= new sf::Clock;
    this->t_animacion=new sf::Clock;
}

void Pet::update(){
    if (this->t_atacar->getElapsedTime().asSeconds()>2){
        if(this->atacando==false){
            this->anim_actual=anim_angry;
            this->anim_anterior=anim_angry;
            this->cambiar_anim(this->anim_angry);
            this->t_atacar->restart();

            this->atacando=true;
        }
        else{
            this->anim_actual=anim_stand;
            this->anim_anterior=anim_stand;
            this->cambiar_anim(this->anim_stand);
            this->t_atacar->restart();

            this->atacando=false;
        }
    }
    this->animar(0.1);
}

Pet::Pet()
{
    //ctor
}

Pet::~Pet()
{
    //dtor
}
