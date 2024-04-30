#pragma once
#include <vector>
#include <glm/vec3.hpp>

class Cara {
public:
	Cara() = default;
	Cara(glm::dvec3, glm::dvec3, glm::dvec3);
	Cara(int, int, int);
	~Cara() = default;
	int numeroVertices;
	std::vector<glm::dvec3> vertices;
	std::vector<int> indices;

	int getIndice(int i) const { return indices[i]; }

	int getIndiceVertice(glm::dvec3 vec) const
	{
		const auto it
			= std::ranges::find(vertices.begin(),
				vertices.end(),
				vec);

		int index = -1;
		if (it != vertices.end())
			index = it - vertices.begin();

		return index;
	}

	int getIndiceVertice(glm::dvec3 vertex, std::vector<glm::dvec3> vector) const
	{
		const auto it
			= std::ranges::find(vector.begin(),
				vector.end(),
				vertex);

		int index = -1;
		if (it != vector.end())
			index = it - vector.begin();

		return index;
	}

	glm::vec3 getVerticeIndice(int index) const
	{
		return vertices[index];
	}
};

