#!/bin/sh

echo "Stopping and disabling sensors service..."

sudo systemctl stop sensors.service

sudo systemctl disable sensors.service

echo "Removing sensors files..."

rm -rf /etc/systemd/system/sensors.service

echo "\nReloading systemctl..."

sudo systemctl daemon-reload
