#pragma once
#include <string>

class Conductor
{
    public:
        float swagTimer = 0.0f;

        float bpm = 100.0f;
        int stepsPerBeat = 4;
        int stepsPerMeasure = 16;
        
        float curStepFloat = 0.0f;
        
        int curStep = 0;
        int curBeat = 0;
        int curMeasure = 0;

        int prevcurStep = -1;
        int prevcurBeat = -1;
        int prevcurMeasure = -1;
        
        void setBPM(float newbpm);
        void changeBPM(float newbpm);

        void onStepHit(int dacurStep);
        void onBeatHit(int dacurBeat);
        void onMeasureHit(int dacurMeasure);

        void updateBeats(float elapsed);
};

extern Conductor conductor;