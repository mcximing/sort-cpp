///////////////////////////////////////////////////////////////////////////////
// BBox.h: Contains multiple expressions and operations of a bounding box.

#ifndef BBOX_H
#define BBOX_H 1

#include <iostream>


///////////////////////////////////////////////////////////////////////////////
// For easy transforming between different styles of rects.
class BBox
{
public:
	enum { XYWH, XY12, XYSR };

	BBox();
	//BBox(float ix, float iy, float iw, float ih);
	//BBox(float ix1, float iy1, float ix2, float iy2);
	BBox(float ixc, float iyc, float is, float ir);
	BBox(float i1, float i2, float i3, float i4, int style);
	~BBox();

	bool valid;

	void init_null();
	void init_xywh(float ix, float iy, float iw, float ih);
	void init_xy12(float ix1, float iy1, float ix2, float iy2);
	void init_xysr(float ixc, float iyc, float is, float ir);
	
	float get_xc();
	float get_yc();
	float get_s();
	float get_r();

	friend std::ostream & operator <<(std::ostream &os, const BBox &bb);
	static double GetIOU(const BBox& bb_test, const BBox& bb_gt);

private:
	float x, y;   // x,y is the top left of the box
	float w, h;   // w,h is width and height

	float x1, y1, x2, y2; // x1,y1 is the top left and x2,y2 is the bottom right

	float xc, yc;   // xc,yc is the center of the box
	float s; // s is the scale/area
	float r; // r is the aspect ratio
};


#endif