/*!
 * @mainpage Triad: 2D Triangle Mesh Refinement Algorithms
 *
 * @section Introduction
 *
 * Triad is an application made to study different kinds of triangle mesh
 * refinement algorithms. In particular, the implementation of a parallel
 * version of the Lepp Bisection refinement algorithm.
 *
 * At the moment, the application has only a GUI interface. It's main purpose is
 * to be able to visualize the loaded and refined meshes as well as information
 * about the mesh itself. A CLI interface will be added soon that will implement
 * benchmark features to test the different algorithms.
 *
 * The application is divided in 3 namespaces: \b Euclid, \b Viewer and \b App.
 *
 * The \b Euclid namespace implements a template library to work with 2
 * dimensional triangle meshes, although it can be extended to N dimensional
 * polygonal meshes. It uses Eigen 2 for the basic geometry definitions.
 *
 * The \b Viewer namespace implements a simple abstraction of the QGLWidget to
 * be able to define and draw an OpenGL scene in a more object oriented way.
 *
 * The \b App namespace contains the source code that generate the user
 * interfaces as well as any class usefull only for the application, for
 * instance, any extension to the Euclid or Scene library will be located here.
 *
 * With this division, the GUI application from the \b App section uses the \b
 * Euclid to load and generate refinements and the \b Viewer section to display
 * them using OpenGL, while the CLI application from the \b App section will
 * only use the \b Euclid section to benchmark different algorithms.
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
 */

