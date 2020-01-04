#!/bin/bash

install_deps.verify() { task.verify.permissive; }
install_deps() {
	apt-get install -y pkg-config
}

config_src.verify() { task.verify.permissive; }
config_src() {
	mkdir build
	cd build
	pyra_cmake ..
}

build_src.verify() { task.verify.permissive; }
build_src() {
	cd build
	make -j 4
}

install_src() {
	cp build/ketm target/root
}


pyra_setprj ketm_engine
task.add install_deps	"Install missing build depenency"
task.add config_src	"Configure ketm"
task.add build_src	"Build sources"
task.add install_src	"Install ketm"


