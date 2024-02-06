#pragma once
class IScriptable {
public:

	virtual void onStart();
	virtual void onUpdate();
	virtual void onEnd();

	int a;
};