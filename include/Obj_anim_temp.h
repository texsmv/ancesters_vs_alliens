#ifndef OBJ_ANIM_TEMP_H
#define OBJ_ANIM_TEMP_H
#include <Objeto_animado.h>


class Obj_anim_temp: public Objeto_animado
{
    public:
        Obj_anim_temp(string [],int ,float , float ,float, float);
        Obj_anim_temp(vector<sf::Texture*>,int,float,float,float,float);
        Obj_anim_temp();
        void update();
        virtual ~Obj_anim_temp();
    protected:
    private:
        bool esFlecha=false;
        sf::Clock * c_vida;
        float   t_vida;
        friend class Arquero;
        friend class Personaje;

};

#endif // OBJ_ANIM_TEMP_H
