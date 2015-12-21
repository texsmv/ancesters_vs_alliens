#include "Cleopatra.h"
#include <math.h>
float distan2(sf::Vector2f a, sf::Vector2f b){
    float dist=sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
    return dist;
}
Cleopatra::Cleopatra(std::string nombreArchivo, float alto, float ancho,sf::Event * evento, sf::RenderWindow * win, int ** matriz,float alto_bloque,float ancho_bloque, bool sec_player){
    this->alto=67;
    this->ancho=88;
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

    //////////////// --------------cargar texturas ---------------------

    string nomb_anim_der[4]={"walk2_0_cleo1.png","walk2_1_cleo1.png","walk2_2_cleo1.png","walk2_3_cleo1.png"};

    for (int i=0;i<4;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_der[i]);
        this->anim_der.push_back(nuevo);
    }

    string nomb_anim_izq[4]={"walk2_0_cleo2.png","walk2_1_cleo2.png","walk2_2_cleo2.png","walk2_3_cleo2.png"};
    for (int j=0;j<4;j++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_izq[j]);
        this->anim_izq.push_back(nuevo);
    }

    //////  stand_left
    string nomb_stand_der[5]={"stand2_0_cleo1.png","stand2_1_cleo1.png","stand2_2_cleo1.png","stand2_3_cleo1.png","stand2_4_cleo1.png"};

    for (int i=0;i<5;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_stand_der[i]);
        this->stand_der.push_back(nuevo);
    }
    //////  stand_left
    string nomb_stand_izq[5]={"stand2_0_cleo2.png","stand2_1_cleo2.png","stand2_2_cleo2.png","stand2_3_cleo2.png","stand2_4_cleo2.png"};

    for (int i=0;i<5;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_stand_izq[i]);
        this->stand_izq.push_back(nuevo);
    }
    ////// shoot_der
    string nomb_shoot_der[3]={"heal_0_cleo1.png","heal_1_cleo1.png","heal_2_cleo1.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_shoot_der[i]);
        this->shoot_der.push_back(nuevo);
    }
    ////// shoot_izq
    string nomb_shoot_izq[3]={"heal_0_cleo2.png","heal_1_cleo2.png","heal_2_cleo2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_shoot_izq[i]);
        this->shoot_izq.push_back(nuevo);
    }
    ////// swing_der
    /*string nomb_swing_der[3]={"swingO2_0.png","swingO2_1.png","swingO2_2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_swing_der[i]);
        this->swing_der.push_back(nuevo);
    }

    */

    buffer.loadFromFile("arrow.wav");
    s_disparo.setBuffer(buffer);
    buffer2.loadFromFile("arrow_impact.wav");
    s_impacto.setBuffer(buffer2);

    this->t_animacion=new sf::Clock;

    this->anim_actual=this->stand_der;

    this->setPosition(40*7,40*3);
    this->Coordenadas=this->getPosition();

    this->pet=new Pet(this->getPosition().x,this->getPosition().y);
    this->b_pet=true;

    string nombres_a[13]={"effect_0_p.png","effect_1_p.png","effect_2_p.png","effect_3_p.png","effect_4_p.png","effect_5_p.png","effect_6_p.png","effect_7_p.png","effect_8_p.png","effect_9_p.png","effect_10_p.png","effect_11_p.png","effect_12_p.png"};
    for (int i=0;i<13;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas_a.push_back(nuevo);
        this->texturas_a.at(i)->loadFromFile(nombres_a[i]);
    }

    string nombres_u[22]={"screen_0.png","screen_1.png","screen_2.png","screen_3.png","screen_4.png","screen_5.png","screen_6.png","screen_7.png","screen_8.png","screen_9.png","screen_10.png",
            "screen_11.png","screen_12.png","screen_13.png","screen_14.png","screen_15.png","screen_16.png","screen_17.png","screen_18.png","screen_19.png","screen_20.png","screen_21.png"};

    for (int i=0;i<22;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas_u.push_back(nuevo);
        this->texturas_u.at(i)->loadFromFile(nombres_u[i]);
    }

    string nombres_hit_p[5]={"hit.0_0_p.png","hit.0_1_p.png","hit.0_2_p.png","hit.0_3_p.png","hit.0_4_p.png"};
    for (int i=0;i<5;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas_hit_p.push_back(nuevo);
        this->texturas_hit_p.at(i)->loadFromFile(nombres_hit_p[i]);
    }
    string nombres_anim[3]={"hit.0_0_l.png","hit.0_1_l.png","hit.0_2_l.png"};
    for (int i=0;i<3;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas_anim.push_back(nuevo);
        this->texturas_anim.at(i)->loadFromFile(nombres_anim[i]);
    }
}




