#ifndef CLEOPATRA_H
#define CLEOPATRA_H
#include <Personaje.h>
#include <light_arrow.h>
#include <Objeto_animado.h>
class Cleopatra: public Personaje
{
    public:
        Cleopatra(std::string , float, float ,sf::Event * , sf::RenderWindow * , int ** ,float ,float, bool);
        Cleopatra();
        void update(vector<Nave*>);
        void verif_disparos();
        void Mover();
        void update_proyectiles();
        void disparar();
        void animar(float);
        void verif_colisiones_proyectiles(vector<Nave*>);
        void skill_activado(vector<Nave*>);
        virtual ~Cleopatra();
    protected:
    private:
        sf::Clock * t_skill_piramide;
        bool skill_piramide_activ=false;
        bool skill_temp=false;
        bool skill_temp2=false;
        vector<sf::Texture*> texturas_a;
        vector<sf::Texture*> texturas_u;
        vector<sf::Texture*> texturas_hit_p;
        vector<sf::Texture*> texturas_anim;
};

#endif // CLEOPATRA_H
