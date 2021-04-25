#!/bin/bash

JLinkSWOViewer_CL -cpufreq 102000000 -itmmask 0x5 -itmport 0x5 -device stm32f411ce -swofreq 6000000
