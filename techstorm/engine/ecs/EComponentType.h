#pragma once

/*
* COMP_NULL : Use for initialization only!
* COMP_SCRIPT : A component that just has a script. Ussually doesnt have other variables.
* COMP_MECHANIC : A complete game mechanic, it has variables, other functions, etc.
* COMP_DATASET : A component full of just variables.
*/
typedef enum EComponentType {
	COMP_NULL = 0,
	COMP_SCRIPT,
	COMP_MECHANIC,
	COMP_DATASET,
};
