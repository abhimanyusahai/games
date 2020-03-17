require 'pry'

INITIAL_MARKER = " ".freeze
PLAYER_MARKER = "X".freeze
COMPUTER_MARKER = "O".freeze
WINNING_LINES = [[1, 2, 3], [4, 5, 6], [7, 8, 9]] +
                [[1, 4, 7], [2, 5, 8], [3, 6, 9]] +
                [[1, 5, 9], [3, 5, 7]]
FIRST_PLAYER = "Choose".freeze

def prompt(message)
  puts "=> #{message}"
end

def display_board(brd, score)
  system 'clear'
  puts "You're a #{PLAYER_MARKER}. Computer is #{COMPUTER_MARKER}"
  puts "Player's score is #{score['Player']}, Computer's score is #{score['Computer']}"
  puts ""
  puts "     |     |"
  puts "  #{brd[1]}  |  #{brd[2]}  |  #{brd[3]}  "
  puts "     |     |"
  puts "-----+-----+-----"
  puts "     |     |"
  puts "  #{brd[4]}  |  #{brd[5]}  |  #{brd[6]}  "
  puts "     |     |"
  puts "-----+-----+-----"
  puts "     |     |     "
  puts "  #{brd[7]}  |  #{brd[8]}  |  #{brd[9]}  "
  puts "     |     |     "
end

def initialize_board
  new_board = {}
  (1..9).each { |num| new_board[num] = INITIAL_MARKER }
  new_board
end

def empty_squares(brd)
  brd.keys.select { |num| brd[num] == INITIAL_MARKER }
end

def joinor(empty_squares, mark = ', ', conjunction = 'or')
  empty_squares[-1] = "#{conjunction} #{empty_squares.last}" if empty_squares.length > 1
  empty_squares.join(mark)
end

def find_at_risk_square(line, brd, marker)
  if brd.values_at(*line).count(marker) == 2 &&
     brd.values_at(*line).count(INITIAL_MARKER) == 1
    brd.select { |k, _| line.include?(k) }.key(INITIAL_MARKER)
  end
end

def player_places_piece!(brd)
  square = ''
  loop do
    prompt "Choose a position to place a piece: #{joinor(empty_squares(brd), '; ')}:"
    square = gets.chomp.to_i
    break if empty_squares(brd).include?(square)
    prompt "Sorry, that's not a valid choice."
  end
  brd[square] = PLAYER_MARKER
end

def computer_places_piece!(brd)
  square = nil

  WINNING_LINES.each do |line|
    square = find_at_risk_square(line, brd, COMPUTER_MARKER)
    break if square
  end

  if !square
    WINNING_LINES.each do |line|
      square = find_at_risk_square(line, brd, PLAYER_MARKER)
      break if square
    end
  end

  if !square
    square = if empty_squares(brd).include?(5)
               5
             else
               empty_squares(brd).sample
             end
  end

  brd[square] = COMPUTER_MARKER
end

def board_full?(brd)
  empty_squares(brd).empty?
end

def display_winner(brd)
  WINNING_LINES.each do |line|
    if brd.values_at(*line).count(PLAYER_MARKER) == 3
      return "Player"
    elsif brd.values_at(*line).count(COMPUTER_MARKER) == 3
      return "Computer"
    end
  end
  nil
end

def someone_won?(brd)
  display_winner(brd)
end

def place_piece!(board, current_player)
  if current_player == "Player"
    player_places_piece!(board)
  else
    computer_places_piece!(board)
  end
end

def alternate_player(current_player)
  current_player == "Player" ? "Computer" : "Player"
end

loop do
  first_player = ""
  if FIRST_PLAYER == "Choose"
    loop do
      prompt "Who should play first? Player or Computer?"
      first_player = gets.chomp.capitalize
      break unless !%w(Player Computer).include?(first_player)
      prompt "Sorry that's not a valid input. Please choose one of Player or Computer"
    end
  else
    first_player = FIRST_PLAYER
  end

  score = { "Player" => 0, "Computer" => 0 }

  loop do
    board = initialize_board

    current_player = first_player == "Player" ? "Player" : "Computer"

    loop do
      display_board(board, score)
      place_piece!(board, current_player)
      current_player = alternate_player(current_player)
      break if someone_won?(board) || board_full?(board)
    end

    display_board(board, score)

    if someone_won?(board)
      prompt "#{display_winner(board)} won this round!"
      score[display_winner(board)] += 1
    else
      prompt "It's a tie!"
    end

    sleep(2)

    break if score.key(5)
  end

  system 'clear'
  prompt "#{score.key(5)} won this game! Play again? (y or n)"
  answer = gets.chomp
  break unless answer.downcase.start_with?("y")
end

prompt "Thanks for playing Tic Tac Toe! Good bye!"
