#ifndef CLOTH_H
#define CLOTH_H
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum typeCloth{
    chest = 1,
    leg = 2,
    head = 3,
    foot = 4
};

class cloth
{
public:
    bool addCloth(string name, typeCloth type);

    string getName() const;
    void setName(const string &value);

    typeCloth getType() const;
    void setType(const typeCloth &value);

private:
    cloth();
    cloth(string name, typeCloth type);
    string name;
    typeCloth type;
    static vector<string> allNames;
};

#endif // UBRANIE_H
