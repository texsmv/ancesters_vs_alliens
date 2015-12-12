#include "Menu.h"

Menu::Menu(string nombre_imagen, string nombre_letra,float alto_boton, float ancho_boton, string* textos_botones,int num_botones, sf::Event* evento,sf::RenderWindow* win, float posx, float posy){
    botones=new Boton*[num_botones];
    for (int i=0;i<num_botones;i++){
        botones[i]=new Boton(nombre_imagen,nombre_letra,alto_boton,ancho_boton,*(textos_botones+i),evento,win, posx, posy + 50*i);
    }

    this->num_botones= num_botones;


}


void Menu::setEvento(sf::Event* evento){
    for(int i=0;i<num_botones;i++){
        botones[i]->setEvento(evento);
    }
}

void Menu::draw(){
    for(int i=0;i<num_botones;i++){
        botones[i]->draw2();
    }

}



Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}
