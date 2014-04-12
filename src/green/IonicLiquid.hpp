#ifndef IONICLIQUID_HPP
#define IONICLIQUID_HPP

#include <iosfwd>
#include <string>

#include "Config.hpp"

#include "EigenPimpl.hpp"

#include "DerivativeTypes.hpp"
#include "ForIdGreen.hpp"
#include "GreenData.hpp"
#include "GreensFunction.hpp"
#include "GreensFunctionFactory.hpp"
#include "IGreensFunction.hpp"

/*! \file IonicLiquid.hpp
 *  \class IonicLiquid<T>
 *  \brief Green's functions for ionic liquid, described by the linearized Poisson-Boltzmann equation.
 *  \author Luca Frediani, Roberto Di Remigio
 *  \date 2013-2014
 *  \tparam T evaluation strategy for the function and its derivatives
 */

template <typename T>
class IonicLiquid : public GreensFunction<T>
{
public:
    IonicLiquid(double epsilon, double kappa) : GreensFunction<T>(false),
        epsilon_(epsilon), kappa_(kappa) {}
    virtual ~IonicLiquid() {}
    /*! 
     *  Returns value of the directional derivative of the 
     *  Greens's function for the pair of points p1, p2:
     *  \f$ \nabla_{\mathbf{p_2}}G(\mathbf{p}_1, \mathbf{p}_2)\cdot \mathbf{n}_{\mathbf{p}_2}\f$
     *  Notice that this method returns the directional derivative with respect
     *  to the probe point, thus assuming that the direction is relative to that point.
     *  
     *  \param[in] direction the direction
     *  \param[in]        p1 first point
     *  \param[in]        p2 second point
     */
    virtual double derivative(const Eigen::Vector3d & direction,
                              const Eigen::Vector3d & p1, const Eigen::Vector3d & p2) const;
    
    virtual double epsilon() const { return epsilon_; }

    friend std::ostream & operator<<(std::ostream & os, IonicLiquid & gf) {
        return gf.printObject(os);
    }
private:
    /*!
     *  Evaluates the Green's function given a pair of points
     *
     *  \param[in] source the source point
     *  \param[in]  probe the probe point
     */
    virtual T operator()(T * source, T * probe) const;
    double epsilon_;
    double kappa_;
    virtual std::ostream & printObject(std::ostream & os);
};

namespace
{
    struct buildIonicLiquid {
        template <typename DerivativeType>
        IGreensFunction * operator()(const greenData & _data) {
            return new IonicLiquid<DerivativeType>(_data.epsilon, _data.kappa);
        }
    };

    IGreensFunction * createIonicLiquid(const greenData & _data)
    {
        buildIonicLiquid build;
        return for_id<derivative_types>(build, _data, _data.how);
    }
    const std::string IONICLIQUID("IonicLiquid");
    const bool registeredIonicLiquid =
        GreensFunctionFactory::TheGreensFunctionFactory().registerGreensFunction(
            IONICLIQUID, createIonicLiquid);
}

#endif // IONICLIQUID_HPP
