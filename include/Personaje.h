#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <Objeto.h>
#include <Obj_anim_temp.h>
#include <Proyectil.h>
#include <green_arrow.h>
#include <Nave.h>
#include <Pet.h>
#include <Objeto_animado.h>
class Personaje : public Objeto
{
    public:
        Personaje();
        Personaje(string, float,float,sf::Event*, sf::RenderWindow*,int**,float,float, bool);
        virtual void update(vector<Nave*>);
        void Mover();
        virtual void animar(float);
        virtual void disparar();
        virtual void draw_proyectiles();
        virtual void verif_disparos();
        virtual void update_proyectiles();
        void eliminar_proyectiles();
        virtual ~Personaje();
        virtual void verif_colisiones_proyectiles(vector<Nave*>);
        void setEvento(sf::Event *);
        void draw_obj_animados();
        void update_obj_animados();
        void update_pet();
        void ataque_melee();
        void draw_pet();
        void set_naves_pointers(vector<Nave*>);
        virtual void skill_activado(vector<Nave*>);
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
        vector <sf::Texture*> swing_izq;
        vector <Nave*> naves;
        int ** matriz;
        int alto_bloque, ancho_bloque;
        vector <Proyectil*> proyectiles;
        vector <Obj_anim_temp*> efectos;
        bool draw_bala=false;
        int saltos=0;
        bool derecha=true;
        int score=0;
        bool b_pet=false;
        bool saltar=false;
        int counter_ultimate=0;
        bool ultimate=false;
        Pet * pet;
        sf::Clock * t_salto;
        sf::Clock * t2_salto;
        sf::Clock * velocidad_ataque_melee;
        sf::Vector2f last_posicion;
        sf::Clock *velocidad_ataque ;
        sf::Keyboard::Key k_up, k_down, k_left, k_right;
        bool sec_player=false;
        Obj_anim_temp * ult;
        float rango_melee;
        float damage_melee;
    friend class Juego;
    friend class Arquero;
    friend class Inca;
    friend class Cleopatra;
};

#endif // PERSONAJE_H
