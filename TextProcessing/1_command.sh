# Example file: data.txt
# ID,Name,Score
# 1,John,85
# 2,Alice,92
# 3,Bob,78

# Print the first and third columns
awk -F',' '{print $1, $3}' data.txt

# Calculate the average of the third column (scores)
awk -F',' '{sum += $3; count++} END {print "Average Score:", sum/count}' data.txt


# Print names of students who scored more than 80
awk -F',' '$3 > 80 {print $2}' data.txt


# Count the number of lines containing "Alice"
awk '/Alice/ {count++} END {print "Occurrences of Alice:", count}' data.txt


# Print lines between lines containing "Alice" and "Bob"
awk '/Alice/, /Bob/' data.txt
