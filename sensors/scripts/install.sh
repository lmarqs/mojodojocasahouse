#!/bin/sh

echo "Installing smartwatch files..."

sudo cmake --install . --component smartwatch

echo "Reloading installing and running smartwatch service..."

sudo systemctl daemon-reload

sudo systemctl stop smartwatch.service

sudo systemctl enable smartwatch.service

sudo systemctl start smartwatch.service
