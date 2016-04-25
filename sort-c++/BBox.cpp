///////////////////////////////////////////////////////////////////////////////
// BBox.cpp: Implementation of class BBox.

#include "BBox.h"
#include <algorithm>


BBox::BBox()
{
	init_null();
}
//BBox(float ix, float iy, float iw, float ih)
//{
//	init_xywh(ix, iy, iw, ih);
//}
//BBox(float ix1, float iy1, float ix2, float iy2)
//{
//	init_xy12(ix1, iy1, ix2, iy2);
//}

BBox::BBox(float ixc, float iyc, float is, float ir)
{
	valid = true;
	init_xysr(ixc, iyc, is, ir);
}

BBox::BBox(float i1, float i2, float i3, float i4, int style)
{
	switch (style)
	{
	case XYWH:
		init_xywh(i1, i2, i3, i4);
		break;
	case XY12:
		init_xy12(i1, i2, i3, i4);
		break;
	case XYSR:
		init_xysr(i1, i2, i3, i4);
		break;
	default:
		init_xywh(i1, i2, i3, i4);
		break;
	}
}

BBox::~BBox(){}



void BBox::init_xywh(float ix, float iy, float iw, float ih)
{
	x = ix;
	y = iy;
	w = iw;
	h = ih;

	x1 = x;
	y1 = y;
	x2 = (x + w);
	y2 = (y + h);

	xc = (x + w / 2);
	yc = (y + h / 2);
	s = w * h;
	r = w / h;

	if (w < 0 || h < 0 || x < 0 || y < 0)
	{
		//std::cerr << "Error: Illegal Definition." << std::endl;
		//std::cerr << "Data: " << ix << ", " << iy << ", " << iw << ", " << ih << std::endl;
		init_null();
	}
}

void BBox::init_xy12(float ix1, float iy1, float ix2, float iy2)
{
	x1 = ix1;
	y1 = iy1;
	x2 = ix2;
	y2 = iy2;

	x = x1;
	y = y1;
	w = (x2 - x1);
	h = (y2 - y1);

	xc = (x + w / 2);
	yc = (y + h / 2);
	s = w * h;
	r = w / h;

	if (w < 0 || h < 0 || x < 0 || y < 0)
	{
		//std::cerr << "Error: Illegal Definition." << std::endl;
		//std::cerr << "Data: " << ix1 << ", " << iy1 << ", " << ix2 << ", " << iy2 << std::endl;
		init_null();
	}
}

void BBox::init_xysr(float ixc, float iyc, float is, float ir)
{
	xc = ixc;
	yc = iyc;
	s = is;
	r = ir;

	w = sqrt(s * r);
	h = s / w;
	x = (xc - w / 2);
	y = (yc - h / 2);
	if (x < 0 && xc > 0)
		x = 0;
	if (y < 0 && yc > 0)
		y = 0;

	x1 = x;
	y1 = y;
	x2 = (x1 + w);
	y2 = (y1 + h);

	if (w < 0 || h < 0 || x < 0 || y < 0)
	{
		//std::cerr << "Error: Illegal Definition." << std::endl;
		//std::cerr << "Data: " << ixc << ", " << iyc << ", " << is << ", " << ir << std::endl;
		//std::cerr << "Data: " << x << ", " << y << ", " << w << ", " << h << std::endl;
		init_null();
	}
}

// initialize remainings with x1,y1,x2,y2 already set
void BBox::init_xy12_given()
{
	x = x1;
	y = y1;
	w = (float)(x2 - x1);
	h = (float)(y2 - y1);

	xc = (x + w / 2);
	yc = (y + h / 2);
	s = w * h;
	r = w / h;

	if (w < 0 || h < 0 || x < 0 || y < 0)
	{
		//std::cerr << "Error: Illegal Definition." << std::endl;
		//std::cerr << "Data: " << xc << ", " << yc << ", " << s << ", " << r << std::endl;
		init_null();
	}
}

void BBox::init_null()
{
	x = y = x1 = y1 = x2 = y2 = -1;
	xc = yc = 0;
	w = h = s = r = 0.0;
	valid = false;
}


// Computes IOU between two BBoxes
double BBox::GetIOU(const BBox& bb_test, const BBox& bb_gt)
{
	float xx1 = std::max(bb_test.x1, bb_gt.x1);
	float yy1 = std::max(bb_test.y1, bb_gt.y1);
	float xx2 = std::min(bb_test.x2, bb_gt.x2);
	float yy2 = std::min(bb_test.y2, bb_gt.y2);
	double w = std::max(0.0f, xx2 - xx1);
	double h = std::max(0.0f, yy2 - yy1);
	double i = w * h;
	double iou = i / (bb_test.s + bb_gt.s - i);
	return iou;
}


std::ostream & operator <<(std::ostream &os, const BBox &bb)
{
	os << bb.x << ", " << bb.y << ", " << bb.w << ", " << bb.h << std::endl;
	return os;
}
