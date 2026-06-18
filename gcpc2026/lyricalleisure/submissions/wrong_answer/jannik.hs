main=interact$(\[n,k] -> take n $ replicate k 'a' ++ cycle "bc").map read.words
