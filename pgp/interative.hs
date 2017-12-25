import Data.Char

main :: IO ()
main = return ()

-- Problem: Haskell programs are pure functions, interactive programs have side effects
-- Solution - use types to distinguesh pure expressions from impure actions

-- Actions
-- IO a - the type of actions that return a value of type a
-- Primitives:
-- getChar :: IO Char
-- putChar :: Char  -> IO()
-- return  :: a -> IO a

-- getLine  :: IO String
-- putStr   :: String -> IO()
-- putStrLn :: String -> IO()

-- A game of NIM
-- Board utilities:
type Board = [Int]
initial :: Board
initial = [5,4..1]

-- Returns true if the game is over, i.e. board is empty
finished :: Board -> Bool
finished b = all (== 0) b

-- Check if move is valid, i.e. selected row has at least as many stars as requested to remove
valid :: Board -> Int -> Int -> Bool
valid b row num = b !! (row -1) >= num

-- Creates new board, removing selected number of stars from selected row
move :: Board -> Int -> Int -> Board
move b row num = [adjust r n | (r,n) <- zip [1..5] b]
                 where
                    adjust r n = if r == row then n-num else n

-- I/O utilities:
newline :: IO()
newline = putChar '\n'

stars :: Int -> String
stars n = concat (replicate n "* ")

putRow :: Int -> Int -> IO()
putRow row num = do putStr (show row)
                    putStr ": "
                    putStr (stars num)

putBoard :: Board -> IO()
putBoard [a,b,c,d,e]  = do putRow 1 a
                           putRow 2 b
                           putRow 3 c
                           putRow 4 d
                           putRow 5 e

getDigit  :: String -> IO Int
getDigit prompt =
  do putStr prompt
     x <- getChar
     newline
     if isDigit x then
       return (ord x - ord '0')
     else
       do putStrLn "ERROR: Invalid digit"
          getDigit prompt
nim :: IO()
nim = play initial 1

next :: Int -> Int
next 1 = 2
next 2 = 1

play :: Board -> Int -> IO()
play board player =
  do newline
     putBoard board
     if finished board then
        do newline
           putStr "Player "
           putStr (show (next player))
           putStr " wins!!"
     else
      do newline
         putStr "Player "
         putStr (show player)
         r <- getDigit "Enter a row number: "
         n <- getDigit "Stars to remove: "
         if valid board r n then
           play (move board r n) (next player)
         else
           do newline
              putStrLn "Error: Invalid play"
