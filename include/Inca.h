#ifndef INCA_H
#define INCA_H
#include <Personaje.h>

class Inca: public Personaje
{
    public:
        Inca(std::string , float , float,sf::Event *, sf::RenderWindow * , int **,float ,float , bool);
        Inca();
        void update(vector<Nave*>);
        void verif_disparos();
        void Mover();
        void update_proyectiles();
        void disparar();
        void animar(float);
        virtual ~Inca();
    protected:
    private:
};

#endif // INCA_H
