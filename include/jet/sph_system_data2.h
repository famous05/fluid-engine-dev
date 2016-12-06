// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_SPH_SYSTEM_DATA2_H_
#define INCLUDE_JET_SPH_SYSTEM_DATA2_H_

#include <jet/particle_system_data2.h>

namespace jet {

//!
//! \brief      2-D SPH particle system data.
//!
//! This class extends ParticleSystemData2 to specialize the data model for SPH.
//! It includes density and pressure array as a default particle attribute, and
//! it also contains SPH utilities such as interpolation operator.
//!
class SphSystemData2 : public ParticleSystemData2 {
 public:
    //! Constructs empty SPH system.
    SphSystemData2();

    //! Destructor.
    virtual ~SphSystemData2();

    //!
    //! \brief Sets the radius.
    //!
    //! Sets the radius of the particle system. The radius will be interpreted
    //! as target spacing.
    //!
    void setRadius(double newRadius) override;

    //! Returns the density array accessor (immutable).
    ConstArrayAccessor1<double> densities() const;

    //! Returns the density array accessor (mutable).
    ArrayAccessor1<double> densities();

    //! Returns the pressure array accessor (immutable).
    ConstArrayAccessor1<double> pressures() const;

    //! Returns the pressure array accessor (mutable).
    ArrayAccessor1<double> pressures();

    //!
    //! \brief Updates the density array with the latest particle positions.
    //!
    //! This function updates the density array by recalculating each particle's
    //! latest nearby particles' position.
    //!
    //! \warning You must update the neighbor searcher
    //! (SphSystemData2::buildNeighborSearcher) before calling this function.
    //!
    void updateDensities();

    //! Sets the target density of this particle system.
    void setTargetDensity(double targetDensity);

    //! Returns the target density of this particle system.
    double targetDensity() const;

    //! Returns the mass of a particle in kg.
    double mass() const;

    //!
    //! \brief Sets the target particle spacing in meters.
    //!
    //! Once this function is called, hash grid and density should be
    //! updated using updateHashGrid() and updateDensities).
    //!
    void setTargetSpacing(double spacing);

    //! Returns the target particle spacing in meters.
    double targetSpacing() const;

    //!
    //! \brief Sets the relative kernel radius.
    //!
    //! Sets the relative kernel radius compared to the target particle
    //! spacing (i.e. kernal radius / target spacing).
    //! Once this function is called, hash grid and density should
    //! be updated using updateHashGrid() and updateDensities).
    //!
    void setRelativeKernelRadius(double relativeRadius);

    //!
    //! \brief Returns the relative kernel radius.
    //!
    //! Returns the relative kernel radius compared to the target particle
    //! spacing (i.e. kernal radius / target spacing).
    //!
    double relativeKernelRadius() const;

    //! Returns the kernel radius in meters unit.
    double kernelRadius() const;

    //! Returns sum of kernel function evaluation for each nearby particle.
    double sumOfKernelNearby(const Vector2D& position) const;

    //!
    //! \brief Returns interpolated value at given origin point.
    //!
    //! Returns interpolated scalar data from the given position using
    //! standard SPH weighted average. The data array should match the
    //! particle layout. For example, density or pressure arrays can be
    //! used.
    //!
    //! \warning You must update the neighbor searcher
    //! (SphSystemData2::buildNeighborSearcher) before calling this function.
    //!
    double interpolate(
        const Vector2D& origin,
        const ConstArrayAccessor1<double>& values) const;

    //!
    //! \brief Returns interpolated vector value at given origin point.
    //!
    //! Returns interpolated vector data from the given position using
    //! standard SPH weighted average. The data array should match the
    //! particle layout. For example, velocity or acceleration arrays can be
    //! used.
    //!
    //! \warning You must update the neighbor searcher
    //! (SphSystemData2::buildNeighborSearcher) before calling this function.
    //!
    Vector2D interpolate(
        const Vector2D& origin,
        const ConstArrayAccessor1<Vector2D>& values) const;

    //!
    //! Returns the gradient of the given values at i-th particle.
    //!
    //! \warning You must update the neighbor lists
    //! (SphSystemData2::buildNeighborLists) before calling this function.
    //!
    Vector2D gradientAt(
        size_t i,
        const ConstArrayAccessor1<double>& values) const;

    //!
    //! Returns the laplacian of the given values at i-th particle.
    //!
    //! \warning You must update the neighbor lists
    //! (SphSystemData2::buildNeighborLists) before calling this function.
    //!
    double laplacianAt(
        size_t i,
        const ConstArrayAccessor1<double>& values) const;

    //!
    //! Returns the laplacian of the given values at i-th particle.
    //!
    //! \warning You must update the neighbor lists
    //! (SphSystemData2::buildNeighborLists) before calling this function.
    //!
    Vector2D laplacianAt(
        size_t i,
        const ConstArrayAccessor1<Vector2D>& values) const;

    //! Builds neighbor searcher with kernel radius.
    void buildNeighborSearcher();

    //! Builds neighbor lists with kernel radius.
    void buildNeighborLists();

 private:
    //! Mass of a particle in kilograms (kg).
    //! Mass is determined by the target density and spacing.
    double _mass;

    //! Target density of this particle system in kg/m^2.
    double _targetDensity = 1000.0;

    //! Target spacing of this particle system in meters.
    double _targetSpacing = 0.1;

    //! Relative radius of SPH kernel.
    //! SPH kernel radius divided by target spacing.
    double _kernelRadiusOverTargetSpacing = 1.8;

    //! SPH kernel radius in meters.
    double _kernelRadius;

    size_t _pressureDataId;

    size_t _densityDataId;

    //! Do not allow setMass call for SPH-type data.
    //! Mass is determined by the target density and spacing.
    void setMass(double newMass) override;

    //! Computes the mass based on the target density and spacing.
    void computeMass();
};

//! Shared pointer for the SphSystemData2 type.
typedef std::shared_ptr<SphSystemData2> SphSystemData2Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_SPH_SYSTEM_DATA2_H_
