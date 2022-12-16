#!/bin/sh

#what I do here is that I trimm out the message at the end, then I remove the empty lines and lastly I search and replace on each line the message to transform it into the python code
sed 's/Can you digest the message? :)//' $1 | sed '/^$/d' |sed 's/ degrees//' | sed 's/ spaces//'  | sed 's/Tourne gauche de /my_pen.left(/' | sed 's/Tourne droite de /my_pen.right(/' | sed 's/Avance /my_pen.forward(/' | sed 's/Recule /my_pen.backward(/' | sed 's/$/)/'
echo "turtle.done()"
