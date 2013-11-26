x = (0..99).to_a.sort_by{rand}.join
i = 0
hash = {}
stack = []
(0..99).each {|i| hash[i] = false}
while i < x.length
  # we check if x has just one character becausewe can't read two characters. We also check if the first character to read isn't zero. We also check if the number read is not in the list hash
  while i < (x.length - 1) and x[i].to_i != 0 and hash[(x[i] + x[i + 1]).to_i] == false
    hash[(x[i] + x[i + 1]).to_i] = true
    stack << (x[i] + x[i + 1])
    i += 2
  end
  while i < x.length
    # we check if the number read isn't in the list hash
    if hash[x[i].to_i] == false
      hash[x[i].to_i] = true
      stack << x[i]
      i += 1 
      break
    else
      # we get rid of the value in the stack because it is not good. If the value which we retrieve is between 0 and 9 included we retrieve the next value in stack. And so on...
      loop do
        val = stack.pop
    	  hash[val.to_i] = false
    	  i -= val.length
  	    break if val.length != 1
      end
    end
  end
end
puts stack.sort_by(&:to_i)