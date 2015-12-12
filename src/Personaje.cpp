#include "Personaje.h"


Personaje::Personaje(std::string nombreArchivo, float alto, float ancho,sf::Event * evento, sf::RenderWindow * win, int ** matriz,float alto_bloque,float ancho_bloque, bool sec_player){
    this->alto=alto;
    this->ancho=ancho;
    this ->textura.loadFromFile(nombreArchivo);
    this ->setTexture(textura);
    this ->setTextureRect(sf::IntRect(3,0,57,70));
    this->matriz=matriz;
    this->Coordenadas=this->getPosition();
    this->last_posicion=this->getPosition();
    this->win=win;
    this->alto_bloque=alto_bloque;
    this->ancho_bloque=ancho_bloque;
    this->evento=evento;
    this->velocidad_ataque=new sf::Clock;
    this->t_salto=new sf::Clock;
    this->t2_salto=new sf::Clock;
    this->sec_player=sec_player;

    if(sec_player==true){
        k_up=sf::Keyboard::W;
        k_down=sf::Keyboard::S;
        k_left=sf::Keyboard::A;
        k_right=sf::Keyboard::D;
    }
    else{
        k_up=sf::Keyboard::Up;
        k_down=sf::Keyboard::Down;
        k_left=sf::Keyboard::Left;
        k_right=sf::Keyboard::Right;
    }
    buffer.loadFromFile("arrow.wav");
    s_disparo.setBuffer(buffer);
    buffer2.loadFromFile("arrow_impact.wav");
    s_impacto.setBuffer(buffer2);

}


void Personaje::setEvento(sf::Event*evento){
    this->evento=evento;

}


void Personaje::update(){
    this->anim_anterior=this->anim_actual;
    this->Mover();


}

void Personaje::animar(float t){
    if(this->anim_actual==shoot_der||this->anim_actual==shoot_izq){
        t=0.1;
    }

    if(this->anim_anterior!=this->anim_actual){
        t=0;
    }
    if(pos_animacion>=anim_actual.size()){
            pos_animacion=0;
        }
    if (t_animacion->getElapsedTime().asSeconds()>t){
        this->setTexture(*anim_actual.at(pos_animacion),true);
        pos_animacion++;
        this->t_animacion->restart();
        if(pos_animacion==anim_actual.size()){
            pos_animacion=0;
        }
    }

}

