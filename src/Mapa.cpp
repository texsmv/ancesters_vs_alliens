#include "Mapa.h"
#include <vector>

int numero_aleatorio_n2(sf::Clock*reloj , int n){
        int num= int (reloj->getElapsedTime().asMicroseconds())%n;

        return num;
}

Mapa::Mapa( float alto_bloque, float ancho_bloque,std::string nombres[],std::string nombres_bloque[],int num_imagenes ,int filas, int columnas, int**matriz, sf::RenderWindow*win)
{
    this->t_inicio=new sf::Clock;
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
    this->bloques= new sf::Sprite*[this->filas];
    this->pasto=new sf::Sprite[this->columnas];






    for(int i=0;i<num_imagenes;i++){
        texturas[i]=new sf::Texture;
        images[i]=new sf::Sprite;
        if(!texturas[i]->loadFromFile(*(imagenes+i)))
            std::cout<<"No se pudo cargar la imagen personaje"<<std::endl;
        images[i]->setTexture(*(texturas[i]));
    }

    for(int i=0;i<this->columnas;i++){
        this->pasto[i].setTexture(*texturas[11]);
    }



    for (int i=0;i<filas;i++){
        this->bloques[i]= new sf::Sprite[this->columnas];
        for (int j=0;j<columnas;j++){

            for (int k=0;k<num_imagenes;k++){

                if(*(*(Matriz+i)+j)==1){
                    this->bloques[i][j].setTexture(*(texturas[6]));


//                    *(this->bloques[i]+j)->setTexture(*(texturas+k));

                }

                else if (*(*(Matriz+i)+j)==0&&*(*(Matriz+i)+j+1)==1&&j!=columnas-1){
                    //int ran_num2= numero_aleatorio_n2(this->t_inicio,5)+7;
                    this->bloques[i][j].setTexture(*(texturas[7]));




                }


                else if(*(*(Matriz+i)+j)==0){
                    int ran_num= numero_aleatorio_n2(this->t_inicio,6);
                    this->bloques[i][j].setTexture(*(texturas[ran_num]));

                }
                else if(*(*(Matriz+i)+j)==9){
                    this->bloques[i][j].setTexture(*(texturas[6]));

                }

            }
        }
    }



}

void Mapa::dibujar()
{




    for (int i=0;i<filas;i++){
        for (int j=0;j<columnas;j++){
            if(*(*(Matriz+i)+j)==0&&*(*(Matriz+i-1)+j)==1){
                if(*(*(Matriz+i)+j)==0&&*(*(Matriz+i)+j+1)==1&&j!=columnas-1){
                    this->images[6]->setPosition(j*40,i*40);
                    this->win->draw(*images[6]);
                }
                    this->bloques[i][j].setPosition(j*40,i*40);
                    win->draw((this->bloques[i][j]));
                if(*(*(Matriz+i)+j)==0&&*(*(Matriz+i)+j+1)==1&&j!=columnas-1){
                    this->images[16]->setPosition(j*40,i*40-16);
                    win->draw(*(this->images[16]));

                    }
                else{
                    this->pasto[j].setPosition(j*40,i*40-16);
                    win->draw((this->pasto[j]));
                }

            }
            else if (*(*(Matriz+i)+j)==0&&*(*(Matriz+i)+j+1)==1&&j!=columnas-1){
                    this->images[6]->setPosition(j*40,i*40);
                    this->win->draw(*images[6]);
                    this->bloques[i][j].setPosition(j*40,i*40);
                    win->draw((this->bloques[i][j]));
                    }
            else{
                this->bloques[i][j].setPosition(j*40,i*40);
                win->draw((this->bloques[i][j]));
            }


        }
    }


}

Mapa::~Mapa()
{
    //dtor
}
