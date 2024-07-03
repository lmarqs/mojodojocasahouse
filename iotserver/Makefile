.PHONY: build

all: build install

build:
	pio run -e raspberrypi_3b_fbdev

install:
	sudo cp etc/systemd/system/iotserver.service /etc/systemd/system/iotserver.service
	sudo chown root:root /etc/systemd/system/iotserver.service

	sudo systemctl daemon-reload
	sudo systemctl stop iotserver.service

	sudo cp .pio/build/raspberrypi_3b_fbdev/program /bin/iotserver
	sudo chown root:root /bin/iotserver

	sudo systemctl enable iotserver.service
	sudo systemctl start iotserver.service

	sudo cp boot/firmware/config.txt boot/firmware/config.txt.$(date +%s).bak
	sudo cp boot/firmware/config.txt /boot/firmware/config.txt
	sudo chown root:root /boot/firmware/config.txt

	sudo cp boot/overlays/tft35a.dtb /boot/overlays/tft35a.dtb
	sudo chown root:root /boot/overlays/tft35a.dtb

increase-swap:
	sudo dphys-swapfile swapoff
	sudo sed -i 's/CONF_SWAPSIZE=100/CONF_SWAPSIZE=2048/g' /etc/dphys-swapfile
	sudo dphys-swapfile setup
	sudo dphys-swapfile swapon
