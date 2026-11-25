#pragma once

// Disables the game's mouse camera smoothing.
//
// The camera manager's mouse path (7.2) does, per frame:
//     raw = mouseDelta * sensitivity;
//     if (smooth) smoothed = lerp(smoothed, raw, clamp01(deltaTime * 15));   // ~67ms time constant
//     else        smoothed = raw;
//     Camera.Rotate(smoothed);
// We turn the `je` that selects the smoothed branch into an unconditional `jmp` to the game's own
// unsmoothed branch (2 bytes, same jump target). Only the keyboard+mouse path goes through it.
namespace MouseSmoothing
{
	// Call periodically. Patches or restores when `disable` changes; does nothing until first enabled.
	void Tick(bool disable);
}
