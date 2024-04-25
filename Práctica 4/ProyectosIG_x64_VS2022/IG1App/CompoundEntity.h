#pragma once
#include "Entity.h"
#include "QuadricEntity.h"

class CompoundEntity :
    public Abs_Entity
{
public:
    //APT59
    CompoundEntity() {};
    ~CompoundEntity() {};

    void addEntity(Abs_Entity* ae);
    void moveModelMat(glm::dmat4 const& aMat);

protected:
    std::vector<Abs_Entity*> gObjects;

};


class AdvancedTIE : public CompoundEntity
{
public:
    AdvancedTIE();
    void render(glm::dmat4 const& modelViewMat) const;

protected:

    //Guardamos aquí los elementos necesarios
    Sphere* body;
    CompoundEntity* wings;


};


class WingAdvancedTIE : public CompoundEntity
{
public:
    WingAdvancedTIE();
    void render(glm::dmat4 const& modelViewMat) const;

protected:

    //Guardamos aquí los elementos necesarios
    Sphere* body;
    RGBCube* rgb;
    Abs_Entity* wings1;
    Abs_Entity* wings2;
    Abs_Entity* wings3;
    Texture* t;

};
