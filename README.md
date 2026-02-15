# Inch Along

2D platformer made in Visual Studio 2019 using C++, Box2D, and SFML 2.6.1

**IMPORTANT NOTE: ** Run in x86!

<img width="1292" height="576" alt="image" src="https://github.com/user-attachments/assets/6740fcca-d1dc-42d5-8b1f-0fcaafce20fe" />

## Game Play: 

Use WASD to move as well as Space to Jump. Use Space or Enter to select items in the menu.

Avoid ants and spikes, collect leaves, and make it to the finish line flag to progress levels.

<img width="1233" height="852" alt="image" src="https://github.com/user-attachments/assets/8afd61d1-15ec-47ab-b987-9f4f9f0ef835" />

The game will keep track of the total amount of leaves you’ve collected throughout the 5 levels, this is your overall game score.

<img width="1522" height="846" alt="image" src="https://github.com/user-attachments/assets/8b85618b-b2a4-4027-93b0-89494190dc47" />

Different levels can be easily imported by the player using the MapFromImage feature and the Map Color Key found in Map.cpp

## Known Bugs:

The player and ants will sometimes register a wall that isn't there and stop moving / turn around randomly. This is a bug within the Box2D collider. The player can correct this bug when it happens by backing up or jumping.

## Credits:

Sky Background made can be found at https://free-game-assets.itch.io/free-pixel-art-cloud-and-sky-backgrounds. All other sprites are original.

Made following The Hello World Guy’s tutorial https://www.youtube.com/watch?v=aCq7P0e4cv0&list=PLlnvVTSJ0XwdnquTl8y5xvsY4aka_8h8H
