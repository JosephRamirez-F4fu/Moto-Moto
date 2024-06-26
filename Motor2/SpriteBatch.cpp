#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
	
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType)
{
}

void SpriteBatch::end()
{
	CreateRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(vba);
	for (size_t i = 0; i < renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return false;
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return false;
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return false;
}

void SpriteBatch::createVertexArray()
{
	if (this->vba == 0) {
		glGenVertexArrays(1, &vba);
	}
	glBindVertexArray(vba);
	if (this->vbo == 0) {
		glGenBuffers(1, &vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glBindVertexArray(0);
}

void SpriteBatch::CreateRenderBatches()
{
	vector <Vertex> vertices;
	vertices.resize(glyphs.size() * 6);
	if (glyphs.empty()) {
		return;
	}
	int cv = 0;
	int offset = 0;
	renderBatches.emplace_back(offset, 6, glyphs[0]->texture);
	vertices[cv++] = glyphs[0]->topLeft;
	vertices[cv++] = glyphs[0]->bottomLeft;
	vertices[cv++] = glyphs[0]->bottomRight;
	vertices[cv++] = glyphs[0]->bottomRight;
	vertices[cv++] = glyphs[0]->topRight;
	vertices[cv++] = glyphs[0]->topLeft;
	offset += 6;
	for (size_t cg = 1; cg < glyphs.size(); cg++) {
		if (glyphs[cg]->texture != glyphs[cg - 1]->texture) {
			renderBatches.emplace_back(offset, 6, glyphs[cg]->texture);
		}
		else {
			renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = glyphs[cg]->topLeft;
		vertices[cv++] = glyphs[cg]->bottomLeft;
		vertices[cv++] = glyphs[cg]->bottomRight;
		vertices[cv++] = glyphs[cg]->bottomRight;
		vertices[cv++] = glyphs[cg]->topRight;
		vertices[cv++] = glyphs[cg]->topLeft;
		offset += 6;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
