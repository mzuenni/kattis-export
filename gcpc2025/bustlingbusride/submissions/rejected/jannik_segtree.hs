-- @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
{-# LANGUAGE Strict #-}
import qualified Data.ByteString.Char8 as B
import Data.Array.Unboxed
import Data.Bifunctor
import Data.Monoid
import qualified Data.IntSet as S

main = B.getContents >>= print . solve . map ((\(Just(x,_))->x) . B.readInt) . B.words

data Tree
 = Tree !Int Tree Tree
 | Leaf !Int
 | Null

val (Tree v _ _) = v
val (Leaf v) = v
val Null = 0
mkTree l r = Tree (val l + val r) l r
update t i n _ | i >= n = t
update Null i n f
  | n == 1 = Leaf (f 0)
  | otherwise = update (Tree 0 Null Null) i n f
update (Leaf v) _ _ f = Leaf $ f v
update (Tree _ l r) i n f
  | i < m     = mkTree (update l i m f) r
  | otherwise = mkTree l                (update r (i - m) (n - m) f)
 where
  m = div (n + 1) 2
query Null _ _ = 0
query (Leaf v) _ _ = v
query (Tree v l r) i n
  | i >= n = v
  | i >= m = val l + query r (i - m) (n - m)
  | otherwise = query l i m
 where
  m = div (n + 1) 2

binarySearch :: (Int -> Bool) -> Int
binarySearch test = head [bs (div hi 2) hi | hi <- (2^) <$> [0..], test hi]
 where
  bs lo hi
   | lo + 1 < hi = let m = lo + div (hi - lo) 2 in if test m then bs lo m else bs m hi
   | otherwise = hi

solve (n:b:r:w:dt) = binarySearch test
 where
  ts :: UArray Int Int
  (ts,d) = first (listArray (1,b) . tail . scanl (+) 0) $ splitAt b dt
  q t i = query t i (b + 1)
  upd t i = update t i (b + 1)
  test maxT = try 0 d
   where
    try t xs = go t xs 0 0 Null S.empty Null
    go t [] _ _ _ _ p = True
    go t (dst:xs) ms wait stops seen people
      | t + wait' * 2 * w + ts!ms' > maxT = wait > 0 && try (t + r) (dst:xs)
      | otherwise = go t xs ms' wait' st (S.insert dst seen) ppl
     where
      ms' = max ms dst
      ppl = upd people dst (+ 1)
      st = upd stops dst (const 1)
      wait' = wait + 1 + q st (dst - 1) + if S.member dst seen
       then 0
       else val ppl - q ppl dst
