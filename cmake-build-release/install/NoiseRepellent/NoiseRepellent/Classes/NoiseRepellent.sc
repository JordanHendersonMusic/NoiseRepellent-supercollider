NRLearnType {
    var <>type, <>isLearning;
    *new{^super.new}
    init{ 
        |t, l|
        type = t; 
        isLearning = l;
    }
}
NRAverage : NRLearnType {
    *new{ |isLearning|
        ^super.new.init(1, isLearning)
    }
}
NRMedian : NRLearnType {
    *new{ |isLearning|
        ^super.new.init(2, isLearning)
    }
}
NRMax : NRLearnType {     
    *new{ |isLearning|
        ^super.new.init(3, isLearning)
    }
}

NoiseRepellent : UGen {
    *ar {
        arg input,
        learner,
        reductionAmount=40,
        smoothingFactor=0,
        noiseRescale=0.2,
        isTransientProtected=1,
        whiteningFactor=0,
        invert=0;

        if(input.isValidUGenInput.not, 
            {^format("NoiseRepellent: input must be valid UGen input, got %\n", input).error});

        if(learner.isKindOf(NRLearnType).not
            {^format("NoiseRepellent: learner must be NRAverage, NRMedian, or NRMax, got %: %\n", learner, learner.class).error});

        if(invert.isValidUGenInput.not, 
            {^format("NoiseRepellent: invert must be valid UGen input, got %\n", invert).error});
        if(reductionAmount.isValidUGenInput.not, 
            {^format("NoiseRepellent: reductionAmount must be valid UGen input, got %\n", reductionAmount).error});
        if(smoothingFactor.isValidUGenInput.not, 
            {^format("NoiseRepellent: smoothingFactor must be valid UGen input, got %\n", smoothingFactor).error});
        if(isTransientProtected.isValidUGenInput.not, 
            {^format("NoiseRepellent: isTransientProtected must be valid UGen input, got %\n", isTransientProtected).error});
        if(whiteningFactor.isValidUGenInput.not, 
            {^format("NoiseRepellent: whiteningFactor must be valid UGen input, got %\n", whiteningFactor).error});
        if(noiseRescale.isValidUGenInput.not, 
            {^format("NoiseRepellent: noiseRescale must be valid UGen input, got %\n", noiseRescale).error});

        ^this.multiNew('audio',
            input,
            (learner.isLearning > 0.5) * learner.type,
            invert,
            reductionAmount.clip(0, 40),
            smoothingFactor.linlin(0,1, 0, 100),
            isTransientProtected,
            whiteningFactor.linlin(0,1,0,100),
            noiseRescale.linlin(-1,1, -12, 12)
        )

    }
}
