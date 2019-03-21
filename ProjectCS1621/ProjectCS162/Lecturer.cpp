#include "Lecturer.hpp"

Lecturer::Lecturer()
{
}

Lecturer::Lecturer(string Name):Name(Name)
{
}

string Lecturer::getName() {
    return Name;
}