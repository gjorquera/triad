/*!
 * @mainpage Triad: 2D Triangle Mesh Refinement Algorithms
 *
 * @section Introduction
 *
 * Triad is an application made to study different kinds of triangle mesh
 * refinement algorithms.
 *
 * The application has two interfaces: a GUI interface to visualize the loaded
 * and refined meshes as well as information about the mesh itself, and a CLI
 * interface to benchmark (time used) the different algorithms. At the moment
 * the application works with a secuential version of the Lepp-Bisection
 * refinement algorithm.
 *
 * The application is divided in 3 namespaces: \b Euclid, \b Viewer and \b App.
 *
 * The \b Euclid namespace implements a template library to work with 2
 * dimensional triangle meshes, although it can be extended to N dimensional
 * polygonal meshes.
 *
 * The \b Viewer namespace implements a simple abstraction of the QGLWidget to
 * be able to define and draw an OpenGL scene in a more object oriented way.
 *
 * The \b App namespace contains the source code that generate the user
 * interfaces as well as any class usefull only for the application, for
 * instance, any extension to the Euclid or Scene library will be located here.
 * This namespace contains the GUI and CLI interfaces of the application.
 *
 * With this division, the GUI application from the \b App section uses the \b
 * Euclid to load and generate refinements and the \b Viewer section to display
 * them using OpenGL, while the CLI application from the \b App section will
 * only use the \b Euclid section to execute and benchmark different algorithms.
 *
 * @section Class Diagram
 *
 * The relations between the different classes are explained in the following
 * diagram:
 *
 * @image html class_diagram.png
 *
 * @section Design Patterns
 *
 * The design patterns used to implement this library are the following:
 * - The classes Viewer::IFigure, Viewer::Figure and Viewer::FigureDecorator
 *   implement the Decorator Pattern to be able to switch figure render
 *   decorations.
 * - The classes Viewer::FigureDecorator and Viewer::ComplexDecorator implement
 *   the Composite Pattern to be able to add more than one decoration to the
 *   figure render process.
 * - The class Euclid::TriMeshIO implements the Factory Method pattern to create
 *   TriMesh classes from different file formats.
 * - The class Euclid::Strategy implements the Strategy pattern to be able to
 *   refine a TriMesh using different algorithms. It uses the Criterion class to
 *   decide which triangles are going to be refined.
 * - The iterator pattern is used among all the application, to iterate over the
 *   TriMesh triangles and vertices, over the Widget figures, etc.
 */

