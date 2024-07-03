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
