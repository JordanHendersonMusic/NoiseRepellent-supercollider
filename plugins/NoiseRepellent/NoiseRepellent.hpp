// PluginNoiseRepellent.hpp
// Jordan Henderson (j.henderson.music@outlook.com)

// Using this amazing library! https://github.com/lucianodato/libspecbleach

#pragma once

#include "SC_PlugIn.hpp"

#include "libspecbleach/include/specbleach_denoiser.h"

namespace NoiseRepellent {

struct SpecBleach {
public:
	explicit SpecBleach(uint32 sample_rate);
	~SpecBleach();
	void set_params(SpectralBleachParameters p);
	void process(int num_of_samples, const float* input, float* output);
private:
	SpectralBleachHandle handle;
};

class NoiseRepellent : public SCUnit {
public:
	NoiseRepellent();

private:
	void next(int nSamples);
	SpecBleach bleach;
	enum Args : int {
		LearnNoise = 1,
		ResidualListen = 2,
		ReductionAmount = 3,
		SmoothingFactor = 4,
		TransientProtection = 5,
		WhiteningFactor = 6,
		NoiseRescale = 7
	};
};

} // namespace NoiseRepellent
