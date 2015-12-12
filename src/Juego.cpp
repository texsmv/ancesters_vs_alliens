#include "Juego.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
int ran_Number(int x){
    std::srand(std::time(0));
    int h = std::rand()%(x);

    return h;
}
float distancia(sf::Vector2f a, sf::Vector2f b){
    float dist=sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
    return dist;
}


Juego::Juego(sf::RenderWindow* win,sf::Event* evento, int** matriz, int** matriz_objetos,int filas,int columnas){
    std::string nombres_suelo[]={"pasto.png"};
    std::string nombres_bloques[]={"pasto.png","cielo.png"};
    this->filas=filas;
    this->columnas=columnas;
    this->win=win;
    this->evento=evento;
    this->matriz=matriz;
    this->mapa= new Mapa(40, 40,nombres_bloques,nombres_suelo,2,28,30, matriz, win);
    this->tipo_letra.loadFromFile("Chardons.ttf");
    this->player= new Personaje("stand1_0.png", 66, 64,evento, win, matriz,40,40,false);
    if(multiplayer==true){
        this->player2=new Personaje("walk1_0_i.png", 65, 82,evento, win, matriz,40,40,true);
    }

    this->t_naves=new sf::Clock;
    string nombres_planta[6]={"flame_a_0001.png","flame_a_0002.png","flame_a_0003.png","flame_a_0004.png","flame_a_0005.png","flame_a_0006.png"};
    for (int i=0;i<28;i++){
        for (int j=0;j<30;j++){

            switch (*(*(matriz_objetos+i)+j)){

                case 3 : this->casa = new Hogar("casa.png",40*j,40*(i+1),20);
                        break;

                case 2 : Objeto_animado * nuevo=new Objeto_animado(nombres_planta,6,40*j,40*i,0.5,j%3);
                        this->obj_animados.push_back(nuevo);
                        break;

            }
        }
    }


    //////Texturas para las animaciones
    //// walk_left
    string nomb_anim_der[4]={"walk1_0.png","walk1_1.png","walk1_2.png","walk1_3.png"};

    for (int i=0;i<4;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_der[i]);
        this->player->anim_der.push_back(nuevo);
    }

    string nomb_anim_izq[4]={"walk2_0.png","walk2_1.png","walk2_2.png","walk2_3.png"};
    for (int j=0;j<4;j++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_anim_izq[j]);
        this->player->anim_izq.push_back(nuevo);
    }

    //////  stand_left
    string nomb_stand_der[5]={"stand1_0.png","stand1_1.png","stand1_2.png","stand1_3.png","stand1_4.png"};

    for (int i=0;i<5;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_stand_der[i]);
        this->player->stand_der.push_back(nuevo);
    }
    //////  stand_left
    string nomb_stand_izq[5]={"stand2_0.png","stand2_1.png","stand2_2.png","stand2_3.png","stand2_4.png"};

    for (int i=0;i<5;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_stand_izq[i]);
        this->player->stand_izq.push_back(nuevo);
    }
    ////// shoot_der
    string nomb_shoot_der[3]={"shoot1_0.png","shoot1_1.png","shoot1_2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_shoot_der[i]);
        this->player->shoot_der.push_back(nuevo);
    }
    ////// shoot_izq
    string nomb_shoot_izq[3]={"shoot2_0.png","shoot2_1.png","shoot2_2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_shoot_izq[i]);
        this->player->shoot_izq.push_back(nuevo);
    }
    ////// swing_der
    string nomb_swing_der[3]={"swingO2_0.png","swingO2_1.png","swingO2_2.png"};

    for (int i=0;i<3;i++){
        sf::Texture* nuevo=new sf::Texture;
        nuevo->loadFromFile(nomb_swing_der[i]);
        this->player->swing_der.push_back(nuevo);
    }


    if(this->multiplayer==true){
        //// walk_left
        string nomb_anim_der_i[4]={"walk1_0_i.png","walk1_1_i.png","walk1_2_i.png","walk1_3_i.png"};

        for (int i=0;i<4;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_anim_der_i[i]);
            this->player2->anim_der.push_back(nuevo);
        }

        string nomb_anim_izq_i[4]={"walk2_0_i.png","walk2_1_i.png","walk2_2_i.png","walk2_3_i.png"};
        for (int j=0;j<4;j++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_anim_izq_i[j]);
            this->player2->anim_izq.push_back(nuevo);
        }

        //////  stand_left
        string nomb_stand_der_i[5]={"stand1_0_i.png","stand1_1_i.png","stand1_2_i.png","stand1_3_i.png","stand1_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_stand_der_i[i]);
            this->player2->stand_der.push_back(nuevo);
        }
        //////  stand_left
        string nomb_stand_izq_i[5]={"stand2_0_i.png","stand2_1_i.png","stand2_2_i.png","stand2_3_i.png","stand2_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_stand_izq_i[i]);
            this->player2->stand_izq.push_back(nuevo);
        }
        ////// shoot_der
        string nomb_shoot_der_i[5]={"shoot1_0_i.png","shoot1_1_i.png","shoot1_2_i.png","shoot1_3_i.png","shoot1_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_shoot_der_i[i]);
            this->player2->shoot_der.push_back(nuevo);
        }
        ////// shoot_izq
        string nomb_shoot_izq_i[5]={"shoot2_0_i.png","shoot2_1_i.png","shoot2_2_i.png","shoot2_3_i.png","shoot2_4_i.png"};

        for (int i=0;i<5;i++){
            sf::Texture* nuevo=new sf::Texture;
            nuevo->loadFromFile(nomb_shoot_izq_i[i]);
            this->player2->shoot_izq.push_back(nuevo);
        }
    }


    /////
    this->player->t_animacion=new sf::Clock;

    this->player->anim_actual=this->player->stand_der;

    //////
    if (this->multiplayer==true){
        this->player2->t_animacion=new sf::Clock;
        this->player2->anim_actual=this->player2->stand_der;
        this->player2->setPosition(40*4,40*6);
        this->player2->Coordenadas=this->player2->getPosition();
    }

    ///////

    this->player->setPosition(40*5,40*5);
    this->player->Coordenadas=this->player->getPosition();

    ////music
    t_music=new sf::Clock;
    buffer.loadFromFile("cosmo_canyon.wav");
    music.setBuffer(buffer);
    music.play();
    this->score_1= new sf::Text;
    this->score_1->setFont(tipo_letra);
    this->score_1->setPosition(1000,50);
    this->score_2= new sf::Text;
    this->score_2->setFont(tipo_letra);
    this->score_2->setPosition(1000,100);
}


