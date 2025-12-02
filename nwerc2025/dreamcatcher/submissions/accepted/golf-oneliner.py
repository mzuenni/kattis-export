#!/usr/bin/env python3
print([2 * ((n := int(input())) // 4) - 1, n // 2][n % 2])
