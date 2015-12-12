#ifndef JUEGO_H
#define JUEGO_H
#include <Personaje.h>
#include <Proyectil.h>
#include <Mapa.h>
#include <Nave.h>
#include <Objeto_animado.h>
#include <Hogar.h>

class Juego
{
    public:
        //Este constructor es largo, lo dividire en partes
        Juego(
        //primero las partes que son necesaras para todas las clases
        sf::RenderWindow*, sf::Event*, int**,int**,int,int
/*
        //necesarias para el mapa
        ,float, float,string[], int, int ,int ,
        // necesarias para personaje
        string, float, float,
        //Proyectil
        string, float, float , sf::Vector2f
*/





        );



        Juego();
        void verifHogar();
        void update();
        void setEvento(sf::Event*);
        void draw();
        void crearNaves();
        void colisiones();
        virtual ~Juego();
    protected:
    private:
        int filas;
        int columnas;
        vector <Objeto_animado *> obj_animados;
        Personaje * player;
        Personaje * player2;
        Mapa * mapa;
        sf::RenderWindow* win;
        sf::Event* evento;
        sf::Clock * clock;
        bool mostrar=true;
        bool actualizar=true;
        int ** matriz;
        bool multiplayer=true;
        sf::Clock * t_naves;
        vector <Nave*> naves;
        sf::SoundBuffer buffer;
        sf::Sound music;
        sf::Clock * t_music;
        Hogar * casa;
        sf::Font tipo_letra;
        sf::Text* score_1;
        sf::Text* score_2;

};

#endif // JUEGO_H
