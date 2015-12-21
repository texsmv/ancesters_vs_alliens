#include "Arquero.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
int numero_aleatorio_n(sf::Clock*reloj , int n){
        int num= int (reloj->getElapsedTime().asMicroseconds())%n;

        return num;
}


int ran_Number2(int x){

    std::srand(std::time(0));
    int h = std::rand()%(x);

    return h;
}
float distan3(sf::Vector2f a, sf::Vector2f b){
    float dist=sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
    return dist;
}




Arquero::Arquero(std::string nombreArchivo, float alto, float ancho,sf::Event * evento, sf::RenderWindow * win, int ** matriz,float alto_bloque,float ancho_bloque, bool sec_player){
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
    this->damage_melee=30;
    this->rango_melee=90;
    this->particulas=new ParticleSystem(10000);
    this->t_particulas= new sf::Clock;

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

    string nomb_anim_der[4]={"walk1_0.png","walk1_1.png","walk1_2.png","walk1_3.png"};

    for (int i=0;i<4;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_der[i]);
        this->anim_der.push_back(nuevo);
    }

    string nomb_anim_izq[4]={"walk2_0.png","walk2_1.png","walk2_2.png","walk2_3.png"};
    for (int j=0;j<4;j++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_izq[j]);
        this->anim_izq.push_back(nuevo);
    }

    //////  stand_left
    string nomb_stand_der[5]={"stand1_0.png","stand1_1.png","stand1_2.png","stand1_3.png","stand1_4.png"};

    for (int i=0;i<5;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_stand_der[i]);
        this->stand_der.push_back(nuevo);
    }
    //////  stand_left
    string nomb_stand_izq[5]={"stand2_0.png","stand2_1.png","stand2_2.png","stand2_3.png","stand2_4.png"};

    for (int i=0;i<5;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_stand_izq[i]);
        this->stand_izq.push_back(nuevo);
    }
    ////// shoot_der
    string nomb_shoot_der[3]={"shoot1_0.png","shoot1_1.png","shoot1_2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_shoot_der[i]);
        this->shoot_der.push_back(nuevo);
    }
    ////// shoot_izq
    string nomb_shoot_izq[3]={"shoot2_0.png","shoot2_1.png","shoot2_2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_shoot_izq[i]);
        this->shoot_izq.push_back(nuevo);
    }
    ////// swing_der
    string nomb_swing_der[3]={"swingO2_0_m.png","swingO2_1_m.png","swingO2_2_m.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_swing_der[i]);
        this->swing_der.push_back(nuevo);
    }
    string nomb_swing_izq[3]={"swingO2_0_m_1.png","swingO2_1_m_1.png","swingO2_2_m_1.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_swing_izq[i]);
        this->swing_izq.push_back(nuevo);
    }

    buffer.loadFromFile("arrow.wav");
    s_disparo.setBuffer(buffer);
    buffer2.loadFromFile("arrow_impact.wav");
    s_impacto.setBuffer(buffer2);

    this->t_animacion=new sf::Clock;

    this->anim_actual=this->stand_der;

    this->setPosition(40*7,40*3);
    this->Coordenadas=this->getPosition();

    string nombres_impact[3]={"hit1.0_0_AR.png","hit1.0_1_AR.png","hit1.0_2_AR.png"};
    for (int i=0;i<3;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas_skill_impact.push_back(nuevo);
        this->texturas_skill_impact.at(i)->loadFromFile(nombres_impact[i]);
    }
    string nombres_skill[12]={"effect1_0_AR.png","effect1_1_AR.png","effect1_2_AR.png","effect1_3_AR.png","effect1_4_AR.png","effect1_5_AR.png","effect1_6_AR.png","effect1_7_AR.png","effect1_8_AR.png","effect1_9_AR.png","effect1_10_AR.png","effect1_11_AR.png"};
    for (int i=0;i<12;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->texturas_skill_anim.push_back(nuevo);
        this->texturas_skill_anim.at(i)->loadFromFile(nombres_skill[i]);
    }
    string arrow_nom[2]={"special1.0_0_AR.png","special1.0_0_AR.png"};
    for (int i=0;i<2;i++){
        sf::Texture * nuevo=new sf::Texture;
        this->textura_arrow_blue.push_back(nuevo);
        this->textura_arrow_blue.at(i)->loadFromFile(arrow_nom[i]);
    }
    this->velocidad_ataque_melee=new sf::Clock;

}





void Arquero::update(vector<Nave*> naves){
    this->set_naves_pointers(naves);
    this->anim_anterior=this->anim_actual;
    this->Mover();
    this->verif_disparos();
    if(this->counter_ultimate>500){
        this->ultimate=true;
    }

    this->skill_activado(naves);
    this->update_obj_animados(naves);
    this->draw_obj_animados();


}

