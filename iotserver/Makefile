.PHONY: build

build:
	pio run -e raspberrypi_3b_fbdev

install:
	sudo cp .pio/build/raspberrypi_3b_fbdev/program /bin/iotserver
	chown root:root /bin/iotserver

	sudo cp etc/systemd/system/iotserver.service /etc/systemd/system/iotserver.service
	chown root:root /etc/systemd/system/iotserver.service

	sudo cp boot/firmware/config.txt /boot/firmware/config.txt
	chown root:root /boot/firmware/config.txt

	sudo cp boot/overlays/tft35a.dtb /boot/overlays/tft35a.dtb
	chown root:root /boot/overlays/tft35a.dtb
