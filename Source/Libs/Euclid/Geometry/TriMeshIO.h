#pragma once

#include <cassert>
#include <QRegExp>
#include <QString>
#include "TriMesh.h"

namespace Euclid
{

    /*!
     * TriMesh input output class.
     *
     * This class defines the \b load and \b save method that must be
     * implemented by concrete file format classes to load and save meshes.
     */
    template <class Kernel>
    class TriMeshIO
    {
    public:
        typedef TriMesh<Kernel> TriMeshT;

        TriMeshIO(QString& filename, TriMeshT* trimesh)
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
        QString filename() const
        {
            return _filename;
        }

        TriMeshT* trimesh() const
        {
            return _trimesh;
        }

        static void trimComments(QString& line, const QString& comment)
        {
            int pos = line.indexOf(comment);
            if (-1 != pos) {
                line = line.left(pos);
            }
        }

        static void trimSpaces(QString& line)
        {
            int pos;

            // Trim new lines
            pos = line.indexOf("\n");
            if (-1 != pos) {
                line = line.left(pos);
            }

            // Trim ending spaces
            pos = line.lastIndexOf(QRegExp("[0-9]"));
            if (-1 != pos) {
                line = line.left(pos + 1);
            }

            // Trim beginning spaces
            pos = line.indexOf(QRegExp("[a-zA-Z]"));
            if (-1 != pos) {
                line = line.right(line.length() - pos + 1);
            }
        }

    private:
        QString _filename;
        TriMeshT* _trimesh;
    };
}

