// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_GRID_SMOKE_SOLVER3_H_
#define INCLUDE_JET_GRID_SMOKE_SOLVER3_H_

#include <jet/grid_fluid_solver3.h>

namespace jet {

//!
//! \brief      3-D grid-based smoke solver.
//!
//! This class extends GridFluidSolver2 to implement smoke simulation solver.
//! It adds smoke density and temperature fields to define the smoke and uses
//! buoyancy force to simulate hot rising smoke.
//!
//! \see Fedkiw, Ronald, Jos Stam, and Henrik Wann Jensen.
//!     "Visual simulation of smoke." Proceedings of the 28th annual conference
//!     on Computer graphics and interactive techniques. ACM, 2001.
//!
class GridSmokeSolver3 : public GridFluidSolver3 {
 public:
    //! Constructs empty smoke solver.
    GridSmokeSolver3();

    //! Destructor.
    virtual ~GridSmokeSolver3();

    //! Returns smoke diffusion coefficient.
    double smokeDiffusionCoefficient() const;

    //! Sets smoke diffusion coefficient.
    void setSmokeDiffusionCoefficient(double newValue);

    //! Returns temperature diffusion coefficient.
    double temperatureDiffusionCoefficient() const;

    //! Sets temperature diffusion coefficient.
    void setTemperatureDiffusionCoefficient(double newValue);

    //!
    //! \brief      Returns the buoyancy factor which will be multiplied to the
    //!     smoke density.
    //!
    //! This class computes buoyancy by looking up the value of smoke density
    //! and temperature, compare them to the average values, and apply
    //! multiplier factor to the diff between the value and the average. That
    //! multiplier is defined for each smoke density and temperature separately.
    //! For example, negative smoke density buoyancy factor means a heavier
    //! smoke should sink.
    //!
    //! \return     The buoyance factor for the smoke density.
    //!
    double buoyancySmokeDensityFactor() const;

    //!
    //! \brief          Sets the buoyancy factor which will be multiplied to the
    //!     smoke density.
    //!
    //! This class computes buoyancy by looking up the value of smoke density
    //! and temperature, compare them to the average values, and apply
    //! multiplier factor to the diff between the value and the average. That
    //! multiplier is defined for each smoke density and temperature separately.
    //! For example, negative smoke density buoyancy factor means a heavier
    //! smoke should sink.
    //!
    //! \param newValue The new buoyancy factor for smoke density.
    //!
    void setBuoyancySmokeDensityFactor(double newValue);

    //!
    //! \brief      Returns the buoyancy factor which will be multiplied to the
    //!     temperature.
    //!
    //! This class computes buoyancy by looking up the value of smoke density
    //! and temperature, compare them to the average values, and apply
    //! multiplier factor to the diff between the value and the average. That
    //! multiplier is defined for each smoke density and temperature separately.
    //! For example, negative smoke density buoyancy factor means a heavier
    //! smoke should sink.
    //!
    //! \return     The buoyance factor for the temperature.
    //!
    double buoyancyTemperatureFactor() const;

    //!
    //! \brief          Sets the buoyancy factor which will be multiplied to the
    //!     temperature.
    //!
    //! This class computes buoyancy by looking up the value of smoke density
    //! and temperature, compare them to the average values, and apply
    //! multiplier factor to the diff between the value and the average. That
    //! multiplier is defined for each smoke density and temperature separately.
    //! For example, negative smoke density buoyancy factor means a heavier
    //! smoke should sink.
    //!
    //! \param newValue The new buoyancy factor for temperature.
    //!
    void setBuoyancyTemperatureFactor(double newValue);

    //!
    //! \brief      Returns smoke decay factor.
    //!
    //! In addition to the diffusion, the smoke also can fade-out over time by
    //! setting the decay factor between 0 and 1.
    //!
    //! \return     The decay factor for smoke density.
    //!
    double smokeDecayFactor() const;

    //!
    //! \brief      Sets the smoke decay factor.
    //!
    //! In addition to the diffusion, the smoke also can fade-out over time by
    //! setting the decay factor between 0 and 1.
    //!
    //! \param[in]  newValue The new decay factor.
    //!
    void setSmokeDecayFactor(double newValue);

    //!
    //! \brief      Returns temperature decay factor.
    //!
    //! In addition to the diffusion, the smoke also can fade-out over time by
    //! setting the decay factor between 0 and 1.
    //!
    //! \return     The decay factor for smoke temperature.
    //!
    double smokeTemperatureDecayFactor() const;

    //!
    //! \brief      Sets the temperature decay factor.
    //!
    //! In addition to the diffusion, the temperature also can fade-out over
    //! time by setting the decay factor between 0 and 1.
    //!
    //! \param[in]  newValue The new decay factor.
    //!
    void setTemperatureDecayFactor(double newValue);

    //! Returns smoke density field.
    ScalarGrid3Ptr smokeDensity() const;

    //! Returns temperature field.
    ScalarGrid3Ptr temperature() const;

 protected:
    void onEndAdvanceTimeStep(double timeIntervalInSeconds) override;

    void computeExternalForces(double timeIntervalInSeconds) override;

 private:
    size_t _smokeDensityDataId;
    size_t _temperatureDataId;
    double _smokeDiffusionCoefficient = 0.0;
    double _temperatureDiffusionCoefficient = 0.0;
    double _buoyancySmokeDensityFactor = -0.000625;
    double _buoyancyTemperatureFactor = 5.0;
    double _smokeDecayFactor = 0.001;
    double _temperatureDecayFactor = 0.001;

    void computeDiffusion(double timeIntervalInSeconds);

    void computeBuoyancyForce(double timeIntervalInSeconds);
};

}  // namespace jet

#endif  // INCLUDE_JET_GRID_SMOKE_SOLVER3_H_
