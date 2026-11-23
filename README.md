# Budots PH Synth — VST3 / Windows 64-bit

A JUCE-based, original subtractive-style synthesizer starter project for FL Studio. It creates sound in real time from oscillators (sine, saw, square, triangle and a bright harmonic/buzz wave), with sub oscillator, detune, wobble, drive, a tone control, ADSR envelope and reverb.

## Included
- VST3 instrument target and optional standalone app
- 12-voice polyphonic MIDI synth engine
- Custom dark/neon interface
- Four starting presets: Budots Saw Lead, Rave Square, Zumba Pluck, Festival Brass
- Host automation/state save through JUCE AudioProcessorValueTreeState

## Important
This is a source project, not a precompiled `.vst3` binary. You must build it on Windows using JUCE and Visual Studio. The plugin uses synthesized waveforms; it does not include sampled copyrighted songs or commercial sound libraries. The included presets are starting points and can be refined by ear.

## Requirements
1. Windows 10/11, 64-bit
2. Visual Studio 2022 with **Desktop development with C++** and the Windows 10/11 SDK
3. CMake 3.22+
4. JUCE 7 or JUCE 8 source checkout (https://juce.com/)
5. FL Studio 64-bit

## Build in PowerShell
Assuming JUCE is at `C:\JUCE` and this project is extracted to `C:\BudotsPHSynth`:

```powershell
cd C:\BudotsPHSynth
cmake -S . -B build -DJUCE_DIR=C:\JUCE -A x64
cmake --build build --config Release
```

The CMake target requests VST3 and Standalone. JUCE's post-build copy option may place the VST3 in the standard user VST3 folder. If not, locate `Budots PH Synth.vst3` under `build\BudotsPHSynth_artefacts\Release\VST3\` and copy it to:

`C:\Program Files\Common Files\VST3\`

Restart FL Studio, open **Options > Manage plugins**, verify the VST3 search path includes the folder, then click **Find installed plugins**. Load **Budots PH Synth** from the instrument/plugin list and play it with a MIDI keyboard or piano roll.

## Quick sound design
- **Classic Budots lead:** Saw, Tone 0.9, Drive 0.25, Detune 0.015, short Attack and Release.
- **Rave stab:** Square, Drive 0.4, Sub 0.25, short Decay, Sustain 0.5.
- **Zumba pluck:** Triangle, short Attack, Decay 0.2–0.3 s, Sustain near zero.
- **Festival brass:** Buzz, moderate Detune, longer Attack and Release.

Try notes around C4–C6, use short rhythmic MIDI patterns, and layer a separate kick/snare/hat drum pattern in FL Studio. The plugin currently generates pitched synth tones only; it is not a drum machine or sampler.

## Project notes / limitations
- The interface is a functional first version. Slider labels are accessible through the control names; layout can be polished further.
- This starter engine is intentionally lightweight. It does not yet include wavetable import, unison stacks, preset file browser, arpeggiator, MIDI learn, sidechain, or sample playback.
- For a commercial release, test CPU use, aliasing, automation, mono/stereo behavior and host compatibility thoroughly. Consider adding oversampling and band-limited oscillators before distribution.
- JUCE is distributed under its own license. Review JUCE licensing before distributing a product.

## Easier option: build a Windows installer artifact with GitHub Actions
This repository includes `.github/workflows/build-windows-vst3.yml`. If you upload the project to a GitHub repository, open **Actions**, select **Build Windows VST3**, and click **Run workflow**. When the run finishes, download the artifact named `Budots-PH-Synth-Windows-x64-VST3` from the run's **Artifacts** section. Extract the `.vst3` bundle and copy it to `C:\Program Files\Common Files\VST3\`, then rescan plugins in FL Studio.

This automated build still requires you to run the GitHub workflow; the ZIP itself does not contain a compiled Windows binary.
