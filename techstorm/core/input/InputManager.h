#pragma once
#include <raylib.h>
#include <functional>
#include "../logic/Conditional.h"
#include <stdlib.h>
#include <map>
#include <memory>
#include <mutex>

namespace TechStorm {
	class KeyBind : public ConditionalTask<void> {
	public:

		KeyboardKey triggerKey = {  };

		bool isAwake;

		KeyBind(std::function<void()> bindFunc, std::function<bool()> checker, KeyboardKey trigger, bool wakeOnPush = true) : ConditionalTask(checker, bindFunc), triggerKey(trigger), isAwake(wakeOnPush)
		{
		}

		~KeyBind() {}
	};

	typedef enum EInputWatchType {
		EWATCHTYPE_NULL,
		EWATCHTYPE_PRESS,
		EWATCHTYPE_PRESS_REPEAT,
		EWATCHTYPE_DOWN,
		EWATCHTYPE_UP
	};

	class InputManager {
	private:
		std::map<const char*, std::shared_ptr<KeyBind>> m_keyBinds;

		//std::map<const char*, bool> m_keyBindStatus; // whether or not the keybind is enabled. true = awake

		void m_setKeyBindStatus(const char* bind, bool status) {
			this->m_keyBinds[bind].get()->isAwake = status;
		}

	public:

		void pushKeyBind(std::function<void()> keyBindFunc, std::function<bool()> checker, const char* keybindName, KeyboardKey trigger, bool wakeOnPush = false) {
			this->m_keyBinds[keybindName] = std::make_shared<KeyBind>(KeyBind(keyBindFunc, checker, trigger, wakeOnPush));
		}

		void pushKeyBind(KeyBind bind, const char* name) {
			this->m_keyBinds[name] = std::make_shared<KeyBind>(bind);
		}

		// constructs a default checking function and pushes it.
		void manufactureKeyBind(std::function<void()> keyBindFunc, const char* keybindName, EInputWatchType watchType, KeyboardKey trigger, bool wakeOnPush = false) {
			std::function<bool()> checker;

			switch (watchType)
			{
			case TechStorm::EWATCHTYPE_NULL:
				break;
			case TechStorm::EWATCHTYPE_PRESS:
				checker = [trigger] {
					return IsKeyPressed(trigger);
					};
				break;
			case TechStorm::EWATCHTYPE_PRESS_REPEAT:
				checker = [trigger] {
					return IsKeyPressedRepeat(trigger);
					};
				break;
			case TechStorm::EWATCHTYPE_DOWN:
				checker = [trigger] {
					return IsKeyDown(trigger);
					};
				break;
			case TechStorm::EWATCHTYPE_UP:
				checker = [trigger] {
					return IsKeyUp(trigger);
					};
				break;
			default:
				break;
			}

			this->pushKeyBind(KeyBind(keyBindFunc, checker, trigger, wakeOnPush), keybindName);
		}

		void awakeKeyBind(const char* keybind) {
			this->m_setKeyBindStatus(keybind, true);
		}

		void sleepKeybind(const char* keybind) {
			this->m_setKeyBindStatus(keybind, false);
		}

		bool isKeybindAwake(const char* bind) {
			return m_keyBinds[bind].get()->isAwake;
		}

		void updateAllInput() {
			for (auto& bind : m_keyBinds) {
				bind.second.get()->execute();
			}
		}
	};
}
