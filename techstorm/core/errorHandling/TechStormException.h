#pragma once
#include "../universalTypes/uStr.h"
#include <exception>

#include <toml++/toml.hpp>

namespace TechStorm {
	class ITechStormException : public std::exception
	{
	public:
		ITechStormException(uStr* message) : std::exception(message->cstr()), mMessage(message)
		{
		}

		virtual ~ITechStormException() throw()
		{
		}

		virtual const char* what() const throw()
		{
			return mMessage->cstr();
		}

	private:
		uStr* mMessage;
	};

	class TechStormInvalidCallException : public ITechStormException {
	public:
		TechStormInvalidCallException(uStr* message) : ITechStormException(message)
		{
		}
	};

	class TechStormInvalidStateException : public ITechStormException {
	public:
		TechStormInvalidStateException(uStr* message) : ITechStormException(message)
		{
		}
	};

	class TechStormNotImplementedException : public ITechStormException {
	public:
		TechStormNotImplementedException(uStr* message) : ITechStormException(message)
		{
		}
	};

	class TechStormNotInitializedException : public ITechStormException {
	public:
		TechStormNotInitializedException(uStr* message) : ITechStormException(message)
		{
		}
	};

	class TechStormInvalidParameterException : public ITechStormException {
	public:
		TechStormInvalidParameterException(uStr* message) : ITechStormException(message) {
		}
	};

	class TechStormOutOfMemoryException : public ITechStormException {
	public:
		TechStormOutOfMemoryException(uStr* message) : ITechStormException(message) {
		}
	};

	class TechStormFileException : public ITechStormException {
	public:
		TechStormFileException(uStr* message) : ITechStormException(message) {
		}
	};

	class TechStormIOException : public ITechStormException {
	public:
		TechStormIOException(uStr* message) : ITechStormException(message) {
		}
	};

	class TechStormGenericException : public ITechStormException {
	public:
		TechStormGenericException(uStr* message) : ITechStormException(message) {
		}
	};

	class TechStormInternalException : public ITechStormException {
	public:
		TechStormInternalException(uStr* message) : ITechStormException(message) {
		}
	};

	template <typename T>
	class ITechStormLibraryException abstract : public ITechStormException {
	public:

		TechStormLibraryException(uStr* message) : ITechStormException(message) {
		}

		virtual T* GetException() = 0;

		virtual T* GetException() {
			return mException;
		}

		virtual T* GetException() const = 0;

		virtual ~ITechStormLibraryException() throw()
		{
		}

		virtual const char* what() const throw()
		{
			return mException->what();
		}

	private:
		T* mException;
	};

	void ThrowTechStormException(const char* message, ITechStormException* exception) {
		if (exception) {
			throw exception;
		}
		else {
			throw ITechStormException(new uStr(message));
		}
	}
}
