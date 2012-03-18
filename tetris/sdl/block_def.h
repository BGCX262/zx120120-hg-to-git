typedef int BShape[4][4][4];

const BShape Shape_I = {
	{{0,1,0,0},
	 {0,1,0,0},
	 {0,1,0,0},
	 {0,1,0,0}},
	/*-------*/
	{{0,0,0,0},
	 {1,1,1,1},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{0,1,0,0},
	 {0,1,0,0},
	 {0,1,0,0},
	 {0,1,0,0}},
	/*-------*/	
	{{0,0,0,0},
	 {1,1,1,1},
	 {0,0,0,0},
	 {0,0,0,0}},
};

const BShape Shape_L = {
	{{1,0,0,0},
	 {1,1,1,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,1,0,0},
	 {1,0,0,0},
	 {1,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,1,1,0},
     {0,0,1,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{0,1,0,0},
	 {0,1,0,0},
	 {1,1,0,0},
	 {0,0,0,0}},
};

const BShape Shape_J = {
	{{0,0,1,0},
	 {1,1,1,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,0,0,0},
	 {1,0,0,0},
	 {1,1,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,1,1,0},
     {1,0,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,1,0,0},
	 {0,1,0,0},
	 {0,1,0,0},
	 {0,0,0,0}},
};

const BShape Shape_O = {
	{{1,1,0,0},
	 {1,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,1,0,0},
	 {1,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{1,1,0,0},
	 {1,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{1,1,0,0},
	 {1,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
};

const BShape Shape_S = {
	{{0,1,1,0},
	 {1,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,0,0,0},
	 {1,1,0,0},
	 {0,1,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{0,1,1,0},
	 {1,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{1,0,0,0},
	 {1,1,0,0},
	 {0,1,0,0},
	 {0,0,0,0}},
};

const BShape Shape_Z = {
	{{1,1,0,0},
	 {0,1,1,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{0,1,0,0},
	 {1,1,0,0},
	 {1,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{1,1,0,0},
	 {0,1,1,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{0,1,0,0},
	 {1,1,0,0},
	 {1,0,0,0},
	 {0,0,0,0}},
};

const BShape Shape_T = {
	{{0,1,0,0},
	 {1,1,1,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/
	{{1,0,0,0},
	 {1,1,0,0},
	 {1,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{1,1,1,0},
	 {0,1,0,0},
	 {0,0,0,0},
	 {0,0,0,0}},
	/*-------*/	
	{{0,1,0,0},
	 {1,1,0,0},
	 {0,1,0,0},
	 {0,0,0,0}},
};


const BShape* shape[] = {&Shape_L,&Shape_I,&Shape_J,&Shape_O,&Shape_S,&Shape_Z,&Shape_T};
const int n_shape = sizeof(shape)/sizeof(shape[0]);