#pragma once
#include <exception>
namespace TechStorm {

	// Severities go as below
	//
	// Unknown = an error that it's severity is unknown, these are very dangerous!
	// Low = a trivial error that honestly doesnt affect much. (Can still be seen)
	// Medium = an error that DOES have a noticeable impact.
	// High = an error that MAY be fatal, basically it is bad and has the capability to be fatal
	// Fatal = an error that WILL result in a crash.
	typedef enum EExceptionSeverity {
		ESEVERITY_UNKNOWN = 0,
		ESEVERITY_LOW,
		ESEVERITY_MEDIUM,
		ESEVERITY_HIGH,
		ESEVERITY_FATAL
	};

	// A exception thrown BY TECHSTORM (The game engine).
	class EngineException : public std::exception {
	public:
		EExceptionSeverity severity;

		// Constructor with a custom error message
		EngineException(const char* message, EExceptionSeverity severity);

		// Override the what() function to provide error message
		const char* what() const noexcept override;

	private:
		const char* m_message;
	};

	// A exception thrown by YOU in your code.
	class GameException : public std::exception {
	public:
		EExceptionSeverity severity;

		GameException(const char* message, EExceptionSeverity severity);

		// Override the what() function to provide error message
		const char* what() const noexcept override;

	private:
		const char* m_message;
	};
}
