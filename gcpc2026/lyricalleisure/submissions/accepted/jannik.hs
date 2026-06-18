main=interact$(\[n,k] -> take n $ replicate k 'a' ++ cycle "bcd").map read.words
