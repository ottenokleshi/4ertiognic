#ifndef _MATLAB_RENDERER_H
#define _MATLAB_RENDERER_H
#include <iostream>
#include <fstream> 
#include <string>
#include "GUI.h"
#include "GUI_types.h"
#include "objects.h"
#include "MArray.h"

using namespace std;
class MatlabRenderer : public GUI {
	string _filename;
	size_t _markersize;
	
public:
	MatlabRenderer(string filename,  size_t markersize) {
		_filename = filename;
		_markersize = markersize;
	}
	virtual void drawSketch(Array<Primitive_Type> *objType, Array <Array<double>> *parametrs);

	virtual bool drawPrimitive(Primitive_Type type, Array<double> &parametrs, size_t markersize);
	virtual  GUIType getTypeGUI() {
		return MATLAB;
	}

};
#endif 