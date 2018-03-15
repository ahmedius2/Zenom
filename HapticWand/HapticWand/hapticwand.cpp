#include "hapticwand.h"

using namespace Hardware;

#define PI          (3.1415926535897932384626433832795)

#define L1          (5.670       * 0.0254)  /* length of link 1 in meters */
#define L2          (7.717       * 0.0254)  /* length of link 2 in meters */
#define L3          (8.32232120  * 0.0254)  /* length of link 3 in meters */
#define L4          (1.417202685 * 0.0254)  /* length of link 4 in meters */
#define L5          (1.750       * 0.0254)  /* length of link 5 in meters */
#define L6          (7.000       * 0.0254)  /* length of link 6 in meters */
#define L7          (2.078363285 * 0.0254)  /* length of link 7 in meters */

/* Link lengths of the haptic wand links in meters */
const double HapticWand::l[7] = { L1, L2, L3, L4, L5, L6, L7 };

/* analog output channels driving the haptic wand motors */
const unsigned int HapticWand::analogChannels[6] = { 0, 1, 2, 3, 4, 5 };

/* encoder input channels for the haptic wand joint encoders */
const unsigned int HapticWand::encoderChannels[6] = { 0, 1, 2, 3, 4, 5 };

/* digital output channels driving the amplifier enable lines */
const unsigned int HapticWand::digitalOutputChannels[6] = { 0, 1, 2, 3, 16, 17 };

#define KT_SMALL    (52.5e-3)   /* N-m per amp */
#define KT_LARGE    (191e-3)    /* N-m per amp */

#define LIMIT_1_SMALL   (7.00)  /* current limits in amps */
#define LIMIT_2_SMALL   (2.15)  /* current limits in amps */
#define LIMIT_1_LARGE   (5.00)  /* current limits in amps */
#define LIMIT_2_LARGE   (1.69)  /* current limits in amps */

#define TIMEOUT_1_SMALL   ( 0.2)    /* timeout in seconds */
#define TIMEOUT_2_SMALL   (10.0)    /* timeout in seconds */
#define TIMEOUT_1_LARGE   ( 0.2)    /* timeout in seconds */
#define TIMEOUT_2_LARGE   (10.0)    /* timeout in seconds */

HapticWand::HapticWand()
{

}

void HapticWand::open(const char *cardType, const int cardIdentifier)
{
    HIL::open( cardType, cardIdentifier );

    // Configures digital I/O lines as outputs.
    setDigitalOutputDirection( digitalOutputChannels, NUM_DIGITAL_OUTPUT );

    for( int i = 0; i < NUM_JOINTS; ++i )
    {
        current_limiters[i].count = 0;
        current_limiters[i].mean = 0;
        current_limiters[i].state = 0;
        current_limiters[i].time = 0;
    }
}

void HapticWand::enableWand()
{
    // enable amplifiers
    const bool amplifiers[NUM_DIGITAL_OUTPUT] = { 1, 1, 1, 1, 1, 1 };
    writeDigital( digitalOutputChannels, amplifiers, NUM_DIGITAL_OUTPUT );

    // The first sample when the controller is ran.
    double joint_angles[6];        // joint angles in radians
    jointAngles( joint_angles );
    forwardKinematics( joint_angles, mFirstSample );
}

void HapticWand::disableWand()
{
    // disable amplifiers
    const bool amplifiers[NUM_DIGITAL_OUTPUT] = { 0, 0, 0, 0, 0, 0 };
    writeDigital( digitalOutputChannels, amplifiers, NUM_DIGITAL_OUTPUT );

    // drive the motors with 0 V
    const double torques[NUM_JOINTS] = { 0, 0, 0, 0, 0, 0 };
    writeAnalog( analogChannels, torques, NUM_JOINTS );
}

void HapticWand::calibrateWand()
{
    disableWand();
    resetEncoders();
}

void HapticWand::resetEncoders()
{
    // reset the encoders to zero
    resetEncoder( encoderChannels, NUM_JOINTS );
}

void HapticWand::readEncoders(int *counts)
{
    HIL::readEncoder( encoderChannels, counts, NUM_JOINTS );
}