void Juego::colisiones(){
    for (int i=0;i<this->player->proyectiles.size();i++){
        for(int j=0;j<this->naves.size();j++){
            if (distancia(this->player->proyectiles.at(i)->getPosition(),this->naves.at(j)->getPosition())<30){
                this->player->s_impacto.play();
                delete this->player->proyectiles.at(i);
                this->player->proyectiles.erase(player->proyectiles.begin()+i);
                this->naves.at(j)->start_destroy=true;
                this->player->score=this->player->score+134;


                break;
            }
            if(this->naves.at(j)->destroy==true){
                delete this->naves.at(j);
                this->naves.erase(naves.begin()+j);

                break;
            }

        }

    }
    if(this->multiplayer==true){
        for (int i=0;i<this->player2->proyectiles.size();i++){
            for(int j=0;j<this->naves.size();j++){
                if (distancia(this->player2->proyectiles.at(i)->getPosition(),this->naves.at(j)->getPosition())<30){
                    this->player2->s_impacto.play();
                    delete this->player2->proyectiles.at(i);
                    this->player2->proyectiles.erase(player2->proyectiles.begin()+i);
                    this->naves.at(j)->start_destroy=true;
                    this->player2->score=this->player2->score+134;
                    break;
                }
                if(this->naves.at(j)->destroy==true){
                    delete this->naves.at(j);
                    this->naves.erase(naves.begin()+j);
                    break;
                }

            }

        }
    }

}

