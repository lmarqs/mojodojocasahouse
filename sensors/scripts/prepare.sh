#!/bin/sh

echo "Preparing venv for sensors..."

sudo apt-get install -y i2c-tools libgpiod-dev python3-libgpiod

sudo raspi-config nonint do_i2c 0
sudo raspi-config nonint do_spi 0
sudo raspi-config nonint do_serial_hw 0
sudo raspi-config nonint do_ssh 0
sudo raspi-config nonint do_camera 0
sudo raspi-config nonint disable_raspi_config_at_boot 0

sudo python3 -m venv /opt/mdch/venv --system-site-packages

sudo /opt/mdch/venv/bin/pip3 install -r requirements.txt

