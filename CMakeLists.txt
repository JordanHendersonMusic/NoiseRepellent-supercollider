####################################################################################################
# CMakeLists file for NoiseRepellent
# Generated by Jordan Henderson
# 2022-07-19
####################################################################################################

####################################################################################################
# basic project config
cmake_minimum_required(VERSION 3.12)
set(project_name "NoiseRepellent")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 17)

find_package(FFTW REQUIRED)

####################################################################################################
# load modules
include(SuperColliderServerPlugin RESULT_VARIABLE server_plugin_found)
if (NOT server_plugin_found)
    message(FATAL_ERROR "Could not find server plugin functions module")
endif ()

include(SuperColliderCompilerConfig RESULT_VARIABLE compiler_config_found)
if (NOT compiler_config_found)
    message(FATAL_ERROR "Could not find compiler config module")
endif ()

# Windows - puts redistributable DLLs in install directory
include(InstallRequiredSystemLibraries)

sc_check_sc_path("${SC_PATH}")
message(STATUS "Found SuperCollider: ${SC_PATH}")
set(SC_PATH "${SC_PATH}" CACHE PATH
        "Path to SuperCollider source. Relative paths are treated as relative to this script" FORCE)

include("${SC_PATH}/SCVersion.txt")
message(STATUS "Building plugins for SuperCollider version: ${SC_VERSION}")

# set project here to avoid SCVersion.txt clobbering our version info
project(${project_name})
sc_do_initial_compiler_config() # do after setting project so compiler ID is available

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR NOT CMAKE_INSTALL_PREFIX)
    message(WARNING "No install prefix provided, defaulting to $BUILD_DIR/install")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install prefix" FORCE)
endif ()

message(STATUS "Install directory set to: ${CMAKE_INSTALL_PREFIX}")

####################################################################################################
# options
option(SUPERNOVA "Build plugins for supernova" ON)
option(SCSYNTH "Build plugins for scsynth" ON)
option(NATIVE "Optimize for native architecture" OFF)
option(STRICT "Use strict warning flags" OFF)
option(NOVA_SIMD "Build plugins with nova-simd support." ON)

####################################################################################################
# include libraries

if (NOVA_SIMD)
    add_definitions(-DNOVA_SIMD)
    include_directories(${SC_PATH}/external_libraries/nova-simd)
endif ()

####################################################################################################
# Begin target NoiseRepellent


set(LibSpecBleachFiles
        plugins/NoiseRepellent/libspecbleach/include/specbleach_adenoiser.h
        plugins/NoiseRepellent/libspecbleach/include/specbleach_denoiser.h
        plugins/NoiseRepellent/libspecbleach/src/processors/specbleach_adenoiser.c
        plugins/NoiseRepellent/libspecbleach/src/processors/specbleach_denoiser.c
        plugins/NoiseRepellent/libspecbleach/src/processors/denoiser/spectral_denoiser.c
        plugins/NoiseRepellent/libspecbleach/src/processors/denoiser/spectral_denoiser.h
        plugins/NoiseRepellent/libspecbleach/src/processors/adaptivedenoiser/adaptive_denoiser.c
        plugins/NoiseRepellent/libspecbleach/src/processors/adaptivedenoiser/adaptive_denoiser.h
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/general_utils.c
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/spectral_utils.h
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/spectral_features.h
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/denoise_mixer.c
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/spectral_features.c
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/spectral_trailing_buffer.c
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/spectral_utils.c
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/spectral_trailing_buffer.h
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/general_utils.h
        plugins/NoiseRepellent/libspecbleach/src/shared/utils/denoise_mixer.h
        plugins/NoiseRepellent/libspecbleach/src/shared/gain_estimation/gain_estimators.c
        plugins/NoiseRepellent/libspecbleach/src/shared/gain_estimation/gain_estimators.h
        plugins/NoiseRepellent/libspecbleach/src/shared/configurations.h
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/critical_bands.c
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/masking_estimator.h
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/transient_detector.h
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/spectral_smoother.h
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/absolute_hearing_thresholds.h
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/transient_detector.c
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/noise_scaling_criterias.c
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/masking_estimator.c
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/critical_bands.h
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/spectral_smoother.c
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/absolute_hearing_thresholds.c
        plugins/NoiseRepellent/libspecbleach/src/shared/pre_estimation/noise_scaling_criterias.h
        plugins/NoiseRepellent/libspecbleach/src/shared/noise_estimation/noise_estimator.c
        plugins/NoiseRepellent/libspecbleach/src/shared/noise_estimation/noise_estimator.h
        plugins/NoiseRepellent/libspecbleach/src/shared/noise_estimation/adaptive_noise_estimator.c
        plugins/NoiseRepellent/libspecbleach/src/shared/noise_estimation/noise_profile.h
        plugins/NoiseRepellent/libspecbleach/src/shared/noise_estimation/noise_profile.c
        plugins/NoiseRepellent/libspecbleach/src/shared/noise_estimation/adaptive_noise_estimator.h
        plugins/NoiseRepellent/libspecbleach/src/shared/post_estimation/spectral_whitening.h
        plugins/NoiseRepellent/libspecbleach/src/shared/post_estimation/spectral_whitening.c
        plugins/NoiseRepellent/libspecbleach/src/shared/post_estimation/postfilter.c
        plugins/NoiseRepellent/libspecbleach/src/shared/post_estimation/postfilter.h
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/stft_windows.h
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/stft_processor.h
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/stft_windows.c
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/stft_buffer.c
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/fft_transform.h
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/stft_buffer.h
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/stft_processor.c
        plugins/NoiseRepellent/libspecbleach/src/shared/stft/fft_transform.c
        plugins/NoiseRepellent/libspecbleach/src/interfaces/spectral_processor.h
        )

set(NoiseRepellent_cpp_files
        plugins/NoiseRepellent/NoiseRepellent.hpp
        plugins/NoiseRepellent/NoiseRepellent.cpp
        ${LibSpecBleachFiles}
        )
set(NoiseRepellent_sc_files
        plugins/NoiseRepellent/NoiseRepellent.sc
        )
set(NoiseRepellent_schelp_files
        plugins/NoiseRepellent/NoiseRepellent.schelp
        plugins/NoiseRepellent/NRLearnType.schelp
        plugins/NoiseRepellent/NRAverage.schelp
        plugins/NoiseRepellent/NRMax.schelp
        plugins/NoiseRepellent/NRMedian.schelp
        )


sc_add_server_plugin(
        "NoiseRepellent/NoiseRepellent" # desination directory
        "NoiseRepellent" # target name
        "${NoiseRepellent_cpp_files}"
        "${NoiseRepellent_sc_files}"
        "${NoiseRepellent_schelp_files}"
)


# End target NoiseRepellent
####################################################################################################

####################################################################################################
# END PLUGIN TARGET DEFINITION
####################################################################################################

message(STATUS "Generating plugin targets done")