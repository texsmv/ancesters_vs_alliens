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
    std::string nombres_bloques[]={"bsc_0.png","bsc_1.png","bsc_2.png","bsc_3.png","bsc_4.png","bsc_5.png","cielo_2.png","Corner1_0.png","Corner1_1.png","Corner1_2.png","Corner1_3.png",
    "enH0_0.png","Corner2_0.png","Corner2_1.png","Corner2_2.png","Corner2_3.png","Grass1_0.png","enV1_1.png"};
    this->filas=filas;
    this->columnas=columnas;
    this->win=win;
    this->evento=evento;
    this->matriz=matriz;
    this->mapa= new Mapa(40, 40,nombres_bloques,nombres_suelo,18,28,30, matriz, win);
    this->tipo_letra.loadFromFile("Chardons.ttf");
    this->player= new Cleopatra("stand1_0.png", 66, 64,evento, win, matriz,40,40,false);


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
    /*
    Objeto_animado *nuevo;
        string nombres_u[22]={"screen_0.png","screen_1.png","screen_2.png","screen_3.png","screen_4.png","screen_5.png","screen_6.png","screen_7.png","screen_8.png","screen_9.png","screen_10.png",
        "screen_11.png","screen_12.png","screen_13.png","screen_14.png","screen_15.png","screen_16.png","screen_17.png","screen_18.png","screen_19.png","screen_20.png","screen_21.png"};

        nuevo = new Objeto_animado(nombres_u, 22,400,100,0.1,2);
    obj_animados.push_back(nuevo);
*/
    //////Texturas para las animaciones
    //// walk_left



    if(this->multiplayer==true){
        this->player2=new Arquero("walk1_0_i.png", 65, 82,evento, win, matriz,40,40,true);

    }


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

void Juego::verif_naves(){
    for(int i=0;i<this->naves.size();i++){
        if(this->naves.at(i)->destroy==true||this->naves.at(i)->t_vida->getElapsedTime().asSeconds()>14){
            delete this->naves.at(i);
            this->naves.erase(naves.begin()+i);
            break;
        }
        if(this->naves.at(i)->vida<=0){
            this->naves.at(i)->start_destroy=true;
        }
    }
}
void Juego::colisiones(){
    for (int i=0;i<this->player->proyectiles.size();i++){
        for(int j=0;j<this->naves.size();j++){
            if (distancia(this->player->proyectiles.at(i)->punto_medio,this->naves.at(j)->punto_medio)<this->player->proyectiles.at(i)->rango_colision){
                this->player->s_impacto.play();
                delete this->player->proyectiles.at(i);
                this->player->proyectiles.erase(player->proyectiles.begin()+i);
                this->naves.at(j)->start_destroy=true;
                this->player->score=this->player->score+134;


                break;
            }

        }

    }
    if(this->multiplayer==true){
        for (int i=0;i<this->player2->proyectiles.size();i++){
            for(int j=0;j<this->naves.size();j++){
                if (distancia(this->player2->proyectiles.at(i)->punto_medio,this->naves.at(j)->punto_medio)<this->player2->proyectiles.at(i)->rango_colision){
                    this->player2->s_impacto.play();
                    delete this->player2->proyectiles.at(i);
                    this->player2->proyectiles.erase(player2->proyectiles.begin()+i);
                    this->naves.at(j)->start_destroy=true;
                    this->player2->score=this->player2->score+134;
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
    this->win->draw(*player);
    this->player->draw_proyectiles();



    for(int i=0;i<obj_animados.size();i++){
        win->draw(*obj_animados.at(i));
    }

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
        float  dist=distancia(this->casa->punto_medio,this->naves.at(i)->getPosition());
        if(dist<80&&this->naves.at(i)->start_destroy!=true){
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
        this->player->update(this->naves);
        this->player->update_proyectiles();

        if (this->multiplayer==true){
            this->player2->animar(0.5);
            this->player2->update(this->naves);
            this->player2->update_proyectiles();
        }

        for(int i=0;i<this->naves.size();i++){
            this->naves.at(i)->verif_choque(40);
            this->naves.at(i)->update();

        }
        this->verifHogar();

        this->crearNaves();
        //this->colisiones();

        this->player->verif_colisiones_proyectiles(this->naves);
        this->player2->verif_colisiones_proyectiles(this->naves);
        this->player->eliminar_proyectiles();
        this->player2->eliminar_proyectiles();
        this->verif_naves();

        //this->verif_naves();
    }
    if (this->mostrar==true){
        this->draw();
    }


}

void Juego::crearNaves(){
    if (this->t_naves->getElapsedTime().asSeconds()>0.4){
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
