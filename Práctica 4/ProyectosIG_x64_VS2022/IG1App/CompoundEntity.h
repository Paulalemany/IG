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
    void render(const glm::dmat4& modelViewMat) const override;

    //M�todos de translaci�n
    
    //Rotaci�n
    GLdouble getRotation() { return rot; }
    void setrotation(GLdouble r) { rot = r; }

protected:
    std::vector<Abs_Entity*> gObjects;

    GLdouble rot = 0;

};


class AdvancedTIE : public CompoundEntity
{
public:
    AdvancedTIE();
    ~AdvancedTIE() override;

    void render(glm::dmat4 const& modelViewMat) const override;
    void update() override;

protected:

    //Guardamos aqu� los elementos necesarios
    //Mejor si lo hacemos con elementos simples que se juntan todos aqu� (Le preguntar� a elena si se pod�a hacer como yo quer�a)
    CompoundEntity* wings;
    Sphere* body;
    Cylinder* eje;

    //Morro
    Cylinder* morro;
    Disk* tapaMorro;
};


class WingAdvancedTIE : public CompoundEntity
{
public:
    WingAdvancedTIE(GLdouble w, GLdouble h);
    void render(glm::dmat4 const& modelViewMat) const override;

protected:

    Abs_Entity* wings1;
    Abs_Entity* wings2;
    Abs_Entity* wings3;

    //Texturas
    Texture* t;

};
