# RippleDeformer
A custom deformation node for Maya that deforms a shape node. Deformation values are influenced by Maya's paint weights. Plugin is written using Maya's C++ api.

### Prerequisites
This plugin has been compiled for Maya 2019.
If you wish to run this for another version of maya, you will need to
clone the repository, change the version and re-compile.

### Usage
The plugin has already been compiled so feel free to download
the plugin directly from here: [.mll file](https://github.com/KieranKnight/RippleDeformer/blob/master/x64/Debug/RippleDeformer.mll)

However, if you want to make any modifications to the code you will need to
clone the code locally and re-compile this code.

Within Maya go to Settings -> Plugin Manager -> Browse
Find the .mll file that you have either compiled or downloaded.

Either create or select a mesh object and run the following code:

```
cmds.deformer(type="rippleDeformer")
```

Once you've run the command, you'll see that a rippleDeformer node has been connected to the object. If you select this node you'll see two attributes; AmplitudeValue and Displace. Changing these values will start to deform the mesh within the maya scene. Both of these attributes are keyable so a form of animation can be applied to the mesh. 

You are also able to modify the deformation location by right clicking the mesh > Paint > rippleDeformer > rippleDeformer-weights. Using Maya's paint weights, the deformation can be isolated and modified to achieve a more desierable output.

Feel free to use this as an example! :) 
