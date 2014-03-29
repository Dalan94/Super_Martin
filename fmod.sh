#!/bin/bash
wget http://www.fmod.org/download/fmodex/api/Linux/fmodapi44431linux.tar.gz
tar zxvf fmodapi44431linux.tar.gz
sudo mkdir /home/xavier/test/usr/include/FMOD
sudo cp fmodapi44431linux/api/inc/* /usr/include/FMOD
sudo cp fmodapi44431linux/api/lib/libfmodex64-4.44.31.so /usr/lib
sudo ln -s /home/xavier/test/usr/lib/libfmodex64-4.44.31.so /usr/lib/libfmod.so
rm -r fmodapi44431linux
rm -v fmodapi44431linux.tar.gz
