import qualified Data.ByteString.Char8 as B
import Data.List

main = B.getContents >>= putStrLn . unwords . map show . (\(_:t:a) -> go t a) . map ((\(Just(x,_)) -> x) . B.readInt) . B.words

sim h (a:as)
 | h>1  = (a+1) : sim (h-1) as
 | a==0 = 1 : as
 | otherwise = 0 : sim (h+a) as
sim _ _ = []

go 0 a = a
go _ [] = []
go t [0] = [rem t 2]
go t (0:a:as) = rem t 2 : (a+div t 2) : go (div t 2) as
go t as = go (t-1) (sim 1 as)
