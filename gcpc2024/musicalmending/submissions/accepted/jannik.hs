import qualified Data.ByteString.Char8 as B
import Data.List

main = B.getContents >>= print . solve . map ((\(Just(x,_)) -> x) . B.readInt) . B.words
solve (n:ts) = let ps = zipWith (-) ts [0..] in sum $ abs . (-) (sort ps!!div n 2) <$> ps

