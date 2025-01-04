import qualified Data.ByteString.Char8 as B
import Data.Graph
import Data.Foldable

l (x:y:xs) = (x,y) : (y,x) : l xs
l _ = []

main = B.getContents >>= print . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words
solve (n:_:es) = foldl' max 0 $ length . toList <$> dff (buildG (1,n) (l es))