void HapticWand::writeAnalogs(const double *voltages)
{
    HIL::writeAnalog( analogChannels, voltages, NUM_JOINTS );
}

void HapticWand::jointAngles(double* jointAngles)
{
    const double offsets[] = { 0.12760527954869, 3.0139873740411, 0.12760527954869, 3.0139873740411, 0.0000, 0.0000 };
    const double factors[] = { 2*PI/20000, 2*PI/20000, -2*PI/20000, -2*PI/20000, 2*PI/20000, 2*PI/20000 };

    // convert counts to radians and rearrange channels appropriately
    for( int i = 0; i < NUM_JOINTS; ++i )
    {
        jointAngles[i] = - HIL::readEncoder( encoderChannels[i] ) * factors[i] + offsets[i];
    }
}

void HapticWand::forwardKinematics(double* theta, double *worldCoordinates)
{
    // compute joint angles to world co-ordinates
    worldCoordinates[0] = l[4] / 0.2e1 + cos(theta[2]) * l[0] / 0.2e1 + cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1] / 0.2e1 + cos(theta[0]) * l[0] / 0.2e1 + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] / 0.2e1;
    worldCoordinates[1] = cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 - sin(theta[5]) * (-l[6] + l[3]) / 0.2e1 + cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 - sin(theta[4]) * (l[6] - l[3]) / 0.2e1;
    worldCoordinates[2] = sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 + cos(theta[5]) * (-l[6] + l[3]) / 0.2e1 + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 + cos(theta[4]) * (l[6] - l[3]) / 0.2e1;
    worldCoordinates[3] = -atan((cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])));
    worldCoordinates[4] = atan((cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])));
}

void HapticWand::generateForces(double period, const double joint_angles[NUM_JOINTS], const double world_forces[NUM_WORLD] )
{
    double joint_torques[NUM_JOINTS];       /* joint torques in N-m */
    double motor_currents[NUM_JOINTS];      /* motor currents in amps */
    double output_voltages[NUM_JOINTS];     /* output voltages in volts */

    /* Compute the output voltages needed to produce the desired world-space generalized forces at the end-effector */
    inverse_force_kinematics(joint_angles, world_forces, joint_torques);    /* convert generalized forces to joint torques */
    joint_torques_to_motor_currents(joint_torques, motor_currents);         /* convert joint torques to motor currents */
    limit_currents( period, motor_currents);               /* limit motor currents to prevent overheating */
    motor_currents_to_output_voltages(motor_currents, output_voltages);     /* compute output voltages required to produce the motor currents */

    /* Write the voltages to the outputs */
    writeAnalogs( output_voltages );
}

void HapticWand::joint_torques_to_motor_currents(const double joint_torques[NUM_JOINTS], double motor_currents[NUM_JOINTS])
{
    static const double torque_constants[NUM_JOINTS] = {KT_SMALL, KT_SMALL, KT_SMALL, KT_SMALL, KT_LARGE, KT_LARGE};

    int i;
    for (i=NUM_JOINTS-1; i >= 0; --i)
        motor_currents[i] = joint_torques[i] / torque_constants[i]; // convert N-m to amps
}

void HapticWand::motor_currents_to_output_voltages(const double motor_currents[NUM_JOINTS], double voltages[NUM_JOINTS])
{
    int i;
    for (i=NUM_JOINTS-1; i >= 0; --i)
        voltages[i] = 2*motor_currents[i];

    voltages[2] = -voltages[2];
    voltages[3] = -voltages[3];
}

