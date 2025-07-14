main = interact $ unwords . map show . solve . tail . map (read :: String -> Int) . words
solve cs = [4, max,may, mix,may, mix,miy, max,miy]
 where
  (max,mix) = (maximum xs,minimum xs)
  (may,miy) = (maximum ys,minimum ys)
  xs = [ x | (x,i) <- zip cs [1..], odd i ]
  ys = [ y | (y,i) <- zip cs [1..], even i ]
