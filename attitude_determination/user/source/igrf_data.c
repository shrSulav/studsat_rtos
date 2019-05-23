#include "igrf_data.h"

float32_t g[IGRF_ROW][IGRF_ROW + 1];
float32_t h[IGRF_ROW][IGRF_ROW + 1];

float32_t Bix,Biy,Biz;

float32_t igrfh[IGRF_ROW][IGRF_COL] = {
	{1, 0, 0, 0}, 
	{1, 1, 4797.1001, -26.6000004}, 
	{2, 0, 0, 0},
	{2, 1, -4928.7002, -47.4580002},
	{2, 2, -555.900024, -12.2110004}, 
	{3, 0, 0, 0}, {3, 1, -353.029999, 25.1070004}, 
	{3, 2, 474.25, -0.774600029}, 
	{3, 3, -425.640015, 1.42299998}, 
	{4, 0, 0, 0}, 
	{4, 1, 1567.80005, -7.19420004}, 
	{4, 2, -738.409973, 20.7399998}, 
	{4, 3, 378.380005, 6.06580019}, 
	{4, 4, -243.669998, -3.84549999}, 
	{5, 0, 0, 0}, 
	{5, 1, 480.880005, 6.09989977}, 
	{5, 2, 1514, 13.0649996}, 
	{5, 3, -561.450012, -5.64750004}, 
	{5, 4, 35.4959984, 7.54300022}, 
	{5, 5, 70.2959976, 0}, 
	{6, 0, 0, 0}, 
	{6, 1, -393.179993, 0}, 
	{6, 2, 496.149994, -31.3829994}, 
	{6, 3, 586.809998, -6.97399998}, 
	{6, 4, -363.970001, 1.09140003}, 
	{6, 5, 16.9860001, 2.0941}, 
	{6, 6, 42.0480003, 0.671689987}, 
	{7, 0, 0, 0}, 
	{7, 1, -1918.90002, 28.3759995}, 
	{7, 2, -564.73999, 11.5839996}, 
	{7, 3, 116.730003, -4.09569979}, 
	{7, 4, 301.309998, -3.70469999}, 
	{7, 5, 20.993, -3.70469999}, 
	{7, 6, -66.3580017, 0.242180005}, 
	{7, 7, -1.42400002, -0.129449993}, 
	{8, 0, 0, 0}, 
	{8, 1, 677.02002, -20.1089993}, 
	{8, 2, -1026.30005, 16.8250008}, 
	{8, 3, 550.880005, 4.1420002}, 
	{8, 4, -390.350006, 13.368}, 
	{8, 5, 240.259995, -2.96609998}, 
	{8, 6, 39.132, -2.05960011}, 
	{8, 7, -22.8120003, 0.752049983}, 
	{8, 8, 1.3161, 0}, 
	{9, 0, 0, 0}, 
	{9, 1, -2751.8999, 0}, 
	{9, 2, 1173.40002, 0}, 
	{9, 3, 979.200012, 0}, 
	{9, 4, -383.359985, 0}, 
	{9, 5, -232.470001, 0}, 
	{9, 6, 135.699997, 0}, 
	{9, 7, 7.53350019, 0}, 
	{9, 8, -10.3360004, 0}, 
	{9, 9, 5.11600018, 0}, 
	{10, 0, 0, 0}, 
	{10, 1, 778.52002, 0}, 
	{10, 2, -84.2770004, 0}, 
	{10, 3, 760.289978, 0}, 
	{10, 4, 514.22998, 0},
	{10, 5, -583.929993, 0}, 
	{10, 6, -24.7919998, 0}, 
	{10, 7, -84.1809998, 0}, 
	{10, 8, -22.9109993, 0}, 
	{10, 9, -3.18569994, 0}, 
	{10, 10, -5.1645999, 0}, 
	{11, 0, 0, 0}, 
	{11, 1, -46.6389999, 0}, 
	{11, 2, 818.099976, 0}, 
	{11, 3, -229.580002, 0}, 
	{11, 4, -263.470001, 0}, 
	{11, 5, 126.739998, 0}, 
	{11, 6, -18.8239994, 0}, 
	{11, 7, -109.129997, 0}, 
	{11, 8, -31.8640003, 0}, 
	{11, 9, -22.0370007, 0}, 
	{11, 10, -5.44070005, 0}, 
	{11, 11, -1.39199996, 0}, 
	{12, 0, 0, 0}, 
	{12, 1, -986.72998, 0}, 
	{12, 2, 318.049988, 0}, 
	{12, 3, 1233.5, 0}, 
	{12, 4, -1071.19995, 0}, 
	{12, 5, 100.209999, 0}, 
	{12, 6, 145.809998, 0}, 
	{12, 7, -11.7049999, 0}, 
	{12, 8, 17.5580006, 0}, 
	{12, 9, 5.1086998, 0}, 
	{12, 10, -8.48919964, 0}, 
	{12, 11, -0.278149992, 0}, 
	{12, 12, 0.397439986, 0}, 
	{13, 0, 0, 0}, 
	{13, 1, -1557.19995, 0}, 
	{13, 2, 619.01001, 0}, 
	{13, 3, 2053, 0}, 
	{13, 4, -492.059998, 0}, 
	{13, 5, -835.049988, 0}, 
	{13, 6, -45.1549988, 0}, 
	{13, 7, 106.860001, 0}, 
	{13, 8, -14.2790003, 0}, 
	{13, 9, 27.2290001, 0}, 
	{13, 10, 14.1940002, 0}, 
	{13, 11, -3.01099992, 0}, 
	{13, 12, -1.13549995, 0}, 
	{13, 13, -0.445389986, 0}
		};
		
