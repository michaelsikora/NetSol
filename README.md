 Person of Contact: Michael Sikora <m.sikora@uky.edu>
 Date: 2018.03.03
 Purpose:
	Application using Qt5 for reading a Serial Port and displaying received data.
	To be used for Senior Design project by team Netsol.
	
	The debug/ folder is included which contains the .exe compiled application for
	windows. The dependencies were tracked down and copied to the debug/ folder as 
	well, so the debug/ folder can be copied to other windows machines and the .exe
	should run the application. UPDATE: debug/ is ignored for git because the dll's
	are too large. To setup standalone .exe on windows the following .dll's were
	searched for and copied to the debug/ directory:
	
	Qt5Guid.dll
	Qt5Cored.dll
	Qt5SerialPortd.dll
	Qt5Widgetsd.dll
	libgcc_s_dw2-1.dll
	libstdc++-6.dll
	libwinpthread-1.dll
	
	System used: Qt5.10.1, Qt Creator on Windows 10 with MinGW 32bit compiler

	A snapshot was taken of the working application reading from an ESP32 board
	connected to COM7 with a Baudrate set at 115200. The snapshot is in the main
	directory and named snapshot.png.
