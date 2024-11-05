## FreezeFrame
**Class Name:** UGFE_Time_FreezeFrame \
**Effect Type:** Time \
**Description:** Freezes the game for a short period of time. Can quickly create a slow-motion effect. \
**Configuration:**
- `MinimumTimeDilation`: `float`
	The time dilation value to apply during the freeze-frame effect.

## TimeFollow
**Class Name:** UGFE_Time_TimeFollow \
**Effect Type:** Time \
**Description:** Interpolates the global time dilation value over time. Can be used to create a smooth transition between time dilation values. This effect is potentially useful for creating some kind of time manipulation effect. \
**Configuration:**
- `StartTimeDilation`: `float`
	Time dilation coefficients for interpolated starting points
- `EndTimeDilation`: `float`
	Time dilation coefficients for interpolated ending points
- `bForceEndTimeDilationWhenInterrupted`: `bool`
	Force time dilation to EndTimeDilation when interrupted

