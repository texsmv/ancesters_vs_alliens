#ifndef NAVE_H
#define NAVE_H
#include <Objeto.h>

class Nave: public Objeto
{
    public:
        Nave(string, float, float, int**);
        Nave();
        void update();
        void verif_choque(float);
        void muerte();
        void animar(float);
        virtual ~Nave();
    protected:
    private:
        sf::SoundBuffer buffer;
        sf::Sound bip;
        sf::Clock * mov_nave;
        sf::Clock * mov2_nave;
        int t_cambio;
        int var_mov;
        int angle;
        int** matriz;
        bool start_destroy=false;
        bool destroy=false;
        sf::Clock * t_muerte;
        sf::Clock * t_vida;
        sf::Texture * textura_hit;
        vector <sf::Texture*> anim_muerte;
        vector <sf::Texture*> anim_mov;
        vector <sf::Texture*> anim_die;
        float vida=40;
        float last_vida=40;
    friend class Arquero;
    friend class Juego;
    friend class Personaje;
    friend class Cleopatra;
};

#endif // NAVE_H
