#include "rippleDeformer.h"

// maya API
#include <maya/MFnPlugin.h>


// Initializing the plugin, runs on load
MStatus initializePlugin(MObject obj)
{
    MStatus status;
    
    // creating the MFnPlugin object
    MFnPlugin fnPlugin(obj, "Kieran Knight", "1.0", "Any");
   CHECK_MSTATUS_AND_RETURN_IT( status );
   // registering the node for maya
   status = fnPlugin.registerNode("rippleDeformer",
       RippleDeformer::id,
       RippleDeformer::creator,
       RippleDeformer::initialize,
       MPxNode::kDeformerNode
   );
    return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus status;
    // creating the MFnPlugin object
    MFnPlugin fnPlugin(obj);
    // deregistering the node from maya
    status = fnPlugin.deregisterNode(RippleDeformer::id);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return MS::kSuccess;
}