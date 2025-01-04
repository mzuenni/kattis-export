import Data.Bits
import Data.List
i c = (\(Just x) -> x) . elemIndex c
solve [s,t] = (if testBit x 1 then reverse else id) $ (\c -> "bpdq" !! xor x (i c "bpdq")) <$> s
 where x = foldl' (\r c -> xor r $ 1 + i c "vhr") 0 t
main = interact $ solve . words
