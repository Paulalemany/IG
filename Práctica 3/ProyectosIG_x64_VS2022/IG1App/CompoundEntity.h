#pragma once
#include "Entity.h"
class CompoundEntity :
    public Abs_Entity
{
public:
    //APT59
    CompoundEntity() {};
    ~CompoundEntity() {};

    void addEntity(Abs_Entity* ae);
    void render(glm::dmat4 const& modelViewMat) const override;

private:
    std::vector<Abs_Entity*> gObjects;


};

class AdvancedTIE : public CompoundEntity
{
public:
    AdvancedTIE();
    void render(glm::dmat4 const& modelViewMat) const;

protected:

};

