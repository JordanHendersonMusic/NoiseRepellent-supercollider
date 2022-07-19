// PluginNoiseRepellent.cpp
// Jordan Henderson (j.henderson.music@outlook.com)

#include "SC_PlugIn.hpp"
#include "NoiseRepellent.hpp"

static InterfaceTable* ft;

namespace NoiseRepellent {


SpecBleach::SpecBleach(uint32 sample_rate) : handle(specbleach_initialize(sample_rate)){}

SpecBleach::~SpecBleach() { specbleach_free(handle); }

void SpecBleach::set_params(SpectralBleachParameters p) {
	specbleach_load_parameters(handle, p);
}
void SpecBleach::process(int num_of_samples, const float* input, float* output) {
	specbleach_process(handle, num_of_samples, input, output);
}


NoiseRepellent::NoiseRepellent() : bleach(static_cast<uint32>(sampleRate())) {
	mCalcFunc = make_calc_function<NoiseRepellent, &NoiseRepellent::next>();
	next(1);
}


void NoiseRepellent::next(int nSamples) {
	const float* input = in(0);

	const float* learn_noise_i = in(LearnNoise);
	const float* residual_listen_i = in(ResidualListen);
	const float* reduction_amount_i = in(ReductionAmount);
	const float* smoothing_factor_i = in(SmoothingFactor);
	const float* transient_protection_i = in(TransientProtection);
	const float* whitening_factor_i = in(WhiteningFactor);
	const float* noise_rescale_i = in(NoiseRescale);


	const int learn_noise = std::max(std::min(3, static_cast<int>(std::round(learn_noise_i[0]))), 0);
	const bool residual_listen = residual_listen_i[0] > 0.5f;
	const bool transient_protection = transient_protection_i[0] > 0.5f;

	bleach.set_params(
			SpectralBleachParameters{.learn_noise=learn_noise,
					.residual_listen=residual_listen,
					.reduction_amount=reduction_amount_i[0],
					.smoothing_factor=smoothing_factor_i[0],
					.transient_protection=transient_protection,
					.whitening_factor=whitening_factor_i[0],
					.noise_rescale=noise_rescale_i[0]}
	);

	float* outbuf = out(0);

	bleach.process(nSamples, input, outbuf);
}

} // namespace NoiseRepellent

PluginLoad(NoiseRepellentUGens) {
	ft = inTable;
	registerUnit<NoiseRepellent::NoiseRepellent>(ft, "NoiseRepellent", false);
}
