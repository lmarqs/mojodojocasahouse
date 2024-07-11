#!/bin/sh

echo "Installing sensors files..."

sudo cp etc/systemd/system/sensors.service /etc/systemd/system/sensors.service

sudo chmod 644 /etc/systemd/system/sensors.service

echo "Reloading installing and running sensors service..."

sudo systemctl daemon-reload

sudo systemctl stop sensors.service

sudo systemctl enable sensors.service

sudo systemctl start sensors.service
