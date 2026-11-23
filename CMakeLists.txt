cmake_minimum_required(VERSION 3.22)
project(BudotsPHSynth VERSION 1.0.0)

# Set JUCE_DIR to your local JUCE checkout, or pass -DJUCE_DIR=...
if(NOT DEFINED JUCE_DIR)
    message(FATAL_ERROR "Set JUCE_DIR to your JUCE folder, e.g. -DJUCE_DIR=C:/JUCE")
endif()
add_subdirectory(${JUCE_DIR} JUCE)

juce_add_plugin(BudotsPHSynth
    COMPANY_NAME "Budots PH Audio"
    BUNDLE_ID "ph.budots.audio.synth"
    PLUGIN_MANUFACTURER_CODE BdPH
    PLUGIN_CODE BpS1
    FORMATS VST3 Standalone
    PRODUCT_NAME "Budots PH Synth"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD TRUE
)

juce_generate_juce_header(BudotsPHSynth)

target_sources(BudotsPHSynth PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_compile_features(BudotsPHSynth PRIVATE cxx_std_17)
target_compile_definitions(BudotsPHSynth PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)
target_link_libraries(BudotsPHSynth PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
