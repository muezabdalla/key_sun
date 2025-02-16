# key-sun

![preview when clicked](./screenshots/example.png "image")

this is the image when you click the right button.

## The keyboard monitoring software for linux
this is a software to show the keyboard clicks on screen. it is useful when making a tutorial video so that learners know what you pressed.

[comment]: # (<img src="./screenshots/mouse.png" height="100" align="left"/>)

## how to install
first download the tar file from the [releases](https://github.com/muezabdalla/key-sun/releases)
note: download the key-sun.tar not the source code(the source code is for building from source)

then extract the tar file with this command:

```
tar -xf key-sun.tar
```

then move inside the new folder

```
cd key-sun*
```

then install the dependancies

### dependancies:

- SDL2
- SDL2_image

installing dependancies on void linux:

```
sudo xbps-install SDL2 SDL2_image
```

installing dependancies on debian-based linux:

```
sudo apt install libsdl2 libsdl2-image
```

then to run it:

```
./key-sun
```

## building from source

### dependancies:

- SDL2-devel
- SDL2_image-devel
- gcc (only for compilation)
- make (only for compilation)

installing dependancies on void linux:

```
sudo xbps-install SDL2-devel SDL2_image-devel make gcc
```

installing dependancies on debian-based linux:

```
sudo apt install libsdl2-dev libsdl2-image-dev make gcc
```

after installing the dependancies, download the repository and `cd` into it and run this command to build from source:

```
make install
```

if you want to remove the package run:

```
make clean
```

to run it:

```
./key-sun
```

## common issues:

- if it does not show effect when you click that means you should change the input file by using -i flag. this is becouse the input file for your keyboard file might be differant so check the event file in your `/dev/input/eventX' where X might be any number.
for example if you want to check `/dev/input/event2` then run `cat /dev/input/event2` then click any key on the keyboard if there is an output it means that this is the keyboard input file else try another file.
- if when you use `cat /dev/input/event0` you get authentication failed or something like that. then you have two options. first: run the program as root (not recommended) second: add yourself to the input group

## other project:
mouse_sun a mouse monitoring software 

## similar projects:
- [key-mon](https://github.com/scottkirkwood/key-mon)
- [KmCaster](https://github.com/johantiden/KmCaster)