void Personaje::Mover(){


    this->last_posicion=this->getPosition();
    if (sf::Keyboard::isKeyPressed(k_right)){
        this->velocidad_eje_x={4,0};
        this->anim_actual=anim_der;
        this->derecha=true;

    }
    else if (sf::Keyboard::isKeyPressed(k_left)){
        this->velocidad_eje_x={-4,0};
        this->anim_actual=anim_izq;
        this->derecha=false;

    }
    else{
        if(this->derecha==true)
            this->anim_actual=stand_der;
        else
            this->anim_actual=stand_izq;
    }

    if(sf::Keyboard::isKeyPressed(k_up)){
        if (this->t_salto->getElapsedTime().asSeconds()>2||this->saltar==true){
            this->salto={0,-9};
            this->t_salto->restart();
            this->saltos=0;
            this->saltar=false;
        }
        else if(this->t_salto->getElapsedTime().asSeconds()>0.3&&saltos==0){
            this->salto={0,-9};
            this->saltos++;
            this->t_salto->restart();
        }

    }
    if (sf::Keyboard::isKeyPressed(k_down)){
        this->disparar();
        this->draw_bala=true;
        if(this->derecha==true){
            this->anim_actual=shoot_der;
        }
        else{
            this->anim_actual=shoot_izq;
        }
    }

    this->velocidad_eje_y+=salto;

    ///////////////////////verificar colisiones

    sf::Vector2i esquina_sup_izq, esquina_sup_der, esquina_inf_izq, esquina_inf_der;

    esquina_sup_izq=sf::Vector2i(Coordenadas+this->velocidad_eje_y+this->gravedad);
    esquina_sup_der=sf::Vector2i(Coordenadas+this->velocidad_eje_y+this->gravedad)+sf::Vector2i{ancho,0};
    esquina_inf_izq=sf::Vector2i(Coordenadas+this->velocidad_eje_y+this->gravedad)+sf::Vector2i{0,alto};
    esquina_inf_der=sf::Vector2i(Coordenadas+this->velocidad_eje_y+this->gravedad)+sf::Vector2i{ancho,alto};

    if (((*(*(matriz+esquina_sup_izq.y/alto_bloque)+esquina_sup_izq.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_sup_der.y/alto_bloque)+esquina_sup_der.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_inf_der.y/alto_bloque)+esquina_inf_der.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_inf_izq.y/alto_bloque)+esquina_inf_izq.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_sup_izq.y/alto_bloque)+esquina_sup_izq.x/ancho_bloque)!=9)&&(*(*(matriz+esquina_sup_der.y/alto_bloque)+esquina_sup_der.x/ancho_bloque)!=9)&&(*(*(matriz+esquina_inf_der.y/alto_bloque)+esquina_inf_der.x/ancho_bloque)!=9)&&(*(*(matriz+esquina_inf_izq.y/alto_bloque)+esquina_inf_izq.x/ancho_bloque)!=9))){
        this->setPosition(Coordenadas+this->velocidad_eje_y+this->gravedad);
        this->Coordenadas=this->getPosition();
    }


    esquina_sup_izq=sf::Vector2i(Coordenadas+velocidad_eje_x);
    esquina_sup_der=sf::Vector2i(Coordenadas+velocidad_eje_x)+sf::Vector2i{ancho,0};
    esquina_inf_izq=sf::Vector2i(Coordenadas+velocidad_eje_x)+sf::Vector2i{0,alto};
    esquina_inf_der=sf::Vector2i(Coordenadas+velocidad_eje_x)+sf::Vector2i{ancho,alto};


    if ((*(*(matriz+esquina_sup_izq.y/alto_bloque)+esquina_sup_izq.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_sup_der.y/alto_bloque)+esquina_sup_der.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_inf_der.y/alto_bloque)+esquina_inf_der.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_inf_izq.y/alto_bloque)+esquina_inf_izq.x/ancho_bloque)!=0)&&(*(*(matriz+esquina_sup_izq.y/alto_bloque)+esquina_sup_izq.x/ancho_bloque)!=9)&&(*(*(matriz+esquina_sup_der.y/alto_bloque)+esquina_sup_der.x/ancho_bloque)!=9)&&(*(*(matriz+esquina_inf_der.y/alto_bloque)+esquina_inf_der.x/ancho_bloque)!=9)&&(*(*(matriz+esquina_inf_izq.y/alto_bloque)+esquina_inf_izq.x/ancho_bloque)!=9)){
        this->setPosition(Coordenadas+velocidad_eje_x);
        this->Coordenadas=this->getPosition();

    }




    /////velocidades
    this->velocidad_eje_x={0,0};

    if (this->velocidad_eje_y.y<=0){

        this->velocidad_eje_y.y+=3;
    }
    if (this->salto.y<0)
        this->salto+={0,1};



    if (this->last_posicion.y==this->getPosition().y){
        if(this->t2_salto->getElapsedTime().asSeconds()>0.1)
            this->saltar=true;
    }
    else{
        this->t2_salto->restart();
    }
    if(this->last_posicion.y==this->getPosition().y){
        this->velocidad_eje_y={0,0};
    }

}


void Personaje::draw_proyectiles(){

    for (int i=0;i<this->proyectiles.size();i++){

        proyectiles.at(i)->update();
        win->draw(*proyectiles.at(i));
    }

}

void Personaje::update_proyectiles(){
    for (int i=0;i<this->proyectiles.size();i++){

        proyectiles.at(i)->update();
     }
    for (int i=0;i<this->proyectiles.size();i++){
        if(this->proyectiles.at(i)->t_vida->getElapsedTime().asSeconds()>2){
            delete this->proyectiles.at(i);
            this->proyectiles.erase(proyectiles.begin()+i);
        }

    }

}

void Personaje::disparar(){
    sf::Time t1;
    t1= sf::seconds(0.3);
    if (this->velocidad_ataque->getElapsedTime()>t1){
        this->velocidad_ataque->restart();
        Proyectil * nuevo= new Proyectil("flecha.png",30,30,evento,win,Coordenadas+sf::Vector2f{0,35},14,this->derecha);
        this->proyectiles.push_back(nuevo);
        this->s_disparo.play();
    }
}
Personaje::Personaje()
{
    //ctor
}

Personaje::~Personaje()
{
    //dtor
}
