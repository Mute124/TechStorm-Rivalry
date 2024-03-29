#pragma once
#include <raylib.h>

namespace TechStorm {
	class uShdr {
	private:
		Shader m_shdr;
	public:

		uShdr(Shader)

			virtual operator Shader() const {
		}
	};
}