void HapticWand::limit_currents(double dt, double motor_currents[NUM_JOINTS])
{
    static const double current_limit_1[NUM_JOINTS]  = {LIMIT_1_SMALL,   LIMIT_1_SMALL,   LIMIT_1_SMALL,   LIMIT_1_SMALL,   LIMIT_1_LARGE,   LIMIT_1_LARGE};
    static const double current_limit_2[NUM_JOINTS]  = {LIMIT_2_SMALL,   LIMIT_2_SMALL,   LIMIT_2_SMALL,   LIMIT_2_SMALL,   LIMIT_2_LARGE,   LIMIT_2_LARGE};
    static const double timeout_1[NUM_JOINTS]        = {TIMEOUT_1_SMALL, TIMEOUT_1_SMALL, TIMEOUT_1_SMALL, TIMEOUT_1_SMALL, TIMEOUT_1_LARGE, TIMEOUT_1_LARGE};
    static const double timeout_2[NUM_JOINTS]        = {TIMEOUT_2_SMALL, TIMEOUT_2_SMALL, TIMEOUT_2_SMALL, TIMEOUT_2_SMALL, TIMEOUT_2_LARGE, TIMEOUT_2_LARGE};

    int index;
    for (index = NUM_JOINTS-1; index >= 0; --index)
    {
        double value = fabs(motor_currents[index]);

        switch (current_limiters[index].state)
        {
        case 0: // Limiting to the upper limits and waiting for input to exceed lower limits
            if (value > current_limit_2[index])
            {
                current_limiters[index].state = 1;
                current_limiters[index].time  = 0;
                current_limiters[index].count = 0;
                current_limiters[index].mean  = value;

                if (value > current_limit_1[index])
                    motor_currents[index] = (motor_currents[index] > 0) ? current_limit_1[index] : -current_limit_1[index];
                else
                    motor_currents[index] = motor_currents[index];
            }
            else
                motor_currents[index] = motor_currents[index];

            break;

        case 1: // Limiting to the upper limits and waiting for peak time limit
            current_limiters[index].mean += value;
            current_limiters[index].time += dt;
            current_limiters[index].count++;

            if (current_limiters[index].time >= timeout_1[index])
            {
                current_limiters[index].mean /= current_limiters[index].count + 1;
                if (current_limiters[index].mean > current_limit_2[index])
                {
                    current_limiters[index].state = 2;
                    current_limiters[index].time  = 0;
                    current_limiters[index].count = 0;
                    motor_currents[index] = (motor_currents[index] > 0) ? current_limit_2[index] : -current_limit_2[index];
                }
                else
                {
                    current_limiters[index].state = 0;
                    motor_currents[index] = motor_currents[index];
                }
            }
            else if (value > current_limit_1[index])
                motor_currents[index] = (motor_currents[index] > 0) ? current_limit_1[index] : -current_limit_1[index];
            else
                motor_currents[index] = motor_currents[index];

            break;

        case 2: // Limiting to the lower limits and waiting for motors to recover
            current_limiters[index].time += dt;
            current_limiters[index].count++;

            if (current_limiters[index].time >= timeout_2[index])
            {
                if (value > current_limit_2[index])
                {
                    current_limiters[index].state = 1;
                    current_limiters[index].time  = 0;
                    current_limiters[index].count = 0;
                    current_limiters[index].mean  = value;

                    if (value > current_limit_1[index])
                        motor_currents[index] = (motor_currents[index] > 0) ? current_limit_1[index] : -current_limit_1[index];
                    else
                        motor_currents[index] = motor_currents[index];
                }
                else
                {
                    current_limiters[index].state = 0;
                    motor_currents[index] = motor_currents[index];
                }
            }
            else if (value > current_limit_2[index])
                motor_currents[index] = (motor_currents[index] > 0) ? current_limit_2[index] : -current_limit_2[index];
            else
                motor_currents[index] = motor_currents[index];

            break;
        }
    }
}

