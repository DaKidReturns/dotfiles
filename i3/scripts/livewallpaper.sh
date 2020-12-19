#! /bin/bash

pic1Dir="/home/rohit/Pictures/Inkscape/My Illustraions/Practice pics/cursor_off.png"
pic2Dir="/home/rohit/Pictures/Inkscape/My Illustraions/Practice pics/cursor_on.png"
while [ 1 ]
do
    sleep 0.5
    nitrogen --set-zoom-fill $pic1Dir 
    sleep 0.5
    nitrogen --set-zoom-fill $pic2Dir 
done

exec nitrogen --restore
