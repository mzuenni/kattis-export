{-# LANGUAGE NoMonomorphismRestriction, FlexibleContexts, TypeFamilies #-}
import Diagrams.Prelude
import Diagrams.Backend.SVG.CmdLine

treeNode :: Int -> Diagram B
treeNode x = (circle 1 <> text (show x)) # scale 0.3 # named (show x)

treeStep :: Int -> Diagram B
treeStep n = foldr (.) id edges nodes
  where points = map p2 [(3,8),(6,7),(7,6),(1,7),(4,6),(2,6),(5,5)]
        nodes = position $ take n $ zip points (map treeNode [3,6,7,1,4,2,5])
        drawEdge (a,b) = connectOutside' (with & headLength .~ verySmall) (show a) (show b)
        edges = take (n-1) $ map drawEdge [(3,6),(6,7),(3,1),(6,4),(1,2),(4,5)]

sampleIllustration :: Diagram B
sampleIllustration = vsep 2 $ map (hsep 2) [map treeStep [1..4], map treeStep [5..7]]

main :: IO ()
main = mainWith $ sampleIllustration # scaleUToY 400 # frame 25 # lwG 2
