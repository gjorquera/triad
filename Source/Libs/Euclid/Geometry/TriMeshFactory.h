#pragma once

#include <string>
#include "TriMesh.h"

namespace Euclid
{

    /*!
     * TriMesh factory.
     */
    template <class Kernel>
    class TriMeshFactory
    {
    public:
        TriMeshFactory(const std::string &filename)
        {
            _filename = filename;
        }

        virtual ~TriMeshFactory()
        {
        }

        TriMesh<Kernel>* load()
        {
            TriMesh<Kernel>* trimesh = factoryMethod(_filename);
            return trimesh;
        }

    protected:
        virtual TriMesh<Kernel>* factoryMethod(const std::string &filename) = 0;

        static void trimComments(std::string &line, const std::string &comment)
        {
            std::string::size_type pos = line.find_first_of(comment);
            if (pos != std::string::npos) line = line.substr(0, pos);
        }

        static void trimSpaces(std::string &line)
        {
            std::string::size_type pos;

            // Trim ending spaces.
            pos = line.find_last_not_of(' ');
            if (pos != std::string::npos) line =
                line.substr(0, pos + 1);

            // Trim beggining spaces.
            pos = line.find_first_not_of(' ');
            if (pos != std::string::npos) line =
                line.substr(pos, line.length());
        }

    private:
        const std::string _filename;
    };
}

