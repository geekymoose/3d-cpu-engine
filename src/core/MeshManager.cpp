#include "core/MeshManager.h"


// -----------------------------------------------------------------------------
// Attributes
// -----------------------------------------------------------------------------
MeshManager* MeshManager::mSingleton = NULL;


// -----------------------------------------------------------------------------
// Init - Constructors
// -----------------------------------------------------------------------------
MeshManager::MeshManager(void) {
    MeshManager::mSingleton = NULL;
    this->isInitialized = false;
}

MeshManager::~MeshManager(void) {
    MeshManager::mSingleton = NULL;
}

MeshManager& MeshManager::getSingleton(void) {
    if(MeshManager::mSingleton == NULL) {
        MeshManager::mSingleton = new MeshManager();
    }
    return *mSingleton;
}

MeshManager* MeshManager::getSingletonPtr(void) {
    if(MeshManager::mSingleton == NULL) {
        MeshManager::mSingleton = new MeshManager();
    }
    return mSingleton;
}

void MeshManager::startUp(void) {
    if(!isInitialized) {
        this->isInitialized = true;
    }
}

void MeshManager::shutDown(void) {
    if(isInitialized) {
        this->isInitialized = false;
        this->listMeshes.clear();
    }
}


// -----------------------------------------------------------------------------
// Class functions
// -----------------------------------------------------------------------------
void MeshManager::loadMeshesFromJSON(const char* file) {
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;
    ptree pt;
    std::ifstream jsonFile(file);
    read_json(jsonFile, pt);
    for(auto & child : pt.get_child("meshes")) {
        std::string name = child.second.get<std::string>("name", "NameNotFound");

        // Vertices
        std::vector<float> listVertices;
        for(auto & vertice : child.second.get_child("vertices")) {
            std::string value = vertice.second.data();
            listVertices.push_back(::atof(value.c_str()));
        }

        // Faces
        std::vector<float> listIndices;
        for(auto & indice : child.second.get_child("indices")) {
            std::string value = indice.second.data();
            listIndices.push_back(::atof(value.c_str()));
        }

        int uvCount = child.second.get<int>("uvCount", 0);
        // uvCount == 0 -> step 6 / 1 -> step 8 / 2 -> step 10
        int verticesStep = 6 + (uvCount * 2);
        int nbVertices = listVertices.size() / verticesStep;
        int nbFaces = listIndices.size() / 3;
    }
}
