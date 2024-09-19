{-# LANGUAGE BangPatterns, OverloadedStrings #-}
import qualified Data.ByteString.Char8 as C
import Data.List

int s = case C.readInt s of Just (x,_) -> x

data P = P { x :: !Int, y :: !Int }
toP :: [Int] -> [P]
toP (a:b:xs) = P a b : toP xs
toP [] = []

colinear :: P -> P -> P -> Bool
colinear a b c = (x b-x a)*(y c-y a) == (x c-x a)*(y b-y a)

main = C.interact $ solve . toP . map int . tail . C.words

solve ps = if go 3 ps then "possible" else "impossible"
go k ps = null (drop (2*k) ps) || any (go $ k-1) [ filter (not . colinear x y) ps | (x:ys) <- tails $ take (k+1) ps, y <- ys ]
