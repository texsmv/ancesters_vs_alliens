#include "Inca.h"

Inca::Inca(std::string nombreArchivo, float alto, float ancho,sf::Event * evento, sf::RenderWindow * win, int ** matriz,float alto_bloque,float ancho_bloque, bool sec_player){
    this->alto=alto;
    this->ancho=ancho;
    this ->textura.loadFromFile(nombreArchivo);
    this ->setTexture(textura);
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

    //////////////// --------------cargar texturas ---------------------

    string nomb_anim_der[4]={"walk1_0_i.png","walk1_1_i.png","walk1_2_i.png","walk1_3_i.png"};

    for (int i=0;i<4;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_der[i]);
        this->anim_der.push_back(nuevo);
    }

    string nomb_anim_izq[4]={"walk2_0_i.png","walk2_1_i.png","walk2_2_i.png","walk2_3_i.png"};
    for (int j=0;j<4;j++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_izq[j]);
        this->anim_izq.push_back(nuevo);
    }

    //////  stand_left
    string nomb_anim_der_i[4]={"walk1_0_i.png","walk1_1_i.png","walk1_2_i.png","walk1_3_i.png"};

        for (int i=0;i<4;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_anim_der_i[i]);
            this->anim_der.push_back(nuevo);
        }

        string nomb_anim_izq_i[4]={"walk2_0_i.png","walk2_1_i.png","walk2_2_i.png","walk2_3_i.png"};
        for (int j=0;j<4;j++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_anim_izq_i[j]);
            this->anim_izq.push_back(nuevo);
        }

        //////  stand_left
        string nomb_stand_der_i[5]={"stand1_0_i.png","stand1_1_i.png","stand1_2_i.png","stand1_3_i.png","stand1_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_stand_der_i[i]);
            this->stand_der.push_back(nuevo);
        }
        //////  stand_left
        string nomb_stand_izq_i[5]={"stand2_0_i.png","stand2_1_i.png","stand2_2_i.png","stand2_3_i.png","stand2_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_stand_izq_i[i]);
            this->stand_izq.push_back(nuevo);
        }
        ////// shoot_der
        string nomb_shoot_der_i[5]={"shoot1_0_i.png","shoot1_1_i.png","shoot1_2_i.png","shoot1_3_i.png","shoot1_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_shoot_der_i[i]);
            this->shoot_der.push_back(nuevo);
        }
        ////// shoot_izq
        string nomb_shoot_izq_i[5]={"shoot2_0_i.png","shoot2_1_i.png","shoot2_2_i.png","shoot2_3_i.png","shoot2_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_shoot_izq_i[i]);
            this->shoot_izq.push_back(nuevo);
        }



    buffer.loadFromFile("arrow.wav");
    s_disparo.setBuffer(buffer);
    buffer2.loadFromFile("arrow_impact.wav");
    s_impacto.setBuffer(buffer2);

    this->t_animacion=new sf::Clock;

    this->anim_actual=this->stand_der;

    this->setPosition(40*5,40*3);
    this->Coordenadas=this->getPosition();
}


void Inca::update(vector<Nave*>naves){
    this->anim_anterior=this->anim_actual;
    this->Mover();
    this->verif_disparos();

}

void Inca::animar(float t){
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

void Inca::verif_disparos(){
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
}

void Inca::Mover(){


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


void Inca::update_proyectiles(){
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

void Inca::disparar(){
    sf::Time t1;
    t1= sf::seconds(0.3);
    if (this->velocidad_ataque->getElapsedTime()>t1){
        this->velocidad_ataque->restart();
        Proyectil * nuevo= new Proyectil("flecha.png",30,30,evento,win,Coordenadas+sf::Vector2f{0,35},14,this->derecha);
        this->proyectiles.push_back(nuevo);
        this->s_disparo.play();
    }
}




Inca::Inca()
{
    //ctor
}

Inca::~Inca()
{
    //dtor
}
