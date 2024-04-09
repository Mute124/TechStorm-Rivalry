#include "TechStormError.h"

// Override the what() function to provide error message

// Constructor with a custom error message

TechStorm::EngineException::EngineException(const char* message, EExceptionSeverity severity) : m_message(message), severity(severity) {}

const char* TechStorm::EngineException::what() const noexcept {
	return m_message;
}
TechStorm::GameException::GameException(const char* message, EExceptionSeverity severity) : m_message(message), severity(severity) { }

// Override the what() function to provide error message

const char* TechStorm::GameException::what() const noexcept {
	return m_message;
}
