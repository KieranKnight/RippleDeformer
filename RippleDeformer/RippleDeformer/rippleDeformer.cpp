#include "rippleDeformer.h"

// std
#include <math.h>

// maya API
#include <maya/MFnMesh.h>
#include <maya/MGlobal.h>
#include <maya/MPointArray.h>
#include <maya/MDataHandle.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnNumericAttribute.h>

// class object variables
MTypeId RippleDeformer::id;
MObject RippleDeformer::attr_value;
MObject RippleDeformer::attr_displace;

// Ripple deformer class and virtual
RippleDeformer::RippleDeformer() {}
RippleDeformer::~RippleDeformer() {}

// Ripple deformer creator
void* RippleDeformer::creator() { return new RippleDeformer(); }

// Initializing the node on creation
// Adding attributes and default attribute values
MStatus RippleDeformer::initialize()
{
	MStatus status;
	MFnNumericAttribute numeric_attr;  // MFnNumericAttribute variable

	// Creating a AmplitudeValue attribute on the deformation node
	attr_value = numeric_attr.create("AmplitudeValue", "AmplitudeValue", MFnNumericData::kFloat, 0.0);
	// Setting attribute values
	numeric_attr.setKeyable(true);
	numeric_attr.setMin(0);
	numeric_attr.setMax(1);

	// Creating a DisplaceValue attribute on the deformation node
	attr_displace = numeric_attr.create("DisplaceValue", "DisplaceValue", MFnNumericData::kFloat, 0.0);
	// Setting the attribute values
	numeric_attr.setKeyable(true);
	numeric_attr.setMin(0);
	numeric_attr.setMax(10);

	// Adding the attributes to the node
	addAttribute(attr_value);
	addAttribute(attr_displace);
	// Adding what the attribute affects to the node.
	attributeAffects(attr_value, outputGeom);
	attributeAffects(attr_displace, outputGeom);

	// Allowing the node to have the ability to change the influence of the driver mesh through paint weights.
	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer rippleDeformer weights;");

	return MS::kSuccess;
}


// The main deformer method
MStatus RippleDeformer::deform(MDataBlock& block, MItGeometry& iter,
	const MMatrix& matrix, unsigned int index)
{
	MStatus status;

	// Getting the output array value from the mesh
	MArrayDataHandle handle_input_array = block.outputArrayValue(input);
	status = handle_input_array.jumpToElement(index);
	
	// Getting the input element and mesh object from the input element
	MDataHandle handle_input_element = handle_input_array.outputValue(&status);
	MObject input_geom = handle_input_element.child(inputGeom).asMesh();

	// Getting the amplitude value created in the initialize method
	MDataHandle amplitude = block.inputValue(attr_value);
	float amplitude_val = amplitude.asFloat();  // converting value to float

	// Getting the displace value created in the initialize method
	MDataHandle displace = block.inputValue(attr_displace);
	float displace_val = displace.asFloat();  // converting value to float

	MFloatVectorArray vertor_normal;  // FloatVector array variable to store normals
	// Creating a MFnMesh object from the input_geom
	MFnMesh fn_mesh_object(input_geom, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// Getting the vertext normals from the MFnMesh object
	fn_mesh_object.getVertexNormals(false, vertor_normal);

	// Getting the envelope value
	float mesh_envelope = block.inputValue(envelope).asFloat();

	// variables to store deformation values
	float weights;
	MPoint points;

	// Looping through each vertex on the geometry
	for (; !iter.isDone(); iter.next()) {
		points = iter.position();  // Getting the position
		weights = weightValue(block, index, iter.index());  // Getting the paint weight value
		// calculating the the deformation value
		points += sin(iter.index() + displace_val) * amplitude_val * vertor_normal[iter.index()] * weights * mesh_envelope;	
		// Setting the current vertex index to the deformation value
		iter.setPosition(points);
	}
	return MS::kSuccess;
}
