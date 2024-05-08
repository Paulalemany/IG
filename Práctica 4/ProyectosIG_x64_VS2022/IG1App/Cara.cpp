#include "Cara.h"

Cara::Cara(glm::dvec3 v0, glm::dvec3 v1, glm::dvec3 v2)
{
	numeroVertices = 3;

	vertices.resize(3);
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
}

Cara::Cara(int v0, int v1, int v2)
{
	numeroVertices = 3;

	indices.resize(3);
	indices[0] = v0;
	indices[1] = v1;
	indices[2] = v2;
}