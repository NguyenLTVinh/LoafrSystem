#!/usr/bin/env bash
echo "Building ..."
mkdir build
cd build && cmake ../ && make && mv loafr ../ && mv loafr_test ../
