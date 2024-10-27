# GameFeedbackCrafter
> Language: [Chinese](README-zh)

GameFeedbackCrafter is a modular effect creation plugin that enables you to quickly iterate and work with complex game performance.

GameFeedbackCrafter abstracts a complex game effect into a **GameFeedback**, which consists of multiple **GameFeedbackEffects** GameFeedback doesn't provide any effects, it only organizes and maintains the GameFeedbackEffect, while the actual effect logic is implemented in GameFeedbackEffect. This allows us to split a large number of game effects into individual GameFeedbackEffect modules, and combine them in GameFeedback according to actual needs, so as to quickly realize and iterate complex game effects. See [GameFeedbackCore](doc/GameFeedbackCore) for a detailed description of the core library.

The plugin will come with a built-in library of effect modules that will grow as the project develops. Specific module documentation is detailed in [catalog](doc/GameFeedbackEffectIndex).

The project is still in the development stage, but the core framework is now complete, so if you would like to contribute to the plugin, I would appreciate your PR!

Additionally, the plugin's editor experience is currently rather primitive, and I will prioritize completing the plugin's logic features.