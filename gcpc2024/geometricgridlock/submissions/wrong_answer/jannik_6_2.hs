import Data.List
main = interact $ maybe "no\n" (unlines . ("yes":)) . solve . map read . words

five =
 [ "NNNUU"
 , "YWNNU"
 , "YWWUU"
 , "YYWWL"
 , "YLLLL"
 ]
_🔧0 = Just []
5🔧1 = Just ["IIIII"]
_🔧1 = Nothing
5🔧2 = Nothing
w🔧2 = let ws = take (div w 5) $ cycle ["NNYYYY","NNNY"] in Just
 [ "PP" ++ concat (init ws) ++ repeat 'P'
 , "PPP" ++ concat (tail ws) ++ repeat 'P'
 ]
w🔧h | h == 3 || h == 7 = ((cycle <$>
 [ "UUFFP"
 , "UFFPP"
 , "UUFPP"
 ])++) <$> w🔧(h - 3)
w🔧h | h == 4 || h == 6 = ((cycle <$>
 [ "LNVVV"
 , "LNZZV"
 , "LNNZV"
 , "LLNZZ"
 ])++) <$> w🔧(h - 4)
w🔧h = ((cycle <$> five)++) <$> w🔧(h - 5)
solve [h,w]
 | mod h 5 == 0 = transpose . map (take h) <$> h🔧w
 | mod w 5 == 0 = map (take w) <$> w🔧h
 | otherwise = Nothing
 
