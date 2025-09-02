for inputfile in data/secret/*.in; do
	basename="${inputfile%.*}"
	if [ ! -f $basename.ans ]; then
		./submissions/accepted/philipp < $inputfile > $basename.ans
	fi
done
