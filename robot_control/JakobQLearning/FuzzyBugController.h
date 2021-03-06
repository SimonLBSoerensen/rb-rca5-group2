#ifndef FUZZYBUGCONTROLLER_H
#define FUZZYBUGCONTROLLER_H

/*************************************************************/
/*************************************************************/

#include "LaserScanner.h"
#include <fl/Headers.h>

struct ControlOutput
{
    float direction;
    float speed;
};

/*************************************************************/
/*************************************************************/

class FuzzyBugController
{
public:
    FuzzyBugController(LaserScanner* pc_laser_scanner);
    virtual ~FuzzyBugController() = default;

    virtual void buildController();
    virtual ControlOutput getControlOutput(float angleError, float goalDistance, float center_angle_pct);

protected:
    LaserScanner*        m_pcLaserScanner;

    fl::Engine*          m_pcFLEngine;

    fl::InputVariable*   m_pflSensorLeft;
    fl::InputVariable*   m_pflSensorCenter;
    fl::InputVariable*   m_pflSensorRight;
    fl::InputVariable*   m_pflAngleError;
    fl::InputVariable*   m_pflGoalDistance;

    fl::OutputVariable*  m_pflSteerDirection;
    fl::OutputVariable*  m_pflSpeed;
};

/*************************************************************/
/*************************************************************/

#endif // FUZZYBUGCONTROLLER_H
