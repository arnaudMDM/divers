x = (0..99).to_a.sort_by{rand}.join
i = 0
hash = {}
stack = []
(0..99).each {|i| hash[i] = false}
while i < x.length
  while i < (x.length - 1) and x[i].to_i != 0 and hash[(x[i] + x[i + 1]).to_i] == false
    hash[(x[i] + x[i + 1]).to_i] = true
    stack << (x[i] + x[i + 1])
    i += 2
  end
  while i < x.length
    if hash[x[i].to_i] == false
      hash[x[i].to_i] = true
      stack << x[i]
      i += 1 
      break
    else
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