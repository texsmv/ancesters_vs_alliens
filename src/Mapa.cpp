#include "Mapa.h"
#include <vector>


Mapa::Mapa( float alto_bloque, float ancho_bloque,std::string nombres[],std::string nombres_bloque[],int num_imagenes ,int filas, int columnas, int**matriz, sf::RenderWindow*win)
{
    this-> columnas=columnas;
    this-> filas=filas;
    this-> ancho_bloque=ancho_bloque;
    this-> alto_bloque=alto_bloque;
    this-> Matriz=matriz;
    this->imagenes=nombres;
    this->num_imagenes=num_imagenes;
    this->win=win;
    this->nombres_bloques=nombres_bloque;
    this->nombres_bloques=nombres_bloques;
    sf::Texture * texturas[num_imagenes];
    images=new sf::Sprite*[num_imagenes];

/*

    sf::Texture * texturas2[14];
    bloques_suelo=new sf::Sprite*[14];

    for(int i=0;i<14;i++){
        texturas2[i]=new sf::Texture;
        bloques_suelo[i]= new sf::Sprite;
        if(!texturas2[i]->loadFromFile(*(nombres_bloques+i)))
            std::cout<<"No se pudo cargar la imagen personaje"<<std::endl;
        bloques_suelo[i]->setTexture(*(texturas2[i]));
    }

    */

    for(int i=0;i<num_imagenes;i++){
        texturas[i]=new sf::Texture;
        images[i]=new sf::Sprite;
        if(!texturas[i]->loadFromFile(*(imagenes+i)))
            std::cout<<"No se pudo cargar la imagen personaje"<<std::endl;
        images[i]->setTexture(*(texturas[i]));
    }
}

void Mapa::dibujar()
{




    for (int i=0;i<filas;i++){
        for (int j=0;j<columnas;j++){
            for (int k=0;k<num_imagenes;k++){
                if(*(*(Matriz+i)+j)==1){

                    images[k]->setPosition(j*alto_bloque,i*ancho_bloque);
                    win->draw(*(images[k]));
                }


                else if(*(*(Matriz+i)+j)==k){

                    images[k]->setPosition(j*alto_bloque,i*ancho_bloque);
                    win->draw(*(images[k]));
                }
                else if(*(*(Matriz+i)+j)==9){
                    images[1]->setPosition(j*alto_bloque,i*ancho_bloque);
                    win->draw(*(images[1]));

                }

            }
        }
    }


}

Mapa::~Mapa()
{
    //dtor
}