void Cleopatra::update(vector<Nave*>naves){

    this->anim_anterior=this->anim_actual;
    this->Mover();
    this->verif_disparos();


    if(this->counter_ultimate>2500){
        this->ultimate=true;
    }

//-----------Objetos-----------
    this->update_obj_animados();
    this->skill_activado(naves);

// ----------Pet------------

    this->update_pet();
    this->draw_pet();
}

void Cleopatra::animar(float t){
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

void Cleopatra::skill_activado(vector <Nave*> naves){
    if (this->skill_piramide_activ==true){
        this->t_skill_piramide=new sf::Clock;
        this->skill_temp=true;
        this->skill_piramide_activ=false;
    }

    if (this->skill_temp==true){
        if (this->t_skill_piramide->getElapsedTime().asSeconds()>1.5&&this->skill_temp2==false){


            Obj_anim_temp* ult = new Obj_anim_temp(texturas_u, 22,100,0,0.1,2);
            this->efectos.push_back(ult);
            this->skill_temp2=true;

        }

        if (this->t_skill_piramide->getElapsedTime().asSeconds()>2.5){
            for (int i=0;i<naves.size();i++){

                Obj_anim_temp* nuevo = new Obj_anim_temp(texturas_hit_p, 5,naves.at(i)->getPosition().x-naves.at(i)->ancho,naves.at(i)->getPosition().y-naves.at(i)->alto,0.1,2);
                this->efectos.push_back(nuevo);
                naves.at(i)->vida-=40;
                this->skill_temp2=false;
                this->score+=154;
            }
            this->skill_temp=false;
        }
    }


}

void Cleopatra::verif_disparos(){
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&ultimate==true){
        Obj_anim_temp * skill=new Obj_anim_temp(texturas_a, 13,this->getPosition().x-60,this->getPosition().y-150,0.13,1.5);
        this->efectos.push_back(skill);

        this->ultimate=false;
        this->counter_ultimate=0;
        this->skill_piramide_activ=true;
    }
}

void Cleopatra::Mover(){


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

void Cleopatra::verif_colisiones_proyectiles(vector<Nave*> naves){

    int num_imag_anim=3;
    float t_anim=0.2;
    for (int i=0;i<this->proyectiles.size();i++){
        for(int j=0;j<naves.size();j++){
            if (distan2(this->proyectiles.at(i)->punto_medio,naves.at(j)->punto_medio)<this->proyectiles.at(i)->rango_colision){
                this->s_impacto.play();
                this->proyectiles.at(i)->start_last_anim=true;
                if(naves.at(j)->vida>0){
                    this->score=this->score+134;
                    this->counter_ultimate+=40;
                }

                naves.at(j)->vida-=this->proyectiles.at(i)->damage;
                Obj_anim_temp * nuevo= new Obj_anim_temp(texturas_anim,num_imag_anim,proyectiles.at(i)->getPosition().x+proyectiles.at(i)->ancho/2,proyectiles.at(i)->getPosition().y,0.1,t_anim);
                this->efectos.push_back(nuevo);
        }

    }
    }
}


void Cleopatra::update_proyectiles(){
    for (int i=0;i<this->proyectiles.size();i++){

        proyectiles.at(i)->update();
     }
    for (int i=0;i<this->proyectiles.size();i++){
        if(this->proyectiles.at(i)->t_vida->getElapsedTime().asSeconds()>2){
            delete this->proyectiles.at(i);
            this->proyectiles.erase(proyectiles.begin()+i);
        }
        else{
                    if(this->proyectiles.at(i)->getPosition().y<1200&&this->proyectiles.at(i)->getPosition().x>0&&this->proyectiles.at(i)->getPosition().y<800&&this->proyectiles.at(i)->getPosition().x>0){
                        if( *( *(this->matriz + int(this->proyectiles.at(i)->getPosition().y+20)/40 ) + int(this->proyectiles.at(i)->getPosition().x+30)/40)==0 ){
                            delete this->proyectiles.at(i);
                            this->proyectiles.erase(proyectiles.begin()+i);
                        }
                    }


        }

    }

}

void Cleopatra::disparar(){
    sf::Time t1;
    t1= sf::seconds(0.3);
    if (this->velocidad_ataque->getElapsedTime()>t1){
        this->velocidad_ataque->restart();
        Proyectil * nuevo= new light_arrow(evento,Coordenadas+sf::Vector2f{0,35},this->derecha);
        this->proyectiles.push_back(nuevo);
        this->s_disparo.play();

    }
}

Cleopatra::Cleopatra()
{
    //ctor
}

Cleopatra::~Cleopatra()
{
    //dtor
}
