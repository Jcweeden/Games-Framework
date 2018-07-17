#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
  //init an XML document to load into
  TiXmlDocument xmlDoc;
    
  //load the XML file given
  if(!xmlDoc.LoadFile(stateFile))
  {
    //if does not load then return and print error message
    std::cerr << xmlDoc.ErrorDesc() << " " << stateFile << "\n";
    return false;
  }
    
  //get the root element of XML
  TiXmlElement* pRoot = xmlDoc.RootElement();
    
  //will store the node that is the header of the stateID we are looking for
  TiXmlElement* pStateRoot = 0;
  //checks the name of each child of the root node to see if it matches the parameter stateID
  for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    //if the node matches the stateID
    if(e->Value() == stateID)
    {
      //save the node that holds data for the stateID we are looking for
      pStateRoot = e;
      break;
    }
  }
  
  //will store the node that is the header of the textures in stateID
  TiXmlElement* pTextureRoot = 0;
    
  //checks the name of each child of the stateID node to see which match the TEXTURES
  for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    //if the node matches the TEXTURES
    if(e->Value() == std::string("TEXTURES"))
    {
      //save the node that holds data for the TEXTURES
      pTextureRoot = e;
      break;
    }
  }
    
  //pass this node that holds textures for the stateID into a function to parse the textures
  parseTextures(pTextureRoot, pTextureIDs);

  
  //will store the node that is the header of the OBJECTS in stateID
  TiXmlElement* pObjectRoot = 0;
    
  //checks the name of each child of the stateID node to see which match the OBJECTS
  for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    //if the node matches the OBJECTS
    if(e->Value() == std::string("OBJECTS"))
    {
      //save the node that holds data for the OBJECTS
      pObjectRoot = e;
      break;
    }
  }

  //pass this node that holds objects for the stateID into a function to parse the objects
  parseObjects(pObjectRoot, pObjects);

  //success
  return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
  //for each child node of TEXTURES from the XML file
  for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    //parse out the filename and ID
    std::string filenameAttribute = e->Attribute("filename");
    std::string idAttribute = e->Attribute("ID");

    //then add the ID into the vector of textures within the state
    pTextureIDs->push_back(idAttribute);

    //and also add the text to TheTextureManager
    TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
  }
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects)
{
  //for each child node of OBJECTS from the XML file
  for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    //temp storage, will be passed into Creator
    int x, y, width, height, numFrames, callbackID, animSpeed;
    std::string textureID;

    //parse out the gameObject attributes
    //    e->Attribute("x", &x);
    // sets variable x to value contained within 'x' in the XML file
    e->Attribute("x", &x);
    e->Attribute("y", &y);
    e->Attribute("width",&width);
    e->Attribute("height", &height);
    e->Attribute("numFrames", &numFrames);
    e->Attribute("callbackID", &callbackID);
    e->Attribute("animSpeed", &animSpeed);        
    textureID = e->Attribute("textureID");

    //create an Object of the type defined in XML, using the GameObjectFactory and respective Creator
    GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));

    //load the data into the new GameObject using the load() method
    pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));

    //then add the GameObject into the vector of GameObjects within the state
    pObjects->push_back(pGameObject);
  }
}