void HapticWand::inverse_force_kinematics(const double theta[NUM_JOINTS], const double F[NUM_WORLD], double tau[NUM_JOINTS])
{
    double J[NUM_WORLD][NUM_JOINTS]; /* Jacobian */

    J[0][0] = -sin(theta[0]) * l[0] / 0.2e1 - sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin
      (theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) *
      (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 *
      (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[0]) * l[0]) *
      pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1),
      -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[0]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) + (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4
      ] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4]
      + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1] / 0.2e1;

    J[0][1] = -sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0
      ], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[
      0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0],
      0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[1]) * l[0] - 0.2e1 * (sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0]) * cos(theta[1]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1
      ]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[1]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) - (sin(theta[0
      ]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[1]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0
      ] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1] / 0.2e1;

    J[0][2] = -sin(theta[2]) * l[0] / 0.2e1
      - sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(
      theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3
      ]) * l[0]) * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[2]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[
      0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[2]) * l
      [0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) *
      l[0], -0.2e1) * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l
      [0], -0.2e1))) * l[1] / 0.2e1;

    J[0][3] = -sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin
      (theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) *
      (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 *
      (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[3]) * l[0] - 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0]) *
      pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1),
      -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[3]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[
      4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[3]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4
      ] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1] / 0.2e1;

    J[0][4] = 0.0e0;

    J[0][5] = 0.0e0;

    J[1][0] = cos(theta[4]) * (cos(theta[0]) *
      l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] /
      0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] -
      cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[0]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]
      ) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[0
      ]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) + (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta
      [1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[
      1]) * l[0], -0.2e1))) * l[1]) / 0.2e1;

    J[1][1] = cos(theta[4]) * cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin
      (theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 /
      0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[1]) * l[0] - 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) *
      cos(theta[1]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1))
      * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[1]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) - (sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[1]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) *
      l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1] / 0.2e1;

    J[1][2] = cos(theta[5]) * (cos(theta[2]) * l[0] + cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l
      [0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0])
      * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[2]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(
      theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[2]) * l[0] / (l[4]
      + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1)
      * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1
      ))) * l[1]) / 0.2e1;

    J[1][3] = cos(theta[5]) * cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0]
      - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0])))
      * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1
      * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[3]) * l[0] - 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0
      ]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1
      ), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[3]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) *
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[3]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) *
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1] / 0.2e1;

    J[1][4] = -sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[
      4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[
      0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) / 0.2e1 - cos(theta[4]) * (l[6] - l[3]) / 0.2e1;

    J[1][5] = -sin(
      theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3
      ]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1
      - cos(theta[5]) * (-l[6] + l[3]) / 0.2e1;

    J[2][0] = sin(theta[4]) * (cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1])
      * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]
      ) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[
      0] - sin(theta[1]) * l[0]) * cos(theta[0]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] -
      sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[0]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) +
      (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta
      [0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1]) / 0.2e1;

    J[2][1] = sin(theta[4]) * cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[
      1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) *
      l[0]) * sin(theta[1]) * l[0] - 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[1]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] -
      cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[1]) * l[0]
      / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) - (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0
      ], -0.2e1) * sin(theta[1]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]
      , -0.2e1))) * l[1] / 0.2e1;

    J[2][2] = sin(theta[5]) * (cos(theta[2]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1)
       + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) *
      l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)
      , -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3
      ]) * l[0]) * cos(theta[2]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) *
      l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[2]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(theta[2]) * l
      [0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1]) / 0.2e1;

    J[2][3] = sin(theta[5]) * cos(PI - acos(sqrt
      (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2
      ]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1)
      + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(
      theta[3]) * l[0] - 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) *
      l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[3]) * l[0] / (l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin
      (theta[3]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[
      1] / 0.2e1;

    J[2][4] = cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0])
      * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta
      [1]) * l[0]))) * l[1]) / 0.2e1 - sin(theta[4]) * (l[6] - l[3]) / 0.2e1;

    J[2][5] = cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(
      theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) / 0.2e1 - sin(theta[5]) * (-l[6] + l[3]) / 0.2e1;

    J[3][0] = -(cos(theta[4
      ]) * (cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[
      0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[0]) * l[0]) * pow(0.4e1 - (
      pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1)
      / 0.2e1 + (cos(theta[0]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) + (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[
      0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0
      ]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1]) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos
      (theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l
      [4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(
      l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) *
      l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) - (cos(theta[4]) * (sin(theta[
      0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin
      (theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1
      ]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1)
      + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0]
      - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(
      PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1) *
      sin(theta[4]) * (cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow
      (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4
      ] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[0]) * l[0]) * pow(
      0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1)
      , -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[0]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) + (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow
      (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(
      l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1])) / (0.1e1 + pow(cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] -
      sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] +
      sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3]), 0.2e1) *
      pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0
      ] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))
      ) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0],
      0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2])
      * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1));

    J[3][1] = -(cos(theta[4]) * cos(PI - acos(sqrt(pow(l[4] + cos(theta[0])
      * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1])
      * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l
      [0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[1]) * l[0] - 0.2e1 *
      (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[1]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[1]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0]) - (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[1]) * l[0]) /
      (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1] / (l[5] + sin(theta[4]
      ) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0
      ], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4
      ]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta
      [2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]
      ) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) - (cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)
      ) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6
      ] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[
      0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0])
      )) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4]
      + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4]
      + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0]
      - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * sin(theta[4]) * cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l
      [0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0])
      * sin(theta[1]) * l[0] - 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[1]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[1]) * l[0]
      / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) - (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0
      ], -0.2e1) * sin(theta[1]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]
      , -0.2e1))) * l[1]) / (0.1e1 + pow(cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) +
      pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] -
      cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] -
      cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) /
      (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3]), 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] +
      sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(
      theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) *
      l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(
      theta[5]) * (-l[6] + l[3]), -0.2e1));

    J[3][2] = -(-cos(theta[5]) * (cos(theta[2]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) *
      l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0
      ], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0]) * cos(theta[2]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(
      theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[2]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(
      theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) *
      l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1]) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0
      ] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin
      (theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[
      3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) -
      cos(theta[5]) * (-l[6] + l[3])) + (cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) +
      pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0]
      - cos(theta[1]) * l[0]))) * l[
      1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1
      ) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[
      0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] +
      sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1)
      * sin(theta[5]) * (cos(theta[2]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(
      theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (
      l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[2]) * l[0]) *
      pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1
      ), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[2]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) *
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow
      (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1])) / (0.1e1 + pow(cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] -
      sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0]
      + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3]), 0.2e1)
      * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l
      [0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]
      ))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0
      ], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[
      2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1));

    J[3][3] = -(-cos(theta[5]) * cos(PI - acos(sqrt(pow(l[4] + cos(theta[2])
      * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3])
      * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2
      ]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[3]) * l[0] - 0.2e1
      * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(
      sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[3]) * l[0] / (l[4] + cos(theta[2]) * l[0] -
      cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[3]) * l[0])
      / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1] / (l[5] + sin(
      theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1])
      * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(
      theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(
      theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(
      theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) + (cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos
      (theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1
      )) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[
      6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l
      [0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]
      ))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4]
      + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4]
      + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0]
      - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * sin(theta[5]) * cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l
      [0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0])
      * sin(theta[3]) * l[0] - 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(
      theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (-cos(theta[3]) * l[0
      ] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l
      [0], -0.2e1) * sin(theta[3]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[
      0], -0.2e1))) * l[1]) / (0.1e1 + pow(cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1)
      + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0]
      - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0]
      - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0])
      / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3]), 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] +
      sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(
      theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) *
      l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5])
      * (-l[6] + l[3]), -0.2e1));

    J[3][4] = -((-sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) *
      l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - cos(theta[4]) * (l[6] - l[3])) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4]
      + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0]
      - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[
      0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) -
      (cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1])
      - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) +
      pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] -
      cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta
      [0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta
      [1]) * l[0]) / (l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * (cos(theta[4]) * (sin(theta[
      0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[
      1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[
      3]))) / (0.1e1 + pow(cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta
      [0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]
      ) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3
      ]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3]), 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (
      sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0
      ], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5
      ]) * (-l[6] + l[3]), -0.2e1));

    J[3][5] = -((sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0
      ], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[
      2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + cos(theta[5]) * (-l[6] + l[3])) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] -
      sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0]
      + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) - (cos
      (theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[
      1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) -
      sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(
      sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos
      (theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]
      ) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]
      ) * l[0]) / (l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * (-cos(theta[5]) * (sin(theta
      [2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l
      [1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] +
      l[3]))) / (0.1e1 + pow(cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[
      1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3]) - cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta
      [3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3]), 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) *
      (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l
      [0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta
      [5]) * (-l[6] + l[3]), -0.2e1));

    J[4][0] = ((-sin(theta[0]) * l[0] - sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1
      ]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[
      4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[0]) * l[0]) * pow(0.4e1
      - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1)
      / 0.2e1 + (cos(theta[0]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) + (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1]) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0]
      - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0])
      / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]
      ) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) - (cos(theta[0]) * l[0] +
      cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1]
      / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI
      - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[
      0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) -
      sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta
      [3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) -
      cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * sin(theta[4]) * (cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1)
      + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) *
      l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)
      , -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[0]) * l[0] + 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1
      ]) * l[0]) * cos(theta[0]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) *
      l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[0]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) + (sin(theta
      [0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[0]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l
      [0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1])) / (0.1e1 + pow(cos(theta[0]) * l[0] + cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4
      ] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0
      ] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1], 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI
      - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5])
      * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0],
      0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5])
      * (-l[6] + l[3]), -0.2e1));

    J[4][1] = (-sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(
      theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(
      pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l
      [4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[1]) * l[0] - 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[1]) * l[0]) *
      pow(0.4e1 - (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1
      / 0.2e1) / 0.2e1 + (-cos(theta[1]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) - (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4]
      + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[1]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1] / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) *
      l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) *
      l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos
      (sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(
      theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) - (cos(theta[0]) * l
      [0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(
      pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]
      ) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta
      [2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l
      [1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] +
      l[3]), -0.2e1) * sin(theta[4]) * cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1])
      * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * (pow(pow(l[4]
      + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos
      (theta[0]) * l[0] - cos(theta[1]) * l[0]) * sin(theta[1]) * l[0] - 0.2e1 * (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * cos(theta[1]) * l[0]) * pow(0.4e1 -
      (pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1
      ) / 0.2e1 + (-cos(theta[1]) * l[0] / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]) - (sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) * pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1) * sin(theta[1]) * l[0]) / (0.1e1 + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1) * pow(l[4] +
      cos(theta[0]) * l[0] - cos(theta[1]) * l[0], -0.2e1))) * l[1]) / (0.1e1 + pow(cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4
      ] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0],
      0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2])
      * l[0] - cos(theta[3]) * l[0]))) * l[1], 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(
      theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[
      4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l
      [4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l
      [0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1));

    J[4][2] = ((sin(
      theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) /
      l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) *
      l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[2]) * l[0]
      - cos(theta[3]) * l[0]) * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[2]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(
      theta[2]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] -
      cos(theta[3]) * l[0], -0.2e1) * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos
      (theta[3]) * l[0], -0.2e1))) * l[1]) / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[
      0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta
      [0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(
      theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) + (cos(theta[0]) * l[0] + cos(PI - acos(sqrt(
      pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1]
      / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI
      - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[
      0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) -
      sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta
      [3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) -
      cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * sin(theta[5]) * (cos(theta[2]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1)
      + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) *
      l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)
      , -0.1e1 / 0.2e1) / l[1] * (-0.2e1 * (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[2]) * l[0] + 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3
      ]) * l[0]) * cos(theta[2]) * l[0]) * pow(0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) *
      l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1) / 0.2e1 + (cos(theta[2]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) + (sin(theta[
      2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[2]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[
      0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1])) / (0.1e1 + pow(cos(theta[0]) * l[0] + cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4
      ] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0
      ] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1], 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI
      - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((
      sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5])
      * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0],
      0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5])
      * (-l[6] + l[3]), -0.2e1));

    J[4][3] = (sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(
      theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[
      4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[3]) * l[0] - 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0]) * pow
      (0.4e1 - (pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1
      / 0.2e1) / 0.2e1 + (-cos(theta[3]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4]
      + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[3]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1] / (l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) *
      l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) *
      l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos
      (sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(
      theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3])) + (cos(theta[0]) * l
      [0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(
      pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0])
      * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2
      ]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1
      ] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[
      3]), -0.2e1) * sin(theta[5]) * cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) *
      l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * (pow(pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1), -0.1e1 / 0.2e1) / l[1] * (0.2e1 * (l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0]) * sin(theta[3]) * l[0] - 0.2e1 * (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * cos(theta[3]) * l[0]) * pow(0.4e1 - (
      pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) * pow(l[1], -0.2e1), -0.1e1 / 0.2e1)
      / 0.2e1 + (-cos(theta[3]) * l[0] / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]) - (sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) * pow(l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0], -0.2e1) * sin(theta[3]) * l[0]) / (0.1e1 + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1) * pow(l[4] + cos(theta
      [2]) * l[0] - cos(theta[3]) * l[0], -0.2e1))) * l[1]) / (0.1e1 + pow(cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1])
      * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) +
      pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] -
      cos(theta[3]) * l[0]))) * l[1], 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1])
      * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(
      theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(
      theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1));

    J[4][4] = -(cos(theta[0]) * l
      [0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(
      theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] +
      sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) +
      atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(
      theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) *
      l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(
      theta[5]) * (-l[6] + l[3]), -0.2e1) * (cos(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) +
      pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] -
      cos(theta[1]) * l[0]))) * l[1]) - sin(theta[4]) * (l[6] - l[3])) / (0.1e1 + pow(cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] -
      cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (
      l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] +
      cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1], 0.2e1) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI -
      acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (
      sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)
      ) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (
      -l[6] + l[3]), -0.2e1));

    J[4][5] = -(cos(theta[0]) * l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(
      theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1
      ]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] -
      sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[
      1]) * pow(l[5] + sin(theta[4]) * (sin(theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0])
      * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l
      [0]))) * l[1]) + cos(theta[4]) * (l[6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) *
      l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(
      theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1) * (-cos(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l
      [4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l
      [0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1]) + sin(theta[5]) * (-l[6] + l[3])) / (0.1e1 + pow(cos(theta[0]) *
      l[0] + cos(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1)) / l[1] / 0.2e1)
       + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1] - cos(theta[2]) * l[0] - cos(PI -
      acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l[0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1)
      + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]))) * l[1], 0.2e1) * pow(l[5] + sin(theta[4]) * (sin
      (theta[0]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0], 0.2e1) + pow(sin(theta[0]) * l[0] - sin(theta[1]) * l[0], 0.2e1
      )) / l[1] / 0.2e1) + atan((sin(theta[0]) * l[0] - sin(theta[1]) * l[0]) / (l[4] + cos(theta[0]) * l[0] - cos(theta[1]) * l[0]))) * l[1]) + cos(theta[4]) * (l[
      6] - l[3]) - sin(theta[5]) * (sin(theta[2]) * l[0] + sin(PI - acos(sqrt(pow(l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0], 0.2e1) + pow(sin(theta[2]) * l
      [0] - sin(theta[3]) * l[0], 0.2e1)) / l[1] / 0.2e1) + atan((sin(theta[2]) * l[0] - sin(theta[3]) * l[0]) / (l[4] + cos(theta[2]) * l[0] - cos(theta[3]) * l[0]
      ))) * l[1]) - cos(theta[5]) * (-l[6] + l[3]), -0.2e1));

    tau[0] = J[0][0]*F[0] + J[1][0]*F[1] + J[2][0]*F[2] + J[3][0]*F[3] + J[4][0]*F[4];
    tau[1] = J[0][1]*F[0] + J[1][1]*F[1] + J[2][1]*F[2] + J[3][1]*F[3] + J[4][1]*F[4];
    tau[2] = J[0][2]*F[0] + J[1][2]*F[1] + J[2][2]*F[2] + J[3][2]*F[3] + J[4][2]*F[4];
    tau[3] = J[0][3]*F[0] + J[1][3]*F[1] + J[2][3]*F[2] + J[3][3]*F[3] + J[4][3]*F[4];
    tau[4] = J[0][4]*F[0] + J[1][4]*F[1] + J[2][4]*F[2] + J[3][4]*F[3] + J[4][4]*F[4];
    tau[5] = J[0][5]*F[0] + J[1][5]*F[1] + J[2][5]*F[2] + J[3][5]*F[3] + J[4][5]*F[4];
}
