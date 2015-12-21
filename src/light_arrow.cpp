#include "light_arrow.h"
light_arrow::light_arrow(sf::Event* evento,sf::Vector2f posicion, bool derecha){
    this->alto = 53;
    this->ancho = 105;
    if(derecha==true){
        string nom_arrow_anim[10]={"ball_0.png","ball_1.png","ball_2.png","ball_3.png","ball_4.png","ball_5.png","ball_6.png","ball_7.png","ball_8.png","ball_9.png"};
        for (int i=0;i<10;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim[i]);
            this->arrow_anim.push_back(nuevo);
        }
        string nom_arrow_anim_inicial[6]={"keydown_0.png","keydown_1.png","keydown_2.png","keydown_3.png","keydown_4.png","keydown_5.png"};
        for (int i=0;i<6;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim_inicial[i]);
            this->anim_inicial.push_back(nuevo);
        }

    }
    else{
    string nom_arrow_anim[10]={"ball_0_2.png","ball_1_2.png","ball_2_2.png","ball_3_2.png","ball_4_2.png","ball_5_2.png","ball_6_2.png","ball_7_2.png","ball_8_2.png","ball_9_2.png"};
        for (int i=0;i<10;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim[i]);
            this->arrow_anim.push_back(nuevo);
        }
        string nom_arrow_anim_inicial[6]={"keydown_0_2.png","keydown_1_2.png","keydown_2_2.png","keydown_3_2.png","keydown_4_2.png","keydown_5_2.png"};
        for (int i=0;i<6;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nom_arrow_anim_inicial[i]);
            this->anim_inicial.push_back(nuevo);
        }

    }
    this->anim_actual=anim_inicial;
    this->anim_anterior=anim_actual;
    this ->setTexture(*anim_actual.at(0));
    this->setPosition(posicion+sf::Vector2f{30,-80});
    this->Coordenadas=this->getPosition();
    this->scale(0.5,0.5);
    this->t_vida=new sf::Clock;
    if(derecha==true){
        this->velocidad={12,0};
    }
    else{
        this->velocidad={-12,0};
    }
    this->t_animacion=new sf::Clock;
    this->t_anim_inicial=new sf::Clock;
    this->rango_colision=10;
//    this->move(0,50);
    this->punto_medio=this->getPosition()+sf::Vector2f{this->ancho/2,this->alto/2};
    this->damage=6;
    bool anim_colision=true;

}


void light_arrow::update(){
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
        //this->move(0,50);

    }
    else if(b_anim_inicial==false){
        this->scale(1.03,1.03);
        this->move(velocidad);
        this->animar(0.03);
        this->rango_colision+=1;
        this->damage+=0.2;
        if(pass_init_anim==false){
            this->move(0,50);
            this->pass_init_anim=true;

        }
    }
    else{
        this->animar(0.05);
    }

    this->Coordenadas=this->getPosition();
    this->anim_anterior=this->anim_actual;
    this->punto_medio=this->getPosition()+sf::Vector2f{ancho/2,alto/2};
}
light_arrow::light_arrow()
{
    //ctor
}

light_arrow::~light_arrow()
{
    //dtor
}
