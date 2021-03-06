# PlayStation Vita Drop Game
A game about keeping the green ball on the paddle while random objects destabilize it. This game was developed for the PlayStation Vita using the GEF framework in C++ using a custom made component based game object system. Created for a second year module in university.
![GIF of Gameplay](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/GIF.gif)

# Game Structure
The game is structured using a component based game object system. Each game object has components. Each of the scenes are responsible for adding game objects, and unless marked otherwise they are destroyed when the scene changes. This was modelled heavily after how Unity works.

As much modern C++ was used as possible, however the PlayStation Vita has limited support for C++11 which excludes smart pointers.

![Main Menu Screen](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/MainMenuScreen.jpg)

# Running
[Download Here](https://github.com/giodestone/ps-vita-drop-game/releases/tag/1.0.0)

PlayStation 4 controller required. Uses the left analogue stick and RZ.

# Images
![Screenshot of Gameplay 1](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/Image1.jpg)
![Screenshot of Gameplay 2](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/Image2.jpg)
![Screenshot of Gameplay 3](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/Image3.jpg)

# License
Contains Box2D (BSD License).