void Juego::draw(){
    this->mapa->dibujar();

    this->win->draw(*casa);

    for(int i=0;i<this->naves.size();i++){
        this->win->draw(*this->naves.at(i));
    }
    this->player->draw_proyectiles();



    for(int i=0;i<obj_animados.size();i++){
        win->draw(*obj_animados.at(i));
    }
    this->win->draw(*player);
    if (this->multiplayer==true){
        this->win->draw(*player2);
        this->player2->draw_proyectiles();
    }

    this->win->draw(*score_1);
    this->win->draw(*score_2);
}

void Juego::verifHogar(){
    if (this->casa->vida==0){
        this->actualizar=false;
    }



    for (int i=0;i<this->naves.size();i++){
        float  dist=distancia(this->casa->Coordenadas,this->naves.at(i)->getPosition());
        if(dist<180&&this->naves.at(i)->start_destroy!=true){
            this->naves.at(i)->start_destroy=true;
            this->casa->quitarVida(1);
            if (this->casa->vida==16){
                string nombres_planta[6]={"flame_a_0001.png","flame_a_0002.png","flame_a_0003.png","flame_a_0004.png","flame_a_0005.png","flame_a_0006.png"};
                Objeto_animado * nuevo=new Objeto_animado(nombres_planta,6,this->casa->Coordenadas.x+14,this->casa->Coordenadas.y+23,0.5,1);
                nuevo->setScale(0.1,0.1);
                this->obj_animados.push_back(nuevo);
                }
            if (this->casa->vida==11){
                string nombres_planta[6]={"flame_a_0001.png","flame_a_0002.png","flame_a_0003.png","flame_a_0004.png","flame_a_0005.png","flame_a_0006.png"};
                Objeto_animado * nuevo=new Objeto_animado(nombres_planta,6,this->casa->Coordenadas.x+54,this->casa->Coordenadas.y-45,0.5,1);
                nuevo->setScale(0.2,0.2);
                this->obj_animados.push_back(nuevo);
                }
            if (this->casa->vida==7){
                string nombres_planta[6]={"flame_a_0001.png","flame_a_0002.png","flame_a_0003.png","flame_a_0004.png","flame_a_0005.png","flame_a_0006.png"};
                Objeto_animado * nuevo=new Objeto_animado(nombres_planta,6,this->casa->Coordenadas.x+79,this->casa->Coordenadas.y+34,0.5,1);
                nuevo->setScale(0.25,0.25);
                this->obj_animados.push_back(nuevo);
                }

        }
        if(this->naves.at(i)->destroy==true){
            delete this->naves.at(i);
            this->naves.erase(naves.begin()+i);

        }
    }
}


void Juego::update(){
    ////music
    this->score_1->setString(to_string(this->player->score));
    this->score_2->setString(to_string(this->player2->score));

    if(this->t_music->getElapsedTime().asSeconds()>=214){
        this->music.play();
        this->t_music->restart();
    }

    if (this->actualizar==true){

    for(int i=0;i<obj_animados.size();i++){
        obj_animados.at(i)->animar();
    }
    this->player->animar(0.5);
    this->player->update();
    this->player->update_proyectiles();

    if (this->multiplayer==true){
        this->player2->animar(0.5);
        this->player2->update();
        this->player2->update_proyectiles();
    }

    for(int i=0;i<this->naves.size();i++){
        this->naves.at(i)->verif_choque(40);
        this->naves.at(i)->update();
    }
    this->verifHogar();

    this->crearNaves();
    this->colisiones();
    }
    if (this->mostrar==true){
        this->draw();
    }


}

void Juego::crearNaves(){
    if (this->t_naves->getElapsedTime().asSeconds()>1){
        Nave * nuevo = new Nave("move_0.png",50,30,matriz);
        this->naves.push_back(nuevo);
        this->t_naves->restart();

    }

}





void Juego::setEvento(sf::Event*evento){
    this->evento=evento;
}
Juego::Juego()
{
    //ctor
}

Juego::~Juego()
{
    //dtor
}
