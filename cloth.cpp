#include "cloth.h"


std::vector<string> cloth::allNames = vector<string>();

cloth::cloth()
{

}

bool cloth::addCloth(std::string name, typeCloth type)
{

    if(find(allNames.begin(), allNames.end(), name) == allNames.end())
    {
        return false;
    }
    else
    {
        cloth(name, type);
        return true;
    }
}

string cloth::getName() const
{
    return name;
}

void cloth::setName(const string &value)
{
    name = value;
}

typeCloth cloth::getType() const
{
    return type;
}

void cloth::setType(const typeCloth &value)
{
    type = value;
}

cloth::cloth(string name, typeCloth type)
{
    this->name = name;
    this->type = type;
    this->allNames.push_back(name);
}