void Arquero::skill_activado(vector<Nave*> naves){
    if(this->skill_arrows_rain_activate==true){
        this->t_skill_arrows_rain=new sf::Clock;
        this->skill_temp=true;
        this->skill_arrows_rain_activate=false;
        this->frec_arrows_rain=new sf::Clock;
    }
    if (this->skill_temp==true){

        if (this->t_skill_arrows_rain->getElapsedTime().asSeconds()>1.8&&this->t_skill_arrows_rain->getElapsedTime().asSeconds()<9&&frec_arrows_rain->getElapsedTime().asSeconds()>0.04){
            Obj_anim_temp * nuevo= new Obj_anim_temp(textura_arrow_blue,2,numero_aleatorio_n(this->t_skill_arrows_rain,1200),-20,0.1,2);
            nuevo->esFlecha=true;
            this->efectos.push_back(nuevo);
            this->frec_arrows_rain->restart();
        }


    }

}

void Arquero::update_obj_animados(vector<Nave*>naves){
    for(int i=0;i<this->efectos.size();i++){
        if(this->efectos.at(i)->esFlecha==true){

            this->efectos.at(i)->setPosition(efectos.at(i)->getPosition()+sf::Vector2f{5,12});
            for (int j=0;j<naves.size();j++){
                if (distan3(this->efectos.at(i)->getPosition()+sf::Vector2f{35,75},naves.at(j)->getPosition())<25){
                    naves.at(j)->vida-=10;
                    this->efectos.at(i)->destroy=true;
                    Obj_anim_temp*nuevo= new Obj_anim_temp(texturas_skill_impact,3,efectos.at(i)->getPosition().x,efectos.at(i)->getPosition().y,0.1,0.3);
                    this->efectos.push_back(nuevo);

                }
                if(this->efectos.at(i)->getPosition().y<1200&&this->efectos.at(i)->getPosition().x>0&&this->efectos.at(i)->getPosition().y<800&&this->efectos.at(i)->getPosition().x>0){
                    if( *( *(this->matriz + int(this->efectos.at(i)->getPosition().y+20)/40 ) + int(this->efectos.at(i)->getPosition().x+30)/40)==0 ){
                        this->efectos.at(i)->destroy=true;
                        Obj_anim_temp*nuevo= new Obj_anim_temp(texturas_skill_impact,3,efectos.at(i)->getPosition().x-50,efectos.at(i)->getPosition().y-100,0.1,0.3);
                        this->efectos.push_back(nuevo);

                    }
                }
            }
        }

        else{
        this->efectos.at(i)->update();
        }
    }
    for(int i=0;i<this->efectos.size();i++){
        if(this->efectos.at(i)->destroy==true){
            delete this->efectos.at(i);
            this->efectos.erase(efectos.begin()+i);
        }
    }
}

void Arquero::animar(float t){
    if(this->anim_actual==shoot_der||this->anim_actual==shoot_izq){
        t=0.1;
    }

    if(this->anim_actual==swing_der||this->anim_actual==swing_izq){
        t=0.25;
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




void Arquero::verif_disparos(){
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&&ultimate==true){
        Obj_anim_temp * skill=new Obj_anim_temp(texturas_skill_anim,12 ,this->getPosition().x+30,this->getPosition().y-90,0.13,1.5);
        this->efectos.push_back(skill);

        this->ultimate=false;
        this->counter_ultimate=0;
        this->skill_arrows_rain_activate=true;

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
        if(this->derecha==true){
            this->anim_actual=swing_der;
        }
        else{
            this->anim_actual=swing_izq;
        }
        this->ataque_melee();
    }
}

void Arquero::verif_colisiones_proyectiles(vector<Nave*> naves){
    for (int i=0;i<this->proyectiles.size();i++){
        for(int j=0;j<naves.size();j++){
            if (distan3(this->proyectiles.at(i)->punto_medio,naves.at(j)->punto_medio)<this->proyectiles.at(i)->rango_colision){
                this->s_impacto.play();
                this->proyectiles.at(i)->start_last_anim=true;
                if(naves.at(j)->vida>0){
                    this->score=this->score+134;
                    this->counter_ultimate+=20;
                }
                naves.at(j)->vida-=this->proyectiles.at(i)->damage;


        }

    }
    }
}

void Arquero::Mover(){


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


void Arquero::update_proyectiles(){
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

void Arquero::disparar(){
    sf::Time t1;
    t1= sf::seconds(0.3);
    if (this->velocidad_ataque->getElapsedTime()>t1){
        this->velocidad_ataque->restart();
        Proyectil * nuevo= new green_arrow(evento,Coordenadas+sf::Vector2f{0,35},this->derecha);
        this->proyectiles.push_back(nuevo);
        this->s_disparo.play();
    }
}

void Arquero::draw_proyectiles(){

    for (int i=0;i<this->proyectiles.size();i++){

        win->draw(*proyectiles.at(i));
    }
    this->draw_obj_animados();
    particulas->setEmitter(sf::Vector2f{600,100});
    sf::Time elapsed = t_particulas->restart();
    particulas->update(elapsed);
    win->draw(*particulas);
}

Arquero::Arquero()
{
    //ctor
}

Arquero::~Arquero()
{
    //dtor
}
