#ifndef GREEN_ARROW_H
#define GREEN_ARROW_H
#include <Proyectil.h>

class green_arrow: public Proyectil
{
    public:
        green_arrow(sf::Event*,sf::Vector2f, bool);
        green_arrow();
        void update();
        virtual ~green_arrow();
    protected:
    private:
        bool b_anim_inicial=true;

};

#endif // GREEN_ARROW_H
