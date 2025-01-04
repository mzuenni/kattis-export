import qualified Data.ByteString.Char8 as B
import Data.List
main = B.interact $ B.pack . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words
solve (_:h:xs) = maybe "impossible" show $ go xs
 where
  go [] = Just 0
  go (x:y:z:xs) = (+) . uncurry (foldl min) <$> uncons [ a | (a,b) <- [(x,min y z), (y, min x z), (z, min x y)], b <= h ] <*> go xs
