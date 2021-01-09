#pragma once

#include "gbcpp.hpp"

#include "ppu_state.hpp"

class HBlankState : PixelProcessingUnitState
{
    public:
        HBlankState(PixelProcessingUnitContext context, PPUStateMachine stateMachine)
            : PixelProcessingUnitState(context, stateMachine) {}

        void AdvanceMachineCycle()
        {
            _dotCounter += 4;

            if(_dotCounter == 208)
            {
                _context.CurrentLine++;

                if (_context.CurrentLine == 144)
                {
                    _stateMachine.TransitionTo<VBlankState>();
                    _context.RequestVBlankInterrupt();
                }
                else
                    _stateMachine.TransitionTo<OamScanState>();      
            }                
        }

        int GetModeNumber()
        {
            return Common.Constants.Video.HBlankModeNo;
        }

        void Initialize(int clocks)
        {
            _dotCounter = 0;
        }

    private:
        int _dotCounter;
};
