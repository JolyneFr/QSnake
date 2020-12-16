# QSnake
Made By **JolyneFr** / 51902190390  
SJTU SE2019 SEP Project1
## Completed Tasks ##
### 1.Basic Features  
- Start Menu
- Display & Move of Snake
- Display & Determination of Bricks & Apples
- Pause, Save & Load Game, Restart  

### 2.Advanced Features
- MultiPlayer in one game (Arrow Keys for Snake1 & WASD for Snake2)
- 3 Special Fruit
    - LifeFruit.
    - Speed Up & Down (MAX_SPEED == 5 && MIN_SPEED == 1).
    - Exchange Snakes (Only Available in MultiPlayer Games).
- Map Editon
    - You are able to edit bricks (except snakes and boundarys).
    - Edition is available in Pause and Start windows.
    - Remember to ask for permission if you are playing with friends.
- Simple AI-Snake: **"Delamain"**
    - Using BFS Algorithm, treated all fruits equally.
    
## Game Guide
I sincerely hope **EVERYONE** read this guide before playing my QSnake.  
Especially my dear TA, who jugdes my final score.  
1. Bricks represented by different colors are shown in the gameWindow.  
    - <font color = #FFA500> Snake1 </font>,
  <font color = #000080> Snake2 </font>,
  <font color = #FF0000> Apple </font>,
  <font color = #008000> LifeFruit </font>,
  <font color = #0000FF> SpeedUp </font> ,
  <font color = #800080> SpeedDown </font>,
  <font color = #FFC)CB> Exchange </font>.  
    - Exchange Fruits are only available in MultiPlayer games(vs Player2 or Delamain)
2. Number of fruits on the canvas is defaulted set to PlayerNum. When a fruit is eaten, another fruit appears on a random postion within the canvas. So if you want more fruits exist at the same time, just **use edit function** to add as many as you want.
3. You **CAN'T** move through the boundary (You will die if you do so).
4. When your head crashes into another snake's body (or yourself's), you can pay one life to move through one brick.  
5. This game **WON'T** implicitly save the gameSence, please do it manually.
6. Delamain's algorithm may be simple, but beating it is kind of difficult.
7. The implement of QTimer::timeout() and QKeyEvent::keyPressEvent() aren't connected, which means your death may occur **before** you see it on canvas.
8. I'm working **desperately** on completion of comments. So just be paitient.

## Thanks for Playing My First Qt Game
JoyneFr 2020/12/16