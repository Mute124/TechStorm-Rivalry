#pragma once
#include <glm/glm.hpp>

namespace TechStorm {
	class Mat4 {
	protected:
		glm::mat4 mat;
	public:

		Mat4(glm::mat4 mat) : mat(mat) {}

		Mat4() {}

		Mat4(float f) : mat(glm::mat4(f)) {}

		virtual operator glm::mat4() { return mat; }
	};
}
