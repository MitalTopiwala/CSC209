#1/bin/bash

grade = 'cat feedback.txt | tr -d [:blank:]'

IFS='/' read -ra grArray <<< "$grade"
score=${grArray[0]}
max=${grArray[1]}

echo $score
echo $max

