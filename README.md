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
    - LifeFruit
    - Speed Up & Down
    - Exchange Snakes (Only Available in MultiPlayer Games)
- Simple AI-Snake: **"Delamain"**
    - Using BFS Algorithm, treated all fruits equally
    
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
2. You **CAN'T** move through the boundary (You will die if you do so).
3. When your head crashes into another snake's body (or yourself's), you can pay one life to move through one brick.  
    - this will cause a skip of brick in your body. **Don't worry, it's a part of game feature.**
4. This game **WON'T** implicitly save the gameSence, please do it manually.
5. Delamain's algorithm may be simple, but beating it is kind of difficult.
6. The implement of QTimer::timeout() and QKeyEvent::keyPressEvent() aren't connected, which means your death may occur **before** you see it on canvas.
7. I'm working **desperately** on canvas-edit and completion of comments. So just be paitient.

## Thanks for Playing my First Qt Game
JoyneFr 2020/12/16