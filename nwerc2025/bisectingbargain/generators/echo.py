#!/usr/bin/env python3
import sys
import random
from random import randrange

print(eval(' '.join(sys.argv[1:]).encode('ascii').decode('unicode_escape')))
