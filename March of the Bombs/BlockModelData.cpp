#include "BlockModelData.h"

using glm::vec2;
using glm::vec3;

const unsigned short BlockModelData::NUM_INDICES = 36;
BlockModelData::ptr BlockModelData::instance;

void BlockModelData::createVBO()
{
	vec3 positionData[24] =
	{
		vec3(0, 0, 0),
		vec3(0, 0, 1),
		vec3(0, 1, 1),
		vec3(0, 1, 0),

		vec3(1, 0, 0),
		vec3(1, 1, 0),
		vec3(1, 1, 1),
		vec3(1, 0, 1),

		vec3(0, 0, 0),
		vec3(1, 0, 0),
		vec3(1, 0, 1),
		vec3(0, 0, 1),

		vec3(0, 1, 0),
		vec3(0, 1, 1),
		vec3(1, 1, 1),
		vec3(1, 1, 0),

		vec3(0, 0, 0),
		vec3(0, 1, 0),
		vec3(1, 1, 0),
		vec3(1, 0, 0),

		vec3(0, 0, 1),
		vec3(1, 0, 1),
		vec3(1, 1, 1),
		vec3(0, 1, 1)
	};

	vec3 normalData[24] =
	{
		vec3(-1, 0, 0),
		vec3(-1, 0, 0),
		vec3(-1, 0, 0),
		vec3(-1, 0, 0),

		vec3(1, 0, 0),
		vec3(1, 0, 0),
		vec3(1, 0, 0),
		vec3(1, 0, 0),

		vec3(0, -1, 0),
		vec3(0, -1, 0),
		vec3(0, -1, 0),
		vec3(0, -1, 0),

		vec3(0, 1, 0),
		vec3(0, 1, 0),
		vec3(0, 1, 0),
		vec3(0, 1, 0),

		vec3(0, 0, -1),
		vec3(0, 0, -1),
		vec3(0, 0, -1),
		vec3(0, 0, -1),

		vec3(0, 0, 1),
		vec3(0, 0, 1),
		vec3(0, 0, 1),
		vec3(0, 0, 1),
	};

	vec2 texData[24] =
	{
		vec2(0, 0),
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),
		
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),
		vec2(0, 0),

		vec2(0, 0),
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),

		vec2(0, 0),
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),
		
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),
		vec2(0, 0),

		vec2(0, 0),
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1)
	};

	unsigned char indexData[NUM_INDICES] =
	{
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8,  9, 11,
		9, 10, 11,

		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,

		20, 21, 23,
		21, 22, 23
	};

	GLuint vertexBuffers[4];
	glGenBuffers(4, vertexBuffers);

	vertexVBO = vertexBuffers[0];
	texCoordVBO = vertexBuffers[1];
	normalVBO = vertexBuffers[2];
	indexVBO = vertexBuffers[3];

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalData), normalData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texData), texData, GL_STATIC_DRAW);


	glGenVertexArrays(1, &modelVAO);
	glBindVertexArray(modelVAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BlockModelData::setMaterial()
{
	material.ambient[0] = 0;
	material.ambient[1] = 0;
	material.ambient[2] = 0;

	material.diffuse[0] = 0.6f;
	material.diffuse[1] = 0.6f;
	material.diffuse[2] = 0.6f;

	material.specular[0] = 0.4f;
	material.specular[1] = 0.4f;
	material.specular[2] = 0.4f;

	material.shininess = 40.f;

	material.texture1_map.user_ptr = (void*)texture->getHandle();
}

void BlockModelData::useMaterial(GLSLProgram const& prog) const
{
	prog.setUniform("material.ambient", *reinterpret_cast<glm::vec3 const*>(material.ambient));
	prog.setUniform("material.diffuse", *reinterpret_cast<glm::vec3 const*>(material.diffuse));
	prog.setUniform("material.specular", *reinterpret_cast<glm::vec3 const*>(material.specular));
	prog.setUniform("material.shininess", material.shininess);

	glActiveTexture(GL_TEXTURE0 + 5);
	glBindTexture(GL_TEXTURE_2D, (GLuint) material.texture1_map.user_ptr);
}

BlockModelData::BlockModelData()
	: vertexVBO(0), normalVBO(0), texCoordVBO(0), indexVBO(0), modelVAO(0),
	texture(GLTexture::getTexture(L"Images/skull.tga"))
{
	createVBO();
	setMaterial();
}

BlockModelData::~BlockModelData()
{
	if (vertexVBO)
	{
		glDeleteBuffers(1, &vertexVBO);
	}

	if (normalVBO)
	{
		glDeleteBuffers(1, &normalVBO);
	}

	if (texCoordVBO)
	{
		glDeleteBuffers(1, &texCoordVBO);
	}

	if (indexVBO)
	{
		glDeleteBuffers(1, &texCoordVBO);
	}

	if (modelVAO)
	{
		glDeleteVertexArrays(1, &modelVAO);
	}
}

void BlockModelData::draw(GLSLProgram const& prog) const
{
	glBindVertexArray(modelVAO);

	useMaterial(prog);
	glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_BYTE, NULL);

	glBindVertexArray(0);
}

void BlockModelData::drawShadow() const
{
	glBindVertexArray(modelVAO);

	glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_BYTE, NULL);

	glBindVertexArray(0);
}

BlockModelData::ptr BlockModelData::getInstance()
{
	if (!instance)
	{
		instance = BlockModelData::ptr(new BlockModelData());
	}

	return instance;
}