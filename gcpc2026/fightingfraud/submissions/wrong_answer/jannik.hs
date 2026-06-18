import Data.Set qualified as S
main = interact $ (\b -> if b then "yes\n" else "no\n") . solve [] S.empty . tail . words
solve :: [String] -> S.Set String -> [String] -> Bool
solve [] _ ("dropoff":b:xs) = False
solve (s:ss) se ("dropoff":b:xs) = s == b && solve ss se xs
solve ss se (_:b:xs) = not (S.member b se) && solve (b:ss) (S.insert b se) xs
solve [] _ _ = True
solve _ _ _ = False
