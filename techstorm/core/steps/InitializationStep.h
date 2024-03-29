#pragma once
#include "../utils/Task.h"

namespace TechStorm {
	class InitStep abstract {
	protected:

		virtual void initStep() {}
	};

	class SimpleInitStep final : public InitStep, public util::Task {
	public:
		SimpleInitStep(std::function<void()> task) : util::Task(task) {
		}
	};

	class GameInitStep abstract : public InitStep {
	protected:
		virtual void initStep() override {}
	public:
		GameInitStep() {}
	};
}
