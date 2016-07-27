Mudbox plugin: simple sculpt brush   
================================      

To use cmake setting up a plugin, please check the "mudbox custom plugin clean layer" example.                  
                     
有个小问题是 The Mesh::EndChange() interface is new and not at old sdk, for example I cannot find it at mudbox 2014 sdk. Using MeshChange::Finish() is right, and one more step is to delete these meshChanges stored:
it.value()->Fisish();
delete it.value();
it.value() = NULL;
In this way, every stroke will have a new MeshChange.         
       