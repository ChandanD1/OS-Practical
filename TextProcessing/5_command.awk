#!/usr/bin/awk -f

# Process each line and print the last column
{
    print $NF;
}
