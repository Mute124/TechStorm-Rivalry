#pragma once


class IScriptable abstract {
public:



	virtual void onStart();
	virtual void onUpdate();
	virtual void onEnd();

	int ID;

	
};

