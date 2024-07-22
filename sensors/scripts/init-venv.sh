#!/bin/sh

echo "Preparing venv for sensors..."

sudo python3 -m venv /opt/mdch/venv --system-site-packages

sudo /opt/mdch/venv/bin/pip3 install -r requirements.txt
