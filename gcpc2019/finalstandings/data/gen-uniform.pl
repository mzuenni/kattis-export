#!/usr/bin/env perl

use strict;
use warnings;

my $t = shift @ARGV // 15;
my $p = shift @ARGV // 15;
print STDERR "t=$t p=$p\n";
print "$t $p\n";

my @strengths = map {sprintf '%.6f', rand} (1 .. $t-1);
print "@strengths\n";

my @difficulties = map {sprintf '%.6f', rand} (1 .. $p);
print "@difficulties\n";

for my $team (1 .. $t-1) {
    my @row = map {('X', '-', '?')[int rand 3]} (1 .. $p);
    print "@row\n";
}

my @row = map {('X', '-')[int rand 1.85]} (1 .. $p);
print "@row\n";
