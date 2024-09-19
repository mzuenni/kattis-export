import Control.Monad
import Data.List
import Data.Ratio

partitions :: [a] -> [([a],[a])]
partitions [] = [([],[])]
partitions (x:xs) = do
  (ys,zs) <- partitions xs
  [(x:ys,zs), (ys,x:zs)]

values :: [Integer] -> [Rational]
values [] = []
values [x] = [fromIntegral x]
values xs = do
  (ys,zs) <- partitions xs
  guard $ not (null ys) && not (null zs)
  op <- [(+), (-), (*), \x y -> if y /= 0 then x/y else x+y]
  values ys ++ values zs ++ (op <$> values ys <*> values zs)

choose :: Int -> [a] -> [[a]]
choose 0 _ = [[]]
choose _ [] = []
choose k (x:xs) = choose k xs ++ map (x:) (choose (k-1) xs)

goodTriples :: [[Integer]]
goodTriples = filter (all ok . values) $ choose 3 [1..100]
  where ok x = not $ 1 <= x && x <= 9 && denominator x == 1

solve :: Integer -> [Integer]
solve y = head $ filter (\xs -> not $ fromIntegral y `elem` values xs) $ choose 3 [1..100]

main :: IO ()
main = interact $ (++"\n") . unwords . map show . solve . read
