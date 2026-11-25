#pragma once

// Makes vertical mouse camera sensitivity match horizontal.
//
// The camera controller converts rotation input into angular speed per axis using two values of the
// camera's global config (PipelineCameraGlobalConfig, 7.2):
//     DELTA_TO_ANCHOR_ANGULAR_POLAR_RATIO      (horizontal) = 150
//     DELTA_TO_ANCHOR_ANGULAR_ELEVATION_RATIO  (vertical)   = 34      -> vertical is ~4.4x slower
// This is a plain data write (no code is modified): ELEVATION is set to POLAR * percent / 100 while
// enabled and the current input device is not a controller, and the game's value is restored otherwise.
// 100% = vertical matches horizontal in degrees; the game's own value is ~23%.
namespace VerticalSensitivity
{
	// Call periodically. Does nothing until first enabled. `percent` is clamped to 10..200.
	void Tick(bool enable, int percent);
}
