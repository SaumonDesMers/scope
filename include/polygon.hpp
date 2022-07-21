#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

using namespace std;

class Polygon {

	private:

		vector<float> _vertex;
		vector<float> _color;

		GLuint vertexBuffer;
		GLuint colorBuffer;

	public:

		Polygon(vector<float> __vertex, vector<float> __color) : _vertex(__vertex), _color(__color) {
			glGenBuffers(1, &vertexBuffer);
			glGenBuffers(1, &colorBuffer);

			setVertex(_vertex);
			setColor(_color);
		}

		Polygon(Polygon &__src) : _vertex(__src._vertex), _color(__src._color) {}

		Polygon &operator=(Polygon &__src) {
			setVertex(__src._vertex);
			setColor(__src._color);
			return *this;
		}

		~Polygon() {
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteBuffers(1, &colorBuffer);
		}

		void setVertex(vector<float> __vertex) {
			_vertex = __vertex;
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex.size(), _vertex.data(), GL_STATIC_DRAW);
		}

		vector<float> getVertex() { return _vertex; }

		void setColor(vector<float> __color) {
			_color = __color;
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _color.size(), _color.data(), GL_STATIC_DRAW);
		}

		vector<float> getColor() { return _color; }

		void draw(GLuint programID) {

			// Use our shader
			glUseProgram(programID);

			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(
				0,                  // same number as layout in shader
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glVertexAttribPointer(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}
};

#endif