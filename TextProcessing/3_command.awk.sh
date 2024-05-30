#!/usr/bin/awk -f

# Initialize sum variable
BEGIN {
    sum = 0;
}

# Process each line and add the value of the first column to sum
{
    sum += $1;
}

# Print the total sum after processing all lines
END {
    print "Sum of values in the first column:", sum;
}
