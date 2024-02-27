#pragma once

class IMoveableCharacter abstract {

public:

	void init(float baseSpeed, float runDelta, float crawlDelta, float walkDelta) {
		this->baseSpeed = baseSpeed;
		this->runDelta = runDelta;
		this->crawlDelta = crawlDelta;
		this->walkDelta = walkDelta;

		this->speed = baseSpeed + speedAffectDelta;
	}

	virtual void setSpeedAffectDelta(float val) {
		this->speedAffectDelta = val;
	}

	virtual void crawl() {
		crawling = true;
		this->speed = baseSpeed + speedAffectDelta;
		this->speed += crawlDelta;
	}

	virtual void run() {
		this->running = true;
		if (this->walking != false) {
			this->walking = false;
		}

		if (crawling) {
			this->speed = baseSpeed + speedAffectDelta;
			this->speed += runDelta + crawlDelta;
		}
		else {
			this->speed = baseSpeed + speedAffectDelta;
			this->speed += runDelta;
		}
	}

	virtual void walk() {
		this->walking = true;
		if (this->running != false) {
			this->running = false;
		}
		if (crawling) {
			this->speed = baseSpeed + speedAffectDelta;
			this->speed += crawlDelta;
		}
		else {
			this->speed = baseSpeed + speedAffectDelta;
			this->speed += walkDelta;
		}
	}

	virtual void stopCrawling() {
		this->crawling = false;
	}

	virtual void stopRunning() {
		this->running = false;
	}

	virtual void stopWalking() {
		this->walking = false;
	}

	bool isStill() {
		return this->speed == 0.0f;
	}

protected:

	bool running;
	float runDelta;

	bool walking = true;
	float walkDelta;

	bool crawling;

	// subtracts from the runDelta only if crawlRunning;
	float crawlDelta;
	float speed = 0.0f;
	float baseSpeed;

	// how affected is the speed? IMPORTANT: if you need this to decrease the value, set as negative.
	float speedAffectDelta;
	
};