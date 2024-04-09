#pragma once
#include "../errorHandling/TechStormException.h"
#include <iostream>
#include <memory>

namespace TechStorm {
	template<typename T>
	class Shared {
	private:
		T& data;
	public:

		Shared(T& data) : data(data) {
		}

		~Shared() = default;

		//
		// <summary>
		// Creates a shared pointer
		// </summary>
		// <returns></returns>
		// <exception cref="TechStormInternalException"></exception>
		//
		std::shared_ptr<T> makeShared() {
			try
			{
				return std::make_shared<T>(data);
			}
			catch (const std::exception& e)
			{
				throw TechStormInternalException("Error while making shared pointer: " + e.what());
			}
		}

		//
		// <summary>
		// Returns the stored data
		// </summary>
		// <returns></returns>
		//
		T& getStoredData() {
			return data;
		}
	};
}
