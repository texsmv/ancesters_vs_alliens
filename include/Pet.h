#ifndef PET_H
#define PET_H
#include <Objeto.h>

class Pet: public Objeto
{
    public:
        Pet(float, float);
        Pet();
        void update();

        virtual ~Pet();
    protected:
    private:
        vector <sf::Texture*> anim_angry;
        vector <sf::Texture*> anim_stand;
        sf::Clock * t_atacar;
        bool atacando=false;
};

#endif // PET_H
