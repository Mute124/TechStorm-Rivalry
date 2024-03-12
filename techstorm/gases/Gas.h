#pragma once

class Gas abstract {
protected:
	bool essentialToLife;
	float gasToxicity; // 0 = non-toxic.
public:
	float getToxicity() {
		return this->gasToxicity;
	}
};
