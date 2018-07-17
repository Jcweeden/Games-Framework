#ifndef _StateParser_
#define _StateParser_

#include "tinyxml.h"
#include <iostream>
#include <vector>

class GameObject;


//called upon running of onEnter() when opening a new gamestate, and then discarded
//parses the XML associated for that state to determine which objects to instantiate
//via their Creator classes.
class StateParser {
public:

  //parses given XML file to locate the the node storing list ofobjects and textures
  //to be instantiated in the state named
  //parameters:
  //filename of XML file to read from
  //name of the state  which indicates the section of the XML to parse from)
  //a pointer to the vectors holding the gameObjects and textures used in a state
  bool parseState(const char *stateFile,
                  std::string stateID,
                  std::vector<GameObject *> *pObjects,
                  std::vector<std::string> *pTextureIDs);


private:

  //given the node in the XML file that contains the textures for the state,
  //the function parses this data to get the texture's filenames and IDs, and
  //then proceeds to load them in the TextureManager, and add them to the State's
  //vector of textureIDs
  void parseTextures (TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);

  //given the node in the XML file that contains the objects for the state,
  //the function parses this data to get each GameObject's attributes, then
  //creates a new GameObject of that type using its respective creator, and
  //saves it into the State's vector of GameObjects
  void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
};

#endif
