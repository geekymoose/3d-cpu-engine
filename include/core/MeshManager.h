#ifndef ENGINE_CORE_MESH_MANAGER_H_
#define ENGINE_CORE_MESH_MANAGER_H_

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Mesh.h"

/**
 * Singleton manager for meshes.
 */
class MeshManager {
    private:
        // ---------------------------------------------------------------------
        // Attributes
        // ---------------------------------------------------------------------
        /** List of all loaded meshes. */
        std::vector<Mesh> listMeshes;

        /** Keep track if MeshManager has been initialized. */
        bool isInitialized;

    private:
        // ---------------------------------------------------------------------
        // Forbidden area
        // ---------------------------------------------------------------------

        /** Explicitely disable copy constructor. */
        MeshManager(MeshManager const& obj);

        /** Explicitely disable constructor. */
        MeshManager(void);

        /** Explicitely disable destructor. */
        ~MeshManager(void);

        // Explicitely disable = operator. */
        MeshManager& operator=(MeshManager const& other);

    public:
        // ---------------------------------------------------------------------
        // Init methods
        // ---------------------------------------------------------------------
        /**
         * Returns the singleton instance.
         *
         * \return Singleton instance.
         */
        static MeshManager& getInstance(void);

        /**
         * Initialize the MeshManager.
         */
        void startUp(void);

        /**
         * Stop and clean the MeshManager.
         */
        void shutDown(void);

    public:
        // ---------------------------------------------------------------------
        // Class methods
        // ---------------------------------------------------------------------

        /**
         * Load a mesh from a JSON file.
         * If successfully loaded, add mesh in list of registered meshes.
         *
         * \param file File to load.
         * \return The loaded mesh or null if error.
         */
        Mesh loadMeshFromJSON(const char* file);
};


#endif // Header guard



