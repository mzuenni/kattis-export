{-# LANGUAGE BangPatterns #-}
import Data.Bits
import Data.Char
import Data.List
import Data.Word
import qualified Data.ByteString.Char8 as B

data Block = Circle !Word64 | Square !Word64 | Triangle !Word64
  deriving (Eq, Read)

fits :: Block -> Block -> Bool
fits (Circle a)   (Circle b)   = a < b
fits (Circle a)   (Square b)   = 2*a < b
fits (Circle a)   (Triangle b) = a < 876543210 && 12*a^2 < b^2
fits (Square a)   (Circle b)   = a^2 < 2*b^2
fits (Square a)   (Square b)   = a < b
fits (Square a)   (Triangle b) = a*(a+6*b) < 3*b^2
fits (Triangle a) (Circle b)   = a^2 < 3*b^2
fits (Triangle a) (Square b)   = a < 2*b && 48*y^4 < (8*y^2 - x^2)^2
  where x = toInteger a; y = toInteger b
fits (Triangle a) (Triangle b) = a < b

binarySearch :: (Word64 -> Bool) -> Word64
binarySearch prop = if prop 0 then 0 else go 0 (2*10^9)
  where
    go !lo !hi
      | hi-lo == 1  = hi
      | prop md     = go lo md
      | otherwise   = go md hi
      where md = shiftR (lo+hi) 1

grundy :: Block -> Word64
grundy (Circle 1) = 2
grundy block = binarySearch (\x -> not $ fits (Triangle (x+1)) block)

hasSuccessor :: Block -> (Word64 -> Block) -> Word64 -> Bool
hasSuccessor block shape 2 | (shape 1 == Circle 1) = fits (Circle 1) block
hasSuccessor block shape g = fits (shape size) block && grundy (shape size) == g
  where
    size = binarySearch (\x -> fits (Triangle g) (shape x))

solve :: [Block] -> Int
solve blocks = length $ filter id $ canWin <$> blocks <*> [Circle, Square, Triangle] 
  where
    totalGrundy = foldl' xor 0 $ map grundy blocks
    canWin block shape = hasSuccessor block shape (totalGrundy `xor` grundy block)

readBlock :: B.ByteString -> Block
readBlock s =
  case B.head s of
    'c' -> Circle x
    's' -> Square x
    't' -> Triangle x
  where
    Just (y,_) = B.readInt $ B.words s !! 1
    x = fromIntegral y

main :: IO ()
main = B.interact $ B.pack . (++ "\n") . show . solve . map readBlock . tail . B.lines
