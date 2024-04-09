#pragma once
#include "../TechStorm.h"
#include "../logging/Logman.h"
#include "../registry/Registry.h"
#include "EUITypes.h"
#include "EDrawType.h"

namespace TechStorm {
	class UIContainer;

	class BareUIElement;

	// Note, Icons are not natively supported. You have to implement the logic yourself sorry.
	class UIElement {
	public:
		static inline Font font;
		int id = 0; // the id inside of it's container.
		float fontSize = (float)font.baseSize;
		float fontSpacing = 2.0f;
		int globalID = 0; // it's "nickname" globally
		Vector2 anchor = Vector2Zero();
		bool alwaysVisible = false;	// persistance flag.
		bool isVisible = false;
		bool isActive = true;
		bool drawable = true;
		bool deleteMe = false;	// whether or not the element is suicidal, and should be executed immediatly
		EDrawType drawTime = DRAW_FINAL;
		UIContainer* parent;

		virtual void init();

		virtual void drawElement();
		virtual void updateElement();

		virtual void onDestroy();

		void setContainer(UIContainer* container);
	};

	// The UI container not only contains all elements, but also manages them aswell.
	class UIContainer {
	public:

		static void start();

		virtual void update();

		//
		bool isAsleep() const;

		// amimir
		void sleep();

		/*
		* Rise and shine, Mr.Freeman. Rise and... shine. Not that I... wish to imply you have been sleeping on the job. No one is more deserving of a rest...
		* and all the effort in the world would have gone to waste until... well, let's just say your hour has... come again.
		* The right man in the wrong place can make all the difference in the world. So, wake up, Mister Freeman. Wake up and... smell the ashes...
		*/
		void wake();

		// Let this container it is their time to shine!
		void drawChildren(EDrawType drawMode);

		virtual void onChildrenDraw();

		void addChild(UIElement* element);

		virtual void onChildAdded();

		// abduct the child and yeet it!
		UIElement* getChild(int id);

		void clear();

		virtual void onClear();

		const char* containerTag;

		int containerID;

		// threat eliminated! (It gets deleted next frame.)
		void killChild(int target);

		void kill();

		virtual void onChildKilled();

		// Use if you are a child element, signifying the container should exit, for example a button that exits the menu
		virtual void requestKill();

	protected:
		bool shouldKill = false;
	private:

		int elements = 0;

		int assignID();

		bool isSleeping = true;
		std::map<int, UIElement*> children;
	};
}
