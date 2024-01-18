#pragma once

enum TagTypes {
	METAL,
	PLASTIC
};

typedef struct Tag {
	int type;
	int tagData;
};