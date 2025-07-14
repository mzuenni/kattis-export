import qualified Data.ByteString.Char8 as B
import Data.Array

main = B.getContents >>= print . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words

test _ _ [] = True
test d next (p:ps) = next <= p && e - p < d && test d next' ps'
 where
  e' = takeWhile (\(a,b) -> a + d >= b) (zip (p:ps) ps)
  ps' = drop (length e') ps
  e = last $ p:(snd <$> e')
  next' = 2*d + max next (min p (e - d + 1))

solve (n:d:ps) = head [mex | (mex,p) <- assocs p, test d 0 p]
 where
  p = reverse <$> accumArray (flip (:)) [] (0,n) (zip ps [0..n])
