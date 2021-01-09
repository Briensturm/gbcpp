#pragma once

class PixelProcessingUnitState
{
    public:
        protected PixelProcessingUnitState(PPUCtxPtr context, PPUSmPtr stateMachine)
        {
            _context = context;
            _stateMachine = stateMachine;
        }

        void AdvanceMachineCycle();
        int GetModeNumber();
        void Initialize(int clocks);

    protected:
        protected PPUSmPtr _stateMachine;
        protected PPUCtxPtr _context;
};
