#ifndef LIGHT_ARROW_H
#define LIGHT_ARROW_H
#include <Proyectil.h>

class light_arrow:public Proyectil
{
    public:
        light_arrow();
        light_arrow(sf::Event*,sf::Vector2f, bool);
        void update();
        virtual ~light_arrow();
    protected:
    private:
        bool pass_init_anim=false;
        string nombres_anim[3]={"hit.0_0_l.png","hit.0_1_l.png","hit.0_2_l.png"};
        int num_imag_anim=3;
        float t_anim=2;


};

#endif // LIGHT_ARROW_H
