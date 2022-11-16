#include "container.h"
#include <iostream>

void Container::addObject(Object *object) // Task 1&3
{
    if (_num_object < MAX_OBJECT_NUM)
    {
        _objects[_num_object] = object;
        if (object->getSize().x + object->getPosition().x > this->getSize().x || object->getSize().y + object->getPosition().y > this->getSize().y)
        {
            std::cout << "The object " << object->getName() << " is too large and cannot be added to " << this->getName() << std::endl;
        }
        else
        {

            object->setParent(this);

            _num_object++;
        }
    }
}

void Container::display() const // Task 1
{
    cout << "\nContainer";
    displayBasic();
    if (_num_object > 0)
    {
        cout << "\n\t\t"
             << "#objects: " << _num_object << "\n";
        for (int i = 0; i < _num_object; i++)
        {
            _objects[i]->display();
        }
    }
    else
        cout << "\n";
}

Container::Container()
{
    for (int i = 0; i < MAX_OBJECT_NUM; i++)
        _objects[i] = nullptr;

    _num_object = 0;
}

Container::~Container() // Task 1
{
    cout << "\nDestructing Container " << getName();
    for (int i = 0; i < _num_object; i++)
    {
        delete _objects[i];
    }
}