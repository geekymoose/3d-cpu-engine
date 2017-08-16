#include "core/MeshManager.h"


// -----------------------------------------------------------------------------
// Init - Constructors
// -----------------------------------------------------------------------------
MeshManager::MeshManager(void) {
}

MeshManager::~MeshManager(void) {
}

MeshManager& MeshManager::getInstance(void) {
    static MeshManager mMeshManager; // The famous singleton
    return mMeshManager;
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
Mesh MeshManager::loadMeshFromJSON(const char* file) {
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;
    ptree pt;
    // TODO
}
