#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <Objeto.h>
#include <Proyectil.h>

class Personaje : public Objeto
{
    public:
        Personaje();
        Personaje(string, float,float,sf::Event*, sf::RenderWindow*,int**,float,float, bool);
        void update();
        void Mover();
        void animar(float);
        void disparar();
        void draw_proyectiles();
        void update_proyectiles();
        virtual ~Personaje();
        void setEvento(sf::Event *);
    protected:
    private:
        sf::SoundBuffer buffer;
        sf::Sound  s_disparo;
        sf::SoundBuffer buffer2;
        sf::Sound  s_impacto;
        sf::Vector2f velocidad_eje_x={0,0};
        sf::Vector2f velocidad_eje_y={0,0};
        sf::Vector2f gravedad={0,2};
        sf::Vector2f salto;
        vector <sf::Texture*> anim_der;
        vector <sf::Texture*> shoot_der;
        vector <sf::Texture*> anim_izq;
        vector <sf::Texture*> stand_der;
        vector <sf::Texture*> stand_izq;
        vector <sf::Texture*> shoot_izq;
        vector <sf::Texture*> swing_der;
        int ** matriz;
        int alto_bloque, ancho_bloque;
        vector <Proyectil*> proyectiles;
        bool draw_bala=false;
        int saltos=0;
        bool derecha=true;
        int score=0;
        bool saltar=false;
        sf::Clock * t_salto;
        sf::Clock * t2_salto;
        sf::Vector2f last_posicion;
        sf::Clock *velocidad_ataque ;
        sf::Keyboard::Key k_up, k_down, k_left, k_right;
        bool sec_player=false;
    friend class Juego;

};

#endif // PERSONAJE_H
