#!/bin/bash

d="t01"



for x in t01 t02 t03 t04 t05 t06 t07 t08 t09 t10 t11 a1 a2 a3 a4
do
    
    if [ -f "$x/feedback.txt" ]
    then
        
        grade=`tail -n 1 $x/feedback.txt | tr -d [:blank:]` #removes the spaces from last

        IFS='/' read -ra grArray <<< "$grade" #creates an array with the character before and after the / 
        score=${grArray[0]}
        max=${grArray[1]}

        echo $x": "$score" / "$max
    fi

    if [ ! -f "$x/feedback.txt" ] 
    then
        echo $x": - / -"
    fi
done
