SUITS = ['H', 'S', 'D', 'C'].freeze
VALUES = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'].freeze
GAME_MAX = 21
DEALER_MAX = 17

def initialize_deck
  SUITS.product(VALUES).shuffle
end

def prompt(message)
  puts "=> #{message}"
end

def total(cards)
  values = cards.map { |card| card[1] }

  sum = 0
  values.each do |value|
    sum = if value == 'A'
            sum + 11
          elsif value.to_i == 0
            sum + 10
          else
            sum + value.to_i
          end
  end

  values.count('A').times do
    if sum > GAME_MAX
      sum -= 10
    end
  end

  sum
end

def busted?(cards)
  total(cards) > GAME_MAX
end

def calculate_winner(player_cards, dealer_cards)
  if busted?(player_cards)
    :player_busted
  elsif busted?(dealer_cards)
    :dealer_busted
  elsif total(player_cards) > total(dealer_cards)
    :player
  elsif total(dealer_cards) > total(player_cards)
    :dealer
  else
    :tie
  end
end

def display_result(player_cards, dealer_cards)
  case calculate_winner(player_cards, dealer_cards)
  when :player_busted
    prompt "You busted! Dealer wins!"
  when :dealer_busted
    prompt "Dealer busted! You win!"
  when :player
    prompt "You win!"
  when :dealer
    prompt "Dealer wins!"
  else
    prompt "It's a tie!"
  end
end

def play_again?
  puts "-----------------------"
  prompt "Do you want to play again? (y or n)"
  answer = gets.chomp
  answer.downcase.start_with?('y')
end

prompt "Welcome to #{GAME_MAX}!"

loop do
  deck = initialize_deck

  player_cards = []
  dealer_cards = []

  2.times do
    player_cards << deck.pop
    dealer_cards << deck.pop
  end

  prompt "Dealer cards are #{dealer_cards[0]} and another"
  prompt "Your cards are #{player_cards[0]} and #{player_cards[1]} and your total is #{total(player_cards)}"

  loop do
    player_turn = nil
    loop do
      prompt "Do you want to (h)it or (s)tay?"
      player_turn = gets.chomp
      break if %w(h s).include?(player_turn)
      prompt "Sorry, that's not a valid choice. Please choose h or s"
    end

    if player_turn == 'h'
      player_cards << deck.pop
      prompt "You chose to hit!"
      prompt "Your cards are now #{player_cards} and your new total is #{total(player_cards)}"
    end

    break if busted?(player_cards) || player_turn == 's'
  end

  if busted?(player_cards)
    display_winner(player_cards, dealer_cards)
    play_again? ? next : break
  else
    prompt "You stayed at #{total(player_cards)}"
  end

  prompt "Dealer turn..."

  loop do
    break if total(dealer_cards) >= DEALER_MAX
    prompt "Dealer hits!"
    dealer_cards << deck.pop
    prompt "Dealer's cards are now #{dealer_cards}"
  end

  if busted?(dealer_cards)
    display_result(player_cards, dealer_cards)
    play_again? ? next : break
  else
    prompt "Dealer stays at #{total(dealer_cards)}"
  end

  prompt "You chose to stay with #{player_cards} at a total of #{total(player_cards)}"
  prompt "Dealer chose to stay with #{dealer_cards} at a total of #{total(dealer_cards)}"
  display_result(player_cards, dealer_cards)

  break unless play_again?
end

prompt "Thank you for playing #{GAME_MAX}! Good bye!"
