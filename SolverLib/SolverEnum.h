#ifndef __SOLVERENUM_H
#define __SOLVERENUM_H

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
        enum RegularizationType
        {
            RegularizationType_L1,
            RegularizationType_L2
        };

        enum SnapshotFormat
        {
            HDF5,
            BINARYPROTO
        };

        enum SolverMode
        {
            CPU,
            GPU
	};

        enum SolverType
        {
            SGD,
            NESTEROV,
            ADAGRAD,
            RMSPROP,
            ADADELTA,
            ADAM
        };

        enum LrPolicy
        {
            LRPOLICY_FIXED,
            LRPOLICY_STEP,
            LRPOLICY_EXP,
            LRPOLICY_INV,
            LRPOLICY_MULTISTEP,
            LRPOLICY_POLY,
            LRPOLICY_SIGMOID
        };
}
#endif
