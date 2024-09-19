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

randoms :: [Integer]
randoms = map (\x -> 1 + x`mod`100) $ iterate (\s -> (1103515245*s + 12345) `rem` 2^31) 42

solve :: Integer -> [Integer]
solve y = go randoms y
  where
    go xs y =
      let (ys, zs) = splitAt 3 xs
       in if length ys == 3 && not (fromIntegral y `elem` values ys) then ys else go zs y

main :: IO ()
main = readLn >>= (putStrLn . unwords . map show . solve)
