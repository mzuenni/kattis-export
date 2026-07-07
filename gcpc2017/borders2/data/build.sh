./visualize $1 ${1%.in}.ans > tmp.svg
inkscape tmp.svg --export-background=white --export-png=${1%.in}.png
rm tmp.svg
