#pragma once
#include <stdlib.h>
#include <functional>
namespace TechStorm {
	class Conditional {
	public:

		bool m_passedRequirement = false;
		std::function<bool()> m_checkCallBack;

		Conditional(std::function<bool()> checker) : m_checkCallBack(checker) {
		}

		Conditional() {}

		virtual operator bool() const {
			return m_checkCallBack();
		}
	};

	// does something ONLY IF the conditional passes
	template <typename T>
	class ConditionalTask : public Conditional {
	protected:

		std::function<T()> m_conditionalTask;

		ConditionalTask(std::function<bool()> checker, std::function<T()> conditionalTask) : Conditional(checker), m_conditionalTask(conditionalTask) {
		}

	public:

		// Only checks the conditional. Does not execute.
		virtual bool test() {
			return this->m_checkCallBack();
		}

		// executes if passed the test.
		virtual void execute() {
			if (this->test()) {
				this->m_conditionalTask();
			}
		}
	};

	Conditional& makeConditional(std::function<bool()> checker) {
		return Conditional(checker);
	}
}
