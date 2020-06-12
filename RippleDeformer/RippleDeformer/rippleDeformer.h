#ifndef RIPPLEDEFORMER_H
#define RIPPLEDEFORMER_H

// maya API
#include <maya/MItGeometry.h>
#include <maya/MPxDeformerNode.h>


// Main Ripple deformer class inheriting from the MPxDeformerNode
class RippleDeformer : public MPxDeformerNode
{
public:
	RippleDeformer();
	virtual ~RippleDeformer();
	static void* creator();

	static MStatus initialize();

	virtual MStatus deform(
		MDataBlock& block,
		MItGeometry& iter,
		const MMatrix& matrix,
		unsigned int index
	);

	// Class variables
	static MTypeId id;
	static MObject attr_value;
	static MObject attr_displace;

};

#endif