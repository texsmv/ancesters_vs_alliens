#include "Boton.h"

Boton::Boton(string nombre, string letra,float alto, float ancho, string texto, sf::Event* evento,sf::RenderWindow* win, float posx, float posy){

    this->alto=alto;
    this->ancho=ancho;
    this->win=win;
    this->Coor_x=posx;
    this->Coor_y=posy;
    this->letra=letra;
    this->texto=texto;
    this->evento=evento;
    this->boton= new Objeto(nombre,alto , ancho);







}

void Boton::draw2(){

    win->draw(*boton);
    boton->setPosition(Coor_x,Coor_y);

    sf::Font font;
    font.loadFromFile(letra);
    sf::Text texto2(texto,font);
    texto2.setColor(sf::Color::Black);
    texto2.setPosition(Coor_x+ancho/3,Coor_y+alto/8);
    win->draw(texto2);

    //texto->setPosition(Coor_x+ancho,Coor_y+alto);
}

void Boton::setEvento(sf::Event* evento){
    this->evento=evento;

}

bool Boton::clicked(){

    if(evento->type==sf::Event::MouseButtonPressed){


        if(evento->mouseButton.button==sf::Mouse::Left){

            if(evento->mouseButton.x>Coor_x&&evento->mouseButton.x<Coor_x+ancho&&evento->mouseButton.y>Coor_y&&evento->mouseButton.y<Coor_y+alto){
                return true;

            }
        }

    }
    return false;
}

Boton::Boton()
{
    //ctor
}

Boton::~Boton()
{
    //dtor
}

