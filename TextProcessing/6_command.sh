
sed 's/Hello/Hi/' file.txt


# Delete lines containing "2"
sed '/2/d' file.txt



# Print the first line
sed -n '1p' file.txt


# Substitute "Hello" with "Hi" with confirmation
sed 's/Hello/Hi/gp; s/Hello/Hi/'


# Replace line 2 with "Updated Line"
sed '2s/.*/Updated Line/' file.txt

