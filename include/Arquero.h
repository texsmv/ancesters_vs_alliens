#ifndef ARQUERO_H
#define ARQUERO_H
#include <Personaje.h>
#include <green_arrow.h>
#include <Nave.h>
#include <Obj_anim_temp.h>
#include <ParticleSystem.h>

class Arquero: public Personaje
{
    public:
        Arquero(std::string , float , float,sf::Event *, sf::RenderWindow * , int **,float ,float , bool);
        Arquero();
        void verif_disparos();
        void update(vector<Nave*>);
        void verif_colisiones_proyectiles(vector<Nave*>);
        void Mover();
        void update_proyectiles();
        void disparar();
        void animar(float);
        void update_obj_animados(vector<Nave*>);
        void skill_activado(vector<Nave*>);
        void draw_proyectiles();
        virtual ~Arquero();
    protected:
    private:
        sf::Clock * t_skill_arrows_rain;
        bool skill_arrows_rain_activate=false;
        bool skill_temp=false;
        bool skill_temp2=false;
        vector <sf::Texture*> texturas_skill_impact;
        vector <sf::Texture*> texturas_skill_anim;
        vector <Objeto_animado*> arrows_skill;
        vector <sf::Texture*> textura_arrow_blue;
        sf::Texture* arrow_blue;
        sf::Clock * t_particulas;
        sf::Clock * frec_arrows_rain;
        sf::Sprite * arrow;
        ParticleSystem * particulas;

};

#endif // ARQUERO_H