float32_t igrfg[IGRF_ROW][IGRF_COL] = {
	{1, 0, -29442, 10.3000002}, 
	{1, 1, -1501, 18.1000004}, 
	{2, 0, -3667.6001, -13.0500002}, 
	{2, 1, 5218.5, -5.71579981}, 
	{2, 2, 1452.09998, 1.81869996}, 
	{3, 0, 3376.80005, 8.5}, 
	{3, 1, -7202.3999, -16.8400002}, 
	{3, 2, 2373.3999, -1.35549998}, 
	{3, 3, 460.109985, -7.98479986}, 
	{4, 0, 3970.80005, -3.0625}, 
	{4, 1, 4503, 1.10679996}, 
	{4, 2, 471.140015, -35.6090012}, 
	{4, 3, -700.48999, 8.57579994}, 
	{4, 4, 52.0620003, -3.17989993}, 
	{5, 0, -1831.69995, -1.57500005}, 
	{5, 1, 3661, 5.08330011}, 
	{5, 2, 1478.59998, -9.9907999}, 
	{5, 3, -663.109985, -0.470620006}, 
	{5, 4, -349.420013, 3.10590005}, 
	{5, 5, 2.87639999, 2.73609996}, 
	{6, 0, 1010.59998, -4.33120012}, 
	{6, 1, 1279.69995, -1.89030004}, 
	{6, 2, 1086.40002, -10.4610004}, 
	{6, 3, -1294.19995, 20.9220009}, 
	{6, 4, -157.699997, -6.54820013}, 
	{6, 5, 30.7140007, 0.698040009}, 
	{6, 6, -47.6230011, 1.0747}, 
	{7, 0, 2187.8999, 8.04370022}, 
	{7, 1, -2699.19995, -7.0939002}, 
	{7, 2, -196.929993, -14.4799995}, 
	{7, 3, 1060.80005, 26.6219997}, 
	{7, 4, 185.229996, 1.2349}, 
	{7, 5, 58.0400009, -3.70469999}, 
	{7, 6, -6.7810998, -1.9375}, 
	{7, 7, 4.40140009, 0.129449993}, 
	{8, 0, 1216.59998, 10.0550003}, 
	{8, 1, 589.880005, 0}, 
	{8, 2, -947.789978, -33.6489983}, 
	{8, 3, -132.539993, 20.7099991}, 
	{8, 4, -550.77002, -5.34719992}, 
	{8, 5, 198.729996, 5.93219995}, 
	{8, 6, 80.322998, 0.68651998}, 
	{8, 7, -39.8590012, -1.00269997}, 
	{8, 8, -1.25339997, 0.188010007}, 
	{9, 0, 512.789978, 0}, 
	{9, 1, 1121.19995, 0}, 
	{9, 2, 336.820007, 0}, 
	{9, 3, -273.839996, 0}, 
	{9, 4, 39.4630013, 0}, 
	{9, 5, -448.089996, 0}, 
	{9, 6, -1.73979998, 0}, 
	{9, 7, 65.5419998, 0}, 
	{9, 8, -23.5139999, 0}, 
	{9, 9, -6.39499998, 0}, 
	{10, 0, -342.809998, 0}, 
	{10, 1, -1532.69995, 0}, 
	{10, 2, 21.0690002, 0}, 
	{10, 3, 82.6399994, 0}, 
	{10, 4, -58.4350014, 0}, 
	{10, 5, 133.050003, 0}, 
	{10, 6, -28.9239998, 0}, 
	{10, 7, 42.0909996, 0}, 
	{10, 8, 19.6380005, 0}, 
	{10, 9, -4.77860022, 0}, 
	{10, 10, -2.13709998, 0}, 
	{11, 0, 1067.80005, 0}, 
	{11, 1, -699.580017, 0}, 
	{11, 2, -940.809998, 0}, 
	{11, 3, 655.940002, 0}, 
	{11, 4, -191.610001, 0}, 
	{11, 5, 95.0540009, 0}, 
	{11, 6, -65.8820038, 0}, 
	{11, 7, 9.92090034, 0}, 
	{11, 8, 38.6920013, 0}, 
	{11, 9, -1.76300001, 0}, 
	{11, 10, 1.08809996, 0}, 
	{11, 11, 2.02990007, 0}, 
	{12, 0, -1254.40002, 0}, 
	{12, 1, -179.410004, 0}, 
	{12, 2, 318.049988, 0}, 
	{12, 3, 779.059998, 0}, 
	{12, 4, -389.529999, 0}, 
	{12, 5, 300.619995, 0}, 
	{12, 6, 20.8299999, 0}, 
	{12, 7, 58.5270004, 0}, 
	{12, 8, -17.5580006, 0}, 
	{12, 9, -10.217, 0}, 
	{12, 10, 1.8865, 0}, 
	{12, 11, -2.50329995, 0}, 
	{12, 12, 0, 0}, 
	{13, 0, 0, 0}, 
	{13, 1, -1557.19995, 0}, 
	{13, 2, 619.01001, 0}, 
	{13, 3, 641.570007, 0}, 
	{13, 4, -492.059998, 0}, 
	{13, 5, 695.880005, 0}, 
	{13, 6, -90.3089981, 0}, 
	{13, 7, 213.710007, 0}, 
	{13, 8, -14.2790003, 0}, 
	{13, 9, 20.4220009, 0}, 
	{13, 10, 2.83879995, 0}, 
	{13, 11, 5.01840019, 0}, 
	{13, 12, -1.13549995, 0}, 
	{13, 13, -0.167019993, 0}
		};
