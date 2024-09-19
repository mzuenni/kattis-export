-- @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED
import Data.Bits
import Data.Char
import Data.List

data Block = Circle Int | Square Int | Triangle Int
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

binarySearch :: (Int -> Bool) -> Int
binarySearch prop = if prop 0 then 0 else go 0 up
  where
    up = head $ filter prop $ iterate (*2) 1
    go lo hi | hi-lo == 1  = hi
    go lo hi = let md = (lo+hi)`div`2 in if prop md then go lo md else go md hi

grundy :: Block -> Int
grundy (Circle 1) = 2
grundy block = binarySearch (\x -> not $ fits (Triangle (x+1)) block)

hasSuccessor :: Block -> (Int -> Block) -> Int -> Bool
hasSuccessor block shape 2 | (shape 1 == Circle 1) = fits (Circle 1) block
hasSuccessor block shape g = fits (shape size) block && grundy (shape size) == g
  where
    size = binarySearch (\x -> fits (Triangle g) (shape x))

solve :: [Block] -> Int
solve blocks = length $ filter id $ canWin <$> blocks <*> [Circle, Square, Triangle] 
  where
    totalGrundy = foldl' xor 0 $ map grundy blocks
    canWin block shape = hasSuccessor block shape (totalGrundy `xor` grundy block)

main :: IO ()
main = interact $ (++ "\n") . show . solve . map (read . (\(x:xs) -> (toUpper x : xs))) . tail . lines
