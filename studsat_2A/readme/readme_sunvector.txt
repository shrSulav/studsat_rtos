/*************************************************
HOW TO USE THIS DRIVER

1. Initialize the date vector
		uint32_t date[6];
		date[0] : year
		date[1] : month
		date[2] : day
		date[3] : hh
		date[4] : mm
		date[5] : ss
	The date vector can be obtained from GPS.
		
2. Initialize array for sun vector
		float32_t sun_vec;
		
2. call the function
		sun_vector(date, sun_vec);
***************************************************/