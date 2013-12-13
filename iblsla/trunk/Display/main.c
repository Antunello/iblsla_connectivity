/**
 * Check if we are compiling right now. If we are, include the
 * whole class definition, otherwise the declaration suffices
 */
#ifndef BUILD
	#include "MainGui.cc"
#else
	#include "MainGui.hh"
#endif

int main(int argc, char ** argv)
{
	new MainGui();
}
