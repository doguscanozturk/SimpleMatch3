# Simple Match-3

### Developer's Notes
* My goals for this project were understanding C++ and Unreal Engine better, as well as measuring how may I transform my 5 years of experience in C# and Unity.
* Worked on this project in my spare time for nearly 2 months.
* Worked with Unreal Engine 4.27.1. I mainly preferred developing systems with C++ to facilitate traceability but I also took advantage of the *Blueprint Visual Scripting* at some parts.
* Took care of making the gameplay as robust as possible. But 100% of every edge case may possibly have not been covered yet.
* Aimed to write everything appropriate to the *Clean Code* principles. Considered *SoC* and *SOLID* principles while I'm designing the systems and the architecture of the code.
* Game is playable in Match3Gameplay map. Script execution starts from the BeginPlay function of the Match3Initializer script.
* Systems that need to be created once for a session are getting created in the SimpleMatch3GameInstance class.
* MatchIdentifier system designed to support adding new shapes or updating current ones easily.
* Only used third-party library is *boolinq*.

### About the game
* Your objective is to bring 3 or more same colored and consecutive pieces together to match them.
* There are some special shapes of piece combinations that can be accepted as a match. For example, you can match L or T-shaped 5 pieces.
* When all objectives at the target panel get finished you successfully complete that level.

### Gameplay Sample
