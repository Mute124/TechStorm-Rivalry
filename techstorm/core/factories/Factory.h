#pragma once
#include <functional>

namespace TechStorm {
	template<typename T>
	class Factory abstract {
	public:
		void setManufactureFunction(std::function<T()> func) { this->manufactureFunction = &func };

	protected:
		std::function<T()>* manufactureFunction
	};
}
