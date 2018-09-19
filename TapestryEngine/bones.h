#ifndef BONES_H
#define BONES_H

#include "Utils.h"
#include "Console.h"

struct Joint
{
	int mX;
	int mY;
};

struct Bone
{
	Joint* mA;
	Joint* mB;
	int mLength;
};


class Skeleton
{
public:

protected:

	Bone* mRootBone;

};

class Snake : public Skeleton
{



};
#endif