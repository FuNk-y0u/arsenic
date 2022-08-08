#include "a.h"

// Main Window Loop
int proc(unsigned int msg)
{
	switch(msg)
	{
		case WM_CLOSE:
			PostQuitMessage(6);
		break;
	}
}


// Starting Function
int main(int argc, char** argv )
{

	if(!a_create_window("Arsenic Test", 800, 600, proc))
	{
		A_ERROR();
	}
}
