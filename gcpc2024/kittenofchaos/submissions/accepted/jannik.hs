{-# LANGUAGE OverloadedStrings #-}
import qualified Data.ByteString.Char8 as B
import Data.Bits
(💀) (💡) = (\(Just x) -> x) . B.elemIndex (💡)
(🌈) = "bpdq"
(✅) [(🔥),(⚡)] = (if testBit (🧠) 1 then B.reverse else id) $ B.map (\(📄) -> B.index (🌈) (xor (🧠) $ (📄) 💀 (🌈))) (🔥)
  where (🧠) = B.foldl' (\(📜) (📄) -> xor (📜) $ 1 + (📄) 💀 "vhr") 0 (⚡)
main = B.interact $ (✅) . B.words
