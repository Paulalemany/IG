#pragma once
#include "Entity.h"
#include "QuadricEntity.h"

class SpotLight;

class CompoundEntity :
    public Abs_Entity
{
public:
    //APT59
    CompoundEntity() {};
    ~CompoundEntity() {
        for (Abs_Entity* e : gObjects) {
            delete e;
            e = nullptr;
        }
    };

    void addEntity(Abs_Entity* ae); // A�ade entity a la entidad compuesta
    void render(const glm::dmat4& modelViewMat) const override;

    //M�todos de translaci�n
    
    //Rotaci�n
    GLdouble getRotation() { return rot; }
    void setrotation(GLdouble r) { rot = r; }

protected:
    std::vector<Abs_Entity*> gObjects; // Vector de las entidades que forman la entidad compuesta.

    GLdouble rot = 0;

};


class AdvancedTIE : public CompoundEntity
{
public:
    AdvancedTIE();
    ~AdvancedTIE() override;

    void render(glm::dmat4 const& modelViewMat) const override;
    void update() override;

    //apt79
    void activaFoco();
    void desactivaFoco();

protected:

    //Guardamos aqu� los elementos necesarios
    //Mejor si lo hacemos con elementos simples que se juntan todos aqu� (Le preguntar� a elena si se pod�a hacer como yo quer�a)
    CompoundEntity* wing1;
    CompoundEntity* wing2;
    Sphere* body;
    Cylinder* eje;

    //Morro
    Cylinder* morro;
    Disk* tapaMorro;

    //Foco
    SpotLight* foco;
};


class WingAdvancedTIE : public CompoundEntity
{
public:
    WingAdvancedTIE(GLdouble w, GLdouble h, GLdouble rot);
    void render(glm::dmat4 const& modelViewMat) const override;

protected:


};
