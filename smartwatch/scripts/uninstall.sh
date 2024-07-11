#!/bin/sh

echo "Stopping and disabling smartwatch service..."

sudo systemctl stop smartwatch.service

sudo systemctl disable smartwatch.service

echo "Removing smartwatch files..."

cat install_manifest_smartwatch.txt

cat install_manifest_smartwatch.txt | xargs sudo rm -rf

echo "\nReloading systemctl..."

sudo systemctl daemon-reload
