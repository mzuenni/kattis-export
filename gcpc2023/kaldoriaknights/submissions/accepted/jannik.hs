{-# LANGUAGE Strict #-}
import Data.Array.Unboxed
main = interact $ show . solve . map read . words
m x = mod x (10^9 + 7)
solve (n:_:as) = s n $ foldl (\dp p -> (s p dp) : dp) [] pfx
  where
    _:pfx = scanl (+) 0 as
    fac :: UArray Int Int
    fac = listArray (0,n) $ scanl (\x -> m . (x*)) 1 [1..]
    s p acc = m $ fac!p - foldl (+) 0 [ m $ d * fac!(p-f) | (d,f) <- zip (reverse acc) pfx ]
