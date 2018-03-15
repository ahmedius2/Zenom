#ifndef HAPTICWAND_H
#define HAPTICWAND_H

#include "hil.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define NUM_JOINTS  (6)			/* number of joints */
#define NUM_WORLD   (5)	        /* number of world coordinates */
#define NUM_DIGITAL_OUTPUT  (6) /* number of digital output channels */


/**
 *
 * HapticWand class is designed to control Quanser's 5DOF Haptic Wand. The joint coordinates
 * are read from encoder channels 0-5. Analog output channels 0-5 are used to drive the motors.
 *
 */
namespace Hardware
{
    class HAPTICWANDSHARED_EXPORT HapticWand : public HIL
    {
    public:
        HapticWand();

        /**
         * Opens the specified card of the given type. Configures digital I/O lines as outputs.
         *
         * @param cardType          A string identifying the type of card.
         * @param cardIdentifier    An integer identifying the particular
         *                          board among all the boards of the same type.
         */
        virtual void open(const char* cardType = "Q80", const int cardIdentifier = 0);

        /**
         * Enable a motor amplifiers.
         */
        void enableWand();

        /**
         * Disable a motor amplifiers.
         */
        void disableWand();

        /**
         * Calibrate the haptic wand.
         */
        void calibrateWand();

        /**
         * Resets the encoders to zero.
         */
        void resetEncoders();

        /**
         * Reads from encoder channels 0-5.
         * The size of the counts array must be at least 6.
         *
         * @param counts    The count values read from the encoder inputs.
         */
        void readEncoders( int* counts );

        /**
         * Writes user defined voltage values to analog output channels 0-5.
         * The size of the counts array must be at least 6.
         *
         * @param voltages  The voltage values to write to the analog outputs.
         */
        void writeAnalogs( const double* voltages );

        /**
         * Converts encoder counts from the Haptic 5-DOF Wand into joint angles in radians.
         * The parameter jointAngles are output as a 6-vector in order of the joints.
         *
         * @param jointAngles (Output)  The joint angles in radians for the six joints.
         */
        void jointAngles( double* jointAngles );

        /**
         * Computes the end-effector position and orientation.
         * The parameter worldCoordinates are output. The first three elements of
         * the worldCoordinates denote the x, y and z position of the end-effector
         * in meters and the last two elements denote its orientation
         * (roll and pitch ) in radians.
         *
         * @param theta                     The joint angles in radians for the six joints.
         * @param worldCoordinates (Output) The position and orientation of the robot
         *                                  end-effector as a 5-vector: X, Y and Z coordinates
         *                                  in meters, yaw and roll in radians.
         */
        void forwardKinematics( double* theta, double* worldCoordinates );

        /**
         * Converts cartesian end-effector forces to joint torques for the Quanser Haptic 5-DOF Wand.
         *
         * @param period        The period of the controller.
         * @param joint_angles  The joint angles in radians.
         * @param world_forces  The forces and torques in Cartesian coordinates with which to drive
         *                      the Haptic 5-DOF Wand end-effector. The input is a 5-vector, with the
         *                      first three elements being the X, Y and Z forces in N and the last two
         *                      elements being the yaw and roll torques in N-m.
         */
        void generateForces( double period, const double joint_angles[], const double world_forces[] );

        /**
         * The first sample when enableWand() is called. This is useful to set a
         * relative setpoint when doing a position control.
         *
         * @return The first sample when enableWand().
         */
        inline const double* firstSample() { return mFirstSample; }

    private:

        /**
         * Link lengths of the haptic wand links in meters
         */
        static const double l[7];

        /**
         * Analog output channels driving the haptic wand motors
         */
        static const unsigned int analogChannels[6];

        /**
         * Encoder input channels for the haptic wand joint encoders
         */
        static const unsigned int encoderChannels[6];

        /**
         * Digital output channels driving the amplifier enable lines
         */
        static const unsigned int digitalOutputChannels[6];


        struct limiter_state
        {
            double mean;
            double time;
            int    count;
            int    state;
        };

        struct limiter_state current_limiters[NUM_JOINTS];

        /*
            Limit the motor currents such that the thermal rating for the motors is not exceeded
            while continuing to provide the peak torque when necessary.
        */
        void limit_currents(double dt, double motor_currents[NUM_JOINTS]);

        /*
            Determine the motor currents in amps needed to produce the specified joint torques in N-m.
        */
        void joint_torques_to_motor_currents(const double joint_torques[NUM_JOINTS], double motor_currents[NUM_JOINTS]);

        /*
            Determine the voltages with which we need to drive the current amplifiers
            to get the motor currents desired.
        */
        void motor_currents_to_output_voltages(const double motor_currents[NUM_JOINTS], double voltages[NUM_JOINTS]);

        /*
            Compute the motor torques, tau, from the end-effector generalized forces, F. Since this conversion
            is configuration-dependent, the joint tangles, theta, are required.
        */
        void inverse_force_kinematics(const double theta[NUM_JOINTS], const double F[NUM_WORLD], double tau[NUM_JOINTS]);

        /*
            The first sample when enableWand() is called.
        */
        double mFirstSample[5];
    };
}

#endif // HAPTICWAND_H
