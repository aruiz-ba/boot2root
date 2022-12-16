###thor

We find a simple text file called with 1471 lines.
```
...
Avance 1 spaces
Tourne droite de 1 degrees
Avance 1 spaces
Tourne droite de 1 degrees
Avance 1 spaces
Tourne droite de 1 degrees
Avance 1 spaces
Tourne droite de 1 degrees
Avance 1 spaces
Tourne droite de 1 degrees
Avance 1 spaces
Tourne droite de 1 degrees
...
```
We quickly realise that they are some kind of instrucctions for one of this drawing programs that use a pencil that moves with the movement commands you give.
We found a library for python that does this exact thing and is called turtle which give us a hint that we are going on the right direction.
To process the file we do a simple script using sed that trims the yunk from the file empty lines and a message at the end of the file "Can you digest the message? :)" and then just replace the text to have the actual syntax for the library turtle to write

![alt text](.git/turtle.png)

This is the output we get and if we follow the writting we can distinguish the letters "SLASH"

We tried using it by itself as the password but with no luck until we tried to encrypt it with md5sum

```
[adri@thinkpad ~]$ echo -n "SLASH" | md5sum
646da671ca01bb5d84dbb5fb2238dc8e  -
```
And thats it we got the password for it!!!
