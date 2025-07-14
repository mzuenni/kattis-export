{-# LANGUAGE Strict #-}
import qualified Data.ByteString.Char8 as B
import Data.Array.Unboxed
import Data.Bifunctor
import qualified Data.Set as S

main = B.getContents >>= print . solve . map ((\(Just(x,_))->x) . B.readInt) . B.words

binarySearch test = head [bs (div hi 2) hi | hi <- (2^) <$> [0..], test hi]
 where
  bs lo hi
   | lo + 1 < hi = let m = lo + div (hi - lo) 2 in if test m then bs lo m else bs m hi
   | otherwise = hi

solve (n:b:r:w:dt) = binarySearch test
 where
  ts :: UArray Int Int
  (ts,d) = first (listArray (1,b) . tail . scanl (+) 0) $ splitAt b dt
  test maxT = try 0 d
   where
    try t xs = go t xs 0 0 S.empty S.empty
    go t [] _ _ _ p = True
    go t (dst:xs) ms wait stops people
      | t + wait' * 2 * w + ts!ms' > maxT = wait > 0 && try (t + r) (dst:xs)
      | otherwise = go t xs ms' wait' st ppl
     where
      ms' = max ms dst
      ppl = S.insert (dst,wait) people
      st = S.insert dst stops
      wait' = wait + 1 + S.findIndex dst st + if S.member dst stops
       then 0
       else S.size ppl - (1 + S.findIndex (dst,wait) ppl)
