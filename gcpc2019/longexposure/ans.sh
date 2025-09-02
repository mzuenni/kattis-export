for inputfile in data/secret/*.in; do
	basename="${inputfile%.*}"
	if [ ! -f $basename.ans ]; then
		./submissions/accepted/philipp_longdouble_distributive < $inputfile > $basename.ans
	fi
done
