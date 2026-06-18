import System.IO

main :: IO ()
main = do
  let put r c = putStrLn (show r ++ " " ++ show c) >> hFlush stdout
  let get = map read . words <$> getLine
  put 5 5
  [r, _] <- get
  if r == 5
     then put 4 5 >> get >>= \[r, _] -> put (if r == 6 then 3 else 6) 5
     else put 5 4 >> get >>= \[_, c] -> put 5 (if c == 6 then 3 else 6)
