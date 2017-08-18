#ifndef ENGINE_CORE_MESH_MANAGER_H_
#define ENGINE_CORE_MESH_MANAGER_H_

#include <fstream>
#include <stdlib.h> // For atoi, ...
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Mesh.h"


/**
 * Singleton manager for meshes.
 *
 * \since   August 2017
 * \author  Constantin Masson
 */
class MeshManager {
    private:
        // ---------------------------------------------------------------------
        // Attributes
        // ---------------------------------------------------------------------

        /** List of all loaded meshes. */
        std::vector<Mesh> listMeshes;

        /** Keep track if manager has been initialized */
        bool isInitialized;

        /** The famous singleton element */
        static MeshManager* mSingleton;

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

    public:
        // ---------------------------------------------------------------------
        // Init methods
        // ---------------------------------------------------------------------

        /**
         * Returns the singleton instance.
         *
         * \return Singleton instance.
         */
        static MeshManager& getSingleton(void);

        /**
         * Returns the pointer to the singleton instance.
         *
         * \return Pointer to the singleton instance.
         */
        static MeshManager* getSingletonPtr(void);

        /**
         * Initialize the MeshManager.
         * Should be called once at the beginning.
         * Do nothing if already already called.
         */
        void startUp(void);

        /**
         * Stop and clean the MeshManager.
         * Should be called once at the end.
         * Do nothing if already already called.
         */
        void shutDown(void);

    public:
        // ---------------------------------------------------------------------
        // Class methods
        // ---------------------------------------------------------------------

        /**
         * Load meshes from a Babylone JSON file.
         * If successfully loaded, add meshes in list of registered meshes.
         *
         * \see
         * https://doc.babylonjs.com/generals/file_format_map_(.babylon)#meshes
         *
         * \param file File to load.
         */
        void loadMeshesFromJSON(const char* file);
};


#endif // Header guard



