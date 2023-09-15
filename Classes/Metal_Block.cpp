// Todo : Update this file and make sure it is up to date.
#include "Metal_Block.h"
#include <thread>
#include <iostream>


Metal_Block::Metal_Block(Vector3 Position, Model model) : m_position(Position), m_model(model)
{
    Logman::CustomLog(LOG_INFO, "New Metal block Created", NULL);
    
}


void Metal_Block::Draw() const {


}

Metal_Block::~Metal_Block() {
    delete this;
}

int Metal_Block::GetType() const {
    return 0;
}