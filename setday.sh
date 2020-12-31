#!/bin/bash
sed -i -E "s/(day)[0-9]+/\1$1/" makefile
