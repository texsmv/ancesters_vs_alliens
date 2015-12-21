#ifndef MAPA_H
#define MAPA_H
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

class Mapa
{
    public:
        Mapa(float, float,std::string[],std::string[],int, int, int,int**,sf::RenderWindow*);
        void dibujar();
        virtual ~Mapa();
    private:
        int filas;
        int columnas;
        std::string* imagenes;
        float alto_bloque, ancho_bloque;
        int num_imagenes;
        sf::RenderWindow* win;
        int**Matriz;
        std::string* nombres_bloques;
        sf::Sprite ** images;
        sf::Sprite ** bloques_suelo;
        sf::Clock * t_inicio;
        sf::Sprite ** bloques;
        sf::Sprite * pasto;

        friend class Fantasma;

        friend class Pacman;
};

#endif // MAPA_H
