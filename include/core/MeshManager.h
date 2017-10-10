#pragma once

#include <fstream>
#include <stdlib.h> // For atoi, ...
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Mesh.h"
#include "Singleton.h"


/**
 * Singleton manager for meshes.
 *
 * \since   August 2017
 * \author  Constantin Masson
 */
class MeshManager : private Singleton<MeshManager> {
    public:
        // ---------------------------------------------------------------------
        // Attributes
        // ---------------------------------------------------------------------

        /** List of all loaded meshes. */
        std::vector<Mesh> listMeshes; // TODO Change to private

    private:
        /** Keep track if manager has been initialized. */
        bool isInitialized;


        // ---------------------------------------------------------------------
        // Singleton Override
        // ---------------------------------------------------------------------
    private:
        MeshManager();
        friend Singleton<MeshManager>;

    public:
        using Singleton<MeshManager>::getInstance;
        using Singleton<MeshManager>::getInstancePtr;

    public:
        // ---------------------------------------------------------------------
        // Init methods
        // ---------------------------------------------------------------------

        /**
         * Initialize the MeshManager.
         * Should be called once at the beginning.
         * Do nothing if already already called.
         */
        void startUp();

        /**
         * Stop and clean the MeshManager.
         * Should be called once at the end.
         * Do nothing if already already called.
         */
        void shutDown();

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
