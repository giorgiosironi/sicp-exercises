#include "../src/machine_feedback.h"

class MockMachineFeedback : public MachineFeedback {
    public:
        virtual int get_pc();
};
