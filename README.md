# Projectile motion simulator

<p align=center>
  <img src="./assets\imgs\logo.png">
</p>

> [!WARNING]
> This software is unfinished. Keep your expectations low.

## Usage
This app is disigned to generate HD(1920x1080) videos that simulates the motion of Projectile
</br>
this is video showes how it looks like
</br>
</br>
<video controls src="./out/G_is-10.00_V0_is-15_angle_is-45_slow_is_1.0.mp4"></video>


## How to use it
### Textboxes
You can enter the values you want in textbox there are 4 textboxes
![img](./assets/imgs/Screenshot.png)
<ol>
    <li> 
        <strong>Angle</strong>
        : this takes intger value like( 1 , 2 ,3 ) only , (1.1 , 0.3) are not allowed
     </li>
    <li>
        <strong>Velocity</strong>: 
        The values as same as Anlge
    </li>
    <li>
        <strong>Gravity</strong>:
        Takes float values like (9.9 , 8.5)
    </li>
    <li>
        <strong>Slowdown</strong>:
        Takes values like Gravity , this value slow down the time , the value 1 does no effict , the value 2 will slowdown the time by 2 and so on .... ,
    </li>
    
</ol>

### Checkboxes
There is one chackbox for now it for drawing Velocity compontets all video time if you un check it the components will be drown on the max height the ball will reatch only
### keyboard
<ol>
    <li>
        <code>ESC</code> This key is specialized to exit from program
    </li>
    <li>
        <code>Space</code> This key is specialized to preview the ball path  
    </li>
    <li>
        <code>Ctrl + R</code> This two keys are specialized to render the final vidoe 
    </li>
    <li>
        <code>F</code> This key is specialized to go full screen  
    </li>
    
</ol>

## Render
The final video is rendered using [FFMPEG](https://www.ffmpeg.org/about.html)</br>
So don't worry about this window
![ffmpeg](./assets/imgs/ffmpeg.jpg)

## Download 
### Windows (64 bit)
you can download it from here [Projectile motion simulator ](#)
</br>
**Please you need trust me when this warning appears** </br></br>
![warning](./assets/imgs/win_warning.png)</br>

This project is fully open source and safe

### Linux soon
