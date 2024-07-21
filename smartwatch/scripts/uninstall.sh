#!/bin/sh

echo "Stopping and disabling smartwatch service..."

sudo systemctl stop smartwatch.service

sudo systemctl disable smartwatch.service
