#error Documentation only
/*!
 *
 * @defgroup generators_geo 1. Grid generators
 *
      All the grids introduced by this extension can be constructed with
      generator classes.
 * @defgroup grids 2. New geometric grids
 * @defgroup fluxfunctions 3. New functors based on the magnetic field geometry

 All functors in this section model two or three-dimensional functions, i.e. they all overload the operator() like \c aCylindricalFunctor
 * @{
      @defgroup geom 3.1 New flux functions and derivatives
      @{
        @defgroup solovev The solovev magnetic field
        @defgroup taylor The Taylor state magnetic field
        @defgroup guenther The Guenther magnetic field
        @defgroup toroidal The Purely Toroidal magnetic field
        @defgroup circular The Circular magnetic field
      @}
      @defgroup magnetic 3.2 Magnetic field and associated functors
      @defgroup profiles 3.3 Profile functors based on flux functions
 * @}
 * @defgroup fieldaligned 4. Fieldaligned derivatives
 * @defgroup misc_geo 5. Miscellaneous additions
 *
 * Objects that are used to define and integrate the magnetic field lines.
 * All objects can be used in the \c evaluation and \c pullback functions.
 *
 */
/*! @mainpage
 * This extension adds new features to the FELTOR core dg library.
 *
 * - several grid generator classes are added, among them our new Hector class
 *   are added to the \c dg::geo namespace
 * - a bunch of new functors implementing various magnetic field geometries
 *   and profiles are added to the \c dg::geo namespace
 * - there are some miscellaneous additions like a flux surface average class
 * and one used to integrate the field lines for parallel derivatives all in the dg::geo namespace.
 *
 * We have a collection of writeups:
 *  - The <a href="./parallel.pdf" target="_blank">parallel derivative</a>
 *  - The <a href="./hector.pdf" target="_blank">HECTOR algorithm</a>
 */
 /** @class hide_container
  * @tparam container
  * A data container class for which the blas1 functionality is overloaded.
  * We assume that container is copyable/assignable and has a swap member function.
  * Currently this is one of
  *  - dg::HVec, dg::DVec, dg::MHVec or dg::MDVec
  *  - std::vector<dg::HVec>, std::vector<dg::DVec>, std::vector<dg::MHVec> or std::vector<dg::MDVec> .
  *
  */
 /** @class hide_matrix
  * @tparam Matrix
  * A class for which the blas2 functions are callable in connection with the container class.
  * The Matrix type can be one of:
  *  - container: A container acts as a  diagonal matrix.
  *  - dg::HMatrix and dg::IHMatrix with dg::HVec or std::vector<dg::HVec>
  *  - dg::DMatrix and dg::IDMatrix with dg::DVec or std::vector<dg::DVec>
  *  - dg::MHMatrix with dg::MHVec or std::vector<dg::MHVec>
  *  - dg::MDMatrix with dg::MDVec or std::vector<dg::MDVec>
  *  - Any type that has the SelfMadeMatrixTag specified in a corresponding
  *  TensorTraits class (e.g. Elliptic). In this case only those blas2 functions
  *  that have a corresponding member function in the Matrix class (e.g. symv( const container&, container&); ) can be called.
  *  If the container is a std::vector, then the Matrix is applied to each of the elements.
  */
