#!/bin/sh

echo "Preparing env for sensors..."

echo "Installing libs..."

sudo apt-get update

sudo apt-get install -y i2c-tools libgpiod-dev python3-libgpiod

echo "setting up interfaces..."

sudo raspi-config nonint do_i2c 0
sudo raspi-config nonint do_spi 0
sudo raspi-config nonint do_serial_hw 0
sudo raspi-config nonint do_ssh 0
sudo raspi-config nonint do_camera 0
sudo raspi-config nonint disable_raspi_config_at_boot 0

echo "Creating virtual env..."

sudo python3 -m venv /opt/mdch/venv --system-site-packages


echo "Installing python libs..."

sudo /opt/mdch/venv/bin/pip3 install -r requirements.txt

