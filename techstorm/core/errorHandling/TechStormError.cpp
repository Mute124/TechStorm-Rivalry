#include "TechStormError.h"

// Override the what() function to provide error message

// Constructor with a custom error message

inline TechStorm::EngineException::EngineException(const char* message, EExceptionSeverity severity) : m_message(message), severity(severity) {}

inline const char* TechStorm::EngineException::what() const noexcept {
	return m_message;
}

inline TechStorm::GameException::GameException(const char* message, EExceptionSeverity severity) : m_message(message), severity(severity) { }

// Override the what() function to provide error message

inline const char* TechStorm::GameException::what() const noexcept {
	return m_message;
}
