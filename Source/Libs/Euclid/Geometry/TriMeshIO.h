#pragma once

#include <cassert>
#include <QString>
#include "TriMesh.h"

namespace Euclid
{

    /*!
     * TriMesh input output class.
     *
     * This class defines the \b load and \b save method that must be
     * implemented by concrete file format classes to load and save meshes.
     *
     * @todo Convert std::string to QString
     */
    template <class Kernel>
    class TriMeshIO
    {
    public:
        TriMeshIO(QString& filename, TriMesh<Kernel>* trimesh)
        {
            assert(trimesh != 0);
            _filename = filename;
            _trimesh = trimesh;
        }

        virtual ~TriMeshIO()
        {
        }

        virtual void load() = 0;

        virtual void save() = 0;

    protected:
        QString& filename()
        {
            return _filename;
        }

        TriMesh<Kernel>* trimesh()
        {
            return _trimesh;
        }

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
        QString _filename;
        TriMesh<Kernel>* _trimesh;
    };
}

