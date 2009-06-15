Description
===========

Triad is a 2D triangle mesh refinement application aimed at algorithm analysis
and research.

This means that the application is designed and implemented to be easy to extend
with new algorithms or visual properties.

Dependencies
============

Triad depends on the following libraries:

  - [Qt 4.4](http://www.qtsoftware.com/products)

Compilation
===========

To compile simply execute

    qmake && make

Documentation
=============

Open the Docs/index.html file to see the class diagram and the documentation of
all the classes.

Mesh
====

In the folder Mesh there's a 100 vertex (200 triangles aprox.) mesh.

Mesh Format
===========

The application uses the M2D file format, but other file formats can be
implemented extending the appropiate classes. For more information about the M2D
file format go to the [homepage](http://github.com/gjorquera/triangle-mesh)

