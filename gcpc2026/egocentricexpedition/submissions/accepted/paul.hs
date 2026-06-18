import Control.Monad
import System.IO

main :: IO ()
main = do
  n <- read <$> getLine
  replicateM_ n $ do
    let send s = putStrLn s >> hFlush stdout
    send "? 1 0"
    a <- read <$> getLine
    send "? 1 1"
    b <- read <$> getLine
    let r = 2 * a^2 * b^2 / (a^2 + b^2 - a*b * sqrt 2)
    send $ "! " ++ show (round r)
