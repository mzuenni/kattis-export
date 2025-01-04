import Data.List
main = interact $ solve . map read . words
solve (_:h:xs) = maybe "impossible" show $ go xs
 where
  go [] = Just (0 :: Int)
  go (x:y:z:xs) = (+) . uncurry (foldl min) <$> uncons [ a | (a,b) <- [(x,min y z), (y, min x z), (z, min x y)], b <= h ] <*> go xs
