# PlayStation Vita Drop Game
![GIF of Gameplay](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/GIF.gif)
A game about keeping the green ball on the paddle while random objects destabilize it. This game was developed for the PlayStation Vita using the GEF framework in C++. It uses a component game object system.

# Game Structure
The game is structured using a component based game object system. Each game object has components. Each of the scenes are responsible for adding game objects, and unless marked otherwise they are destroyed when the scene changes. This was modelled heavily after how Unity works.

As much modern C++ was used as possible, however the PlayStation Vita has limited support for C++11 which excludes smart pointers.

![Main Menu Screen](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/MainMenuScreen.jpg)

# Running
[Download Here](LINK)

PlayStation 4 controller required. Uses the left analogue stick and RZ.

# Images
![Screenshot of Gameplay 1](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/Image1.jpg)
![Screenshot of Gameplay 2](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/Image2.jpg)
![Screenshot of Gameplay 3](https://raw.githubusercontent.com/giodestone/ps-vita-drop-game/master/Images/Image3.jpg)

# License
Contains Box2D (BSD License).