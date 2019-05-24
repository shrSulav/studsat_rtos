1. include ITM_Port.h and fputc.h header files

2. include fputc.c source file in the project

3. configure options in
	Project -> Options for Target -> Debug -> Settings -> Trace
	
	Enable Trace
	
	Configure Clock to 168 MHz
	
	ITM Stimulus Ports:
		Enable : 0x00000001
		Privilege : 0x00000008

4. Then, you can use printf function to print in Debug Viewer.

http://www.keil.com/support/man/docs/ulink2/ulink2_trace_itm_viewer.htm