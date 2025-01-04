import Data.Graph
import Data.Foldable

l (x:y:xs) = (x,y) : (y,x) : l xs
l _ = []

main = interact $ unlines . return . show . solve . map read . words
solve (n:_:es) = foldl' max 0 $ length . toList <$> dff (buildG (1,n) (l es))
