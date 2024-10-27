# GameFeedbackCrafter

GameFeedbackCrafter是一个模块化的效果制作插件，它使你能够快速迭代和处理复杂的游戏表现。

GameFeedbackCrafter将一个复杂游戏效果抽象为一个**GameFeedback**，一个GameFeedback由多个**GameFeedbackEffect**组成。GameFeedback不提供任何效果，它仅负责组织和维护GameFeedbackEffect，而实际的效果逻辑则是在GameFeedbackEffect中实现。这使我们能够将大量的游戏效果拆分成一个个GameFeedbackEffect模块，并在GameFeedback中根据实际需求组合他们，以此快速实现和迭代复杂的游戏效果。具体核心库介绍详见文档[GameFeedbackCore](doc/GameFeedbackCore-zh.md)。

插件将内置一个自带的效果模块库，它将随着项目的发展不断增大。具体的模块文档详见[目录](doc/GameFeedbackEffectIndex.md)。

项目仍处于研发阶段，不过核心框架现已完成，如果您想对插件做出贡献，欢迎您的PR！我将不胜感激！

此外，目前插件的编辑器体验较为原始，我将优先完成插件的逻辑功能。
 