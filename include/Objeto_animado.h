#ifndef OBJETO_ANIMADO_H
#define OBJETO_ANIMADO_H
#include <Objeto.h>

class Objeto_animado : public Objeto
{
    public:
        Objeto_animado();
        Objeto_animado(string[],int, float, float, float, int);
        void animar();
        virtual ~Objeto_animado();
    protected:
    private:
        vector <sf::Texture *> texturas;
        float t_frecuencia;
        sf::Clock * r_frecuencia;
        int num_imag;
        int pos_imag=0;
};

#endif // OBJETO_ANIMADO_H
