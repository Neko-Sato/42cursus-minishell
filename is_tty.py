#!/usr/bin/python3
import os
import sys
	
os._exit(0 if os.isatty(sys.stdin.fileno()) else 1) 