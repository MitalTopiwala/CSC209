#!/bin/bash

atotal=0
amaxtotal=0

ttotal=0
tmaxtotal=0



for x in a1 a2 a3 a4
do
    
    if [ -f "$x/feedback.txt" ]
    then
        
        grade=`tail -n 1 $x/feedback.txt | tr -d [:blank:]` #removes the spaces from last

        IFS='/' read -ra grArray <<< "$grade" #creates an array with the character before and after the / 
        score=${grArray[0]}
        max=${grArray[1]}
        
        atotal=$(($atotal + ${grArray[0]})) 
        amaxtotal=$(($amaxtotal + ${grArray[1]})) 
        echo $x": "$score" / "$max
    fi

    if [ ! -f "$x/feedback.txt" ] 
    then
        echo $x": - / -"
    fi

done
echo ""
for x in t01 t02 t03 t04 t05 t06 t07 t08 t09 t10 t11
do

    if [ -f "$x/feedback.txt" ]
    then

        grade=`tail -n 1 $x/feedback.txt | tr -d [:blank:]` #removes the spaces from last

        IFS='/' read -ra grArray <<< "$grade" #creates an array with the character before and after the / 
        score=${grArray[0]}
        max=${grArray[1]}

        ttotal=$(($ttotal + ${grArray[0]})) 
        tmaxtotal=$(($tmaxtotal + ${grArray[1]})) 
        echo $x": "$score" / "$max
    fi

    if [ ! -f "$x/feedback.txt" ]
    then
        echo $x": - / -"
    fi
done
echo "" 
echo "Assignment Total: "$atotal" / "$amaxtotal
echo "Tutorial Total: "$ttotal" / "$tmaxtotal 
