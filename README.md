# QSnake
Made By **JolyneFr** / 51902190390  
SJTU SE2019 SEP Project1  
**This game was written only for HW, ANY other feature was NOT included.**  
**Thanks for Understanding**
## Completed Tasks ##
### 1. Basic Features  
- Start Menu
- Display & Move of Snake
- Display & Determination of Bricks & Apples
- Pause, Save & Load Game, Restart  

### 2. Advanced Features
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
    
**All required tasks are included.**
    
## Game Guide
I sincerely hope that **EVERYONE** reads this guide before playing my QSnake.  
Especially my dear TA, who grades my final work.  

### Basic Operation
Use `arrow key` & `WASD` to control the snake.  
Press `space` to pause.

### Game Notice
1. Bricks represented by different colors are shown in the gameWindow.  
    - <font color = #FFA500> Snake1 </font>,
  <font color = #000080> Snake2 </font>,
  <font color = #FF0000> Apple </font>,
  <font color = #008000> LifeFruit </font>,
  <font color = #0000FF> SpeedUp </font> ,
  <font color = #800080> SpeedDown </font>,
  <font color = #FFC)CB> Exchange </font>.  
    - Exchange Fruits are only available in MultiPlayer games(vs Player2 or Delamain)
2. The number of fruits on the canvas is set to PlayerNum by default. When a fruit is eaten, another fruit appears on a random postion within the canvas. So if you want more fruits to exist at the same time, just **use edit function** to add as many as you want.
3. You **CAN'T** move through the boundary (You will die if you do so).
4. When your head crashes into another snake's body (or yourself's), you can consume one life to **BREAK** one brick.  
5. The GameSence **WON'T** be saved implicitly, so please do it manually.
6. Delamain's algorithm may be simple, but beating it is kind of difficult.
7. The implement of `QTimer::timeout()` and `QKeyEvent::keyPressEvent()` is not connected, which means your death may occur **before** you see it on canvas.
8. All comments have been completed.

## Thanks for Playing My First Qt Game
JoyneFr 2020/12/16
