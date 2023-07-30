Jary Chen

*** 2D AIM TRAINER SFML GAME ***

-INTRODUCTION
Welcome to this professionally developed game created with the assistance of the SFML framework. 
The project originated from an exciting idea that I envisioned sharing and enjoying with friends. 
Aspiring to contribute to the broader gaming community, I hope this game will be of value to others in the future. 
Take a sneak peek here: 
->SneakPeek:https://imgur.com/a/KteZ42X

-HOW TO ACTUALLY USE IT
First and foremost, please note that this program is designed specifically for 
Visual Studio 2022, not Visual Studio Code, is a distinction that often confuses my friends.
To access Visual Studio 2022, you can download it from the official Microsoft website: 
->https://visualstudio.microsoft.com/vs/

Additionally, you will need to download the SFML library, 
a critical component of this project, from the following link: SFML Download.
->https://www.sfml-dev.org/download/sfml/2.6.0/

To integrate the SFML library with the Visual Studio project, 
please refer to this helpful tutorial: 
->https://www.youtube.com/watch?v=lFzpkvrscs4

-HOW TO CUSTOMIZE
The game's visual aspects are customizable, allowing you to personalize your gaming experience. 
The required resources, including backgrounds, targets, fonts, and more, can be found in the
dedicated folder on my GitHub:
->https://github.com/CJary/Projects/tree/main/Personal%20Projects/Aim%20Trainer

To incorporate your downloaded resources into the game, access specific functions
in the Game.cpp files, such as initEnemies, initFonts, and the Game Constructor.

-HOW TO PLAY
After everything is finished, you can just run the game and the game window will appear.
You just have to shoot as many targets as fast as possible to achieve your highest score
given the time frame.


** TECHNICAL **
The chosen data structure for this project is a hashmap due to its fast insertion 
and deletion capabilities, essential for efficiently managing data, particularly 
for frequent deletions in the game. Additionally, a set is utilized to store scores,
as it handles duplicates and maintains order, making it easy to display information 
on the screen using a reverse iteration.






