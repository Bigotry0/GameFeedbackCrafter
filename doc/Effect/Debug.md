## PaintString
**Class Name:** UGFE_Debug_PaintString
**Effect Type:** Debug
**Description:** This effect allows for the painting of debug strings to screen.
**Configuration:** 
- `Text`: `FString`
	The text to be displayed on screen.
- `TextDuration`: `float`
	The duration for which the text will be displayed on screen.
- `Color`: `FColor`
	The color of the text to be displayed on screen.
- `bUseKey`: `bool`
	Whether to specify the Key of the printed text
- `Key`: `FName`
	The key used to identify the printed text.
- `Timing`: `EGFE_Debug_PaintString_Timing`
	Determines when the text should be painted on the screen.
	**`EGFE_Debug_PaintString_Timing`:** {OnInit,  OnPlay,  OnPause,  OnResume,  OnStop,  OnTick}
- `bShowInterrupted`: `bool`
	Whether to show the text when the effect is interrupted
**Showcase:** 