/* ********** HOW TO USE THIS DRIVER ****************

1. define a gps_value struct variable and initialize it

	gps_value gps_dummy = {0.01,'N',0.01,'E',680000,{2015,5,31},{1,35,3}} ;

2. call the function
	
	gps_dummy = GetGPSValues();

**************************************************** */