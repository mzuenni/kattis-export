main = interact $ show . solve . read
solve t = minimum [ t - w | w <- [0..min t (10*60)], legal w (t - w) ]
legal w b = (w <= 9*60 || b >= 45) && (w <= 6*60 || b >= 30)
