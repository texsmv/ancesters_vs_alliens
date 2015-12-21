#include "green_arrow.h"
green_arrow::green_arrow(sf::Event* evento,sf::Vector2f posicion, bool derecha){
    this->alto = 53;
    this->ancho = 105;
    if(derecha==true){
        string nom_arrow_anim[3]={"green_arrow1_0.png","green_arrow1_1.png","green_arrow1_2.png"};
        for (int i=0;i<3;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim[i]);
            this->arrow_anim.push_back(nuevo);
        }
        string nom_arrow_anim_inicial[4]={"arrow_effect1_0.png","arrow_effect1_1.png","arrow_effect1_2.png","arrow_effect1_3.png"};
        for (int i=0;i<4;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim_inicial[i]);
            this->anim_inicial.push_back(nuevo);
        }

    }
    else{
    string nom_arrow_anim[3]={"green_arrow2_0.png","green_arrow2_1.png","green_arrow2_2.png"};
        for (int i=0;i<3;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim[i]);
            this->arrow_anim.push_back(nuevo);
        }
        string nom_arrow_anim_inicial[4]={"arrow_effect2_0.png","arrow_effect2_1.png","arrow_effect2_2.png","arrow_effect2_3.png"};
        for (int i=0;i<4;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim_inicial[i]);
            this->anim_inicial.push_back(nuevo);
        }

    }
    this->anim_actual=anim_inicial;
    this->anim_anterior=anim_actual;
    this ->setTexture(*anim_actual.at(0));
    this->setPosition(posicion-sf::Vector2f{0,35});
    this->Coordenadas=this->getPosition();

    this->t_vida=new sf::Clock;
    if(derecha==true){
        this->velocidad={12,0};
    }
    else{
        this->velocidad={-12,0};
    }
    this->t_animacion=new sf::Clock;
    this->t_anim_inicial=new sf::Clock;
    this->rango_colision=40;
    this->punto_medio=this->getPosition()+sf::Vector2f{this->ancho/2,this->alto/2};
}

void green_arrow::update(){
    if(this->start_last_anim==true&&this->empezo_t_muerte==false){
        this->t_muerte= new sf::Clock;
        this->empezo_t_muerte=true;
    }
    if(this->empezo_t_muerte==true){
        if(this->t_muerte->getElapsedTime().asSeconds()<0.5){
            this->destroy=true;
        }
    }

    if(t_anim_inicial->getElapsedTime().asSeconds()>0.2&&b_anim_inicial==true){
        this->anim_actual=arrow_anim;
        this->b_anim_inicial=false;
        this->move(0,15);

    }
    else if(b_anim_inicial==false){
        this->move(velocidad);
        this->animar(0.15);
    }
    else{
        this->animar(0.05);
    }

    this->Coordenadas=this->getPosition();
    this->anim_anterior=this->anim_actual;
    this->punto_medio=this->getPosition()+sf::Vector2f{ancho/2,alto/2};
    this->damage=40;
}


green_arrow::green_arrow()
{
    //ctor
}

green_arrow::~green_arrow()
{
    //dtor
}
