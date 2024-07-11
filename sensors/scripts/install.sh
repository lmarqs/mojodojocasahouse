#!/bin/sh

echo "Installing sensors files..."

sudo cmake --install . --component sensors

echo "Reloading installing and running sensors service..."

sudo systemctl daemon-reload

sudo systemctl stop sensors.service

sudo systemctl enable sensors.service

sudo systemctl start sensors.service
