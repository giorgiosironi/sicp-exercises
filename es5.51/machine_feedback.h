#ifndef MACHINE_FEEDBACK_H
#define MACHINE_FEEDBACK_H

/**
 * Class extracted to avoid creating a mutual dependency between Instruction
 * and Machine
 */
class MachineFeedback {

    public:
        void nextInstruction();
        void forceInstruction(int instructionIndex);
    protected:
        int pc;
};

#endif
